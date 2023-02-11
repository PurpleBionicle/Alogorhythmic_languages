
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace beast = boost::beast;  // from <boost/beast.hpp>
namespace http = beast::http;    // from <boost/beast/http.hpp>
namespace net = boost::asio;     // from <boost/asio.hpp>
using tcp = net::ip::tcp;        // from <boost/asio/ip/tcp.hpp>

void request(const char* host, const char* port, const char* target,
             const char* jstext, const int& version);

#include <header.hpp>
#include <stdexcept>
void request(const char* host, const char* port, const char* target,
             const char* jstext, const int& version) {
    // Обеспечивает основные функции ввода-вывода.
    net::io_context ioc;

    // Эти объекты выполняют наш ввод-вывод
    tcp::resolver resolver(ioc);
    //Сокет потока TCP/IP с тайм-аутами и полиморфным исполнителем.
    beast::tcp_stream stream(ioc);

    // Проверяет доменное имя
    auto const results = resolver.resolve(host, port);

    // Установливает соединение по IP-адресу, который мы получаем в результате
    // поиска
    stream.connect(results);

    // Настройка HTTP-запроса на получение сообщения
    http::request<http::string_body> req{http::verb::post, target, version};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(http::field::content_type, "application/json");
    req.body() = nlohmann::json::parse(jstext).dump();
    req.prepare_payload();

    // Отправляет  HTTP-запрос на удаленный хост
    http::write(stream, req);

    // Этот буфер используется для чтения и должен быть сохранен
    beast::flat_buffer buffer;

    // контейнер для хранения ответа
    http::response<http::dynamic_body> res;

    // Получение HTTP-ответа
    http::read(stream, buffer, res);

    // Write the message to standard out
    std::cout << res << std::endl;

    // Gracefully close the socket
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec};

    // If we get here then the connection is closed gracefully
}