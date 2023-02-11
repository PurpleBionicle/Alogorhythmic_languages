
#include <header.hpp>

size_t str_find(const std::string& str, const std::string& substr) {
    if (str.size() < substr.size()) return std::string::npos;
    auto start = std::chrono::steady_clock::now();
    // std::cout //<<"Длина подстроки="
    //    <<substr.length()<<std::endl;
    for (unsigned int i = 0; i < str.size(); ++i) {
        unsigned int j = 0;
        int k = i;
        while (substr[j] == str[i]) {
            if (i < str.size()) {
                j++;
                i++;
            } else {
                break;
            }
        }
        if (j == substr.size()) {
            auto finish = std::chrono::steady_clock::now();
            auto dur = finish - start;
            std::cout
                    // << "Метод прямого поиска   "
                    << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
                    //  << " micro s "
                    << std::endl;
            return (i - substr.size());
        }
        i = k;
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cout
            // << "Метод прямого поиска   "
            << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
            // << " micro s"
            << std::endl;
    return std::string::npos;
}
size_t rk_find(const std::string& str, const std::string& substr) {
    if (str.size() < substr.size()) return std::string::npos;
    auto start = std::chrono::steady_clock::now();
    // std::cout
    //<<"Длина подстроки="
    // <<substr.length()<<std::endl;
    unsigned int p = 223;  // простое число , 223 для уменьшения числа коллизий
    std::vector<int64_t> p_pow(str.length());
    p_pow[0] = 1;
    for (size_t i = 1; i < p_pow.size(); ++i)
        p_pow[i] = p_pow[i - 1] * p;  //степени
    std::vector<int64_t> h(str.length());
    for (size_t i = 0; i < str.length(); ++i) {
        h[i] = (str[i] - 'a' + 1) * p_pow[i];
        if (i != 0) h[i] += h[i - 1];
    }

    // хэш подстроки
    int64_t h_s = 0;
    for (size_t i = 0; i < substr.length(); ++i)
        h_s += (substr[i] - 'a' + 1) * p_pow[i];

    // перебираем все подстроки и сравниваем их
    for (size_t i = 0; i + substr.length() - 1 < str.length(); ++i) {
        int64_t cur_h = h[i + substr.length() - 1];
        if (i) cur_h -= h[i - 1];
        // приводим хэши к одной степени и сравниваем
        if (cur_h == h_s * p_pow[i]) {
            auto finish = std::chrono::steady_clock::now();
            auto dur = finish - start;
            std::cout
                    //<< "PK Метод    "
                    << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
                    //<< " micro s "
                    << std::endl;
            return i;
        }
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cout
            //<< "PK Метод   "
            << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
            //<< " micro s "
            << std::endl;
    return std::string::npos;
}
std::vector<int> prefix_function(const std::string& s) {
    std::vector<int> pi(s.length());
    for (unsigned int i = 1; i < s.length(); ++i) {
        int j = pi[i - 1];  // для первого всегда 0

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        } else {
            pi[i] = 0;
        }
    }

    return pi;
}
size_t kmp_find(const std::string& str, const std::string& substr) {
    if (str.size() < substr.size()) return std::string::npos;
    auto start = std::chrono::steady_clock::now();
    std::vector<int> pi = prefix_function(substr + " " + str);

    int substrlen = substr.length();
    for (unsigned int i = 0; i < str.length(); i++) {
        if (pi[substrlen + 1 + i] == substrlen) {
            auto finish = std::chrono::steady_clock::now();
            auto dur = finish - start;
            std::cout
                    // << "KMP алгоритм   "
                    << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
                    // << " micro s"
                    << std::endl;
            return (i - substrlen + 1);
        }
    }
    auto finish = std::chrono::steady_clock::now();
    auto dur = finish - start;
    std::cout
            // << "KMP алгоритм   "
            << std::chrono::duration_cast<std::chrono::microseconds>(dur).count()
            // << " micro s"
            << std::endl;
    return std::string::npos;
}