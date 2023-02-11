#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "header.hpp"
//Возвращает разумный тип mime, основанный на расширении файла.
beast::string_view mime_type(beast::string_view path);

auto from_json(const json& j) -> std::string;

//Добавляем относительный путь HTTP к пути локальной файловой системы.
// Возвращаемый путь нормализуется для платформы.
std::string path_cat(beast::string_view base, beast::string_view path);

// Эта функция выдает HTTP-ответ для данного
// запрос. Тип объекта ответа зависит от
// содержимого запроса, поэтому интерфейс требует
//, чтобы вызывающий // передал общий лямбда-код для получения ответа.
template <class Body, class Allocator, class Send>
void handle_request(beast::string_view doc_root,
                    http::request<Body, http::basic_fields<Allocator>>&& req,
                    Send&& send) {
    //Возвращает неверный ответ на запрос
    auto const bad_request = [&req](beast::string_view why) {
        http::response<http::string_body> res{http::status::bad_request,
                                              req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found = [&req](beast::string_view target) {
        http::response<http::string_body> res{http::status::not_found,
                                              req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + std::string(target) + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error = [&req](beast::string_view what) {
        http::response<http::string_body> res{http::status::internal_server_error,
                                              req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + std::string(what) + "'";
        res.prepare_payload();
        return res;
    };

    // Make sure we can handle the method
    if (req.method() != http::verb::get && req.method() != http::verb::head &&
        req.method() != http::verb::post)
        return send(bad_request("Unknown HTTP-method"));

    // Request path must be absolute and not contain "..".
    if (req.target().empty() || req.target()[0] != '/' ||
        req.target().find("..") != beast::string_view::npos)
        return send(bad_request("Illegal request-target"));

    // Build the path to the requested file
    std::string path = path_cat(doc_root, req.target());
    if (req.target().back() == '/') path.append("index.html");

    //Попытка открыть файл
    beast::error_code ec;
    http::file_body::value_type body;
    body.open(path.c_str(), beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if (ec == beast::errc::no_such_file_or_directory)
        return send(not_found(req.target()));

    // Handle an unknown error
    if (ec) return send(server_error(ec.message()));

    // Кэшируйте размер, так как он нам понадобится после перемещения
    auto const size = body.size();

    // Ответить на запрос
    if (req.method() == http::verb::head) {
        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, mime_type(path));
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    } else if (req.method() == http::verb::post) {  // Ответить на запрос POST
        boost::beast::string_view content_type = req[http::field::content_type];
        if (content_type != "application/json" ||
            req.target() != "/v1/api/suggest") {
            return send(bad_request("Bad request"));
        }
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "application/json");
        res.keep_alive(req.keep_alive());

        json jtext = json::parse(req.body());
        std::string input_value = from_json(jtext.at("input"));

        try {
            std::ifstream file("../v1/api/suggest/file.json");
            json data;
            file >> data;
            std::map<size_t, json> cost;
            for (auto& sug : data.at("requests").at(input_value)) {
                json request_arr = json::object();
                request_arr["text"] = sug["name"];
                cost[sug["cost"]] = request_arr;
            }

            json request = json::object();
            size_t i = 0;
            for (auto& elem : cost) {
                elem.second["position"] = i;
                request["suggestions"].push_back(elem.second);
                ++i;
            }
            res.body() = request.dump();
        } catch (const std::exception& ex) {
            if (std::string(ex.what()) == ("[json.exception.out_of_range.403] key '" +
                                           input_value + "' not found")) {
                std::ifstream dictionary("/usr/share/dict/words");
                std::string s;
                std::regex reg("\\b(" + input_value + ")([^ ]*)");

                size_t i = 0;
                std::vector<std::string> sug;
                while (std::getline(dictionary, s) && i < 4) {
                    std::smatch m;
                    while (std::regex_search(s, m, reg) && i < 4) {
                        sug.push_back(m.str());
                        s = m.suffix().str();
                        ++i;
                    }
                }
                sug.erase(sug.begin());
                json request = json::object();
                size_t pos = 0;
                std::ifstream file("../v1/api/suggest/file.json");
                json data = json::object();
                file >> data;
                file.close();
                for (auto& elem : sug) {
                    json new_sug_arr = json::object();
                    json request_arr = json::object();
                    new_sug_arr["name"] = elem;
                    request_arr["text"] = elem;
                    new_sug_arr["cost"] = (10 - static_cast<int>(pow(2, pos + 1))) * 100;
                    request_arr["position"] = pos;
                    ++pos;
                    data["requests"][input_value].push_back(new_sug_arr);
                    request["request"].push_back(request_arr);
                }
                std::ofstream ofile("../v1/api/suggest/file.json");
                ofile << data;
                ofile.close();
                res.body() = request.dump();
            }
        }
        res.prepare_payload();
        return send(std::move(res));
    }

    // Ответить на запрос GET
    http::response<http::file_body> res{
            std::piecewise_construct, std::make_tuple(std::move(body)),
            std::make_tuple(http::status::ok, req.version())};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, mime_type(path));
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    return send(std::move(res));
}

//------------------------------------------------------------------------------

// Report a failure
void fail(beast::error_code ec, char const* what);

//Это эквивалент C++11 универсального лямбда-выражения.
// Объект функции используется для отправки HTTP-сообщения.
template <class Stream>
struct send_lambda {
    Stream& stream_;
    bool& close_;
    beast::error_code& ec_;

    explicit send_lambda(Stream& stream, bool& close, beast::error_code& ec)
            : stream_(stream), close_(close), ec_(ec) {}

    template <bool isRequest, class Body, class Fields>
    void operator()(http::message<isRequest, Body, Fields>&& msg) const {
        // Determine if we should close the connection after
        close_ = msg.need_eof();

        // Нам нужен сериализатор здесь, потому что сериализатор требует
        // неконстантное файловое тело и ориентированная на сообщения версия
        // http::write работает только с постоянными сообщениями.
        http::serializer<isRequest, Body, Fields> sr{msg};
        http::write(stream_, sr, ec_);
    }
};

// Handles an HTTP server connection
void do_session(tcp::socket& socket,
                std::shared_ptr<std::string const> const& doc_root);