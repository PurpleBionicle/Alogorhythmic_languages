
#ifndef INCLUDE_CAST_FROM_STRING_HPP_
#define INCLUDE_CAST_FROM_STRING_HPP_
#include <header.hpp>
#include <limits>
#include <string>
#include <vector>
class CastException : public std::invalid_argument {
public:
    explicit CastException(const std::string& str) : std::invalid_argument(str) {}
};
class IncorrectTYPE : public CastException {
public:
    explicit IncorrectTYPE(const std::string& str) : CastException(str) {}
};
class Incorrect_Symbols : public CastException {
public:
    explicit Incorrect_Symbols(const std::string& str) : CastException(str) {}
};
class Empty_Str : public CastException {
public:
    explicit Empty_Str(const std::string& str) : CastException(str) {}
};
class Bigger_or_lower_than_can : public CastException {
public:
    explicit Bigger_or_lower_than_can(const std::string& str)
            : CastException(str) {}
};
template <typename T>
inline T FromString(const std::string& str) {
    if (str.empty()) throw Empty_Str("empty string");
    if (std::is_same<T, int>::value) {
        std::vector<int> number;
        bool flag = true;
        if (str[0] == '-' || str[0] == '+') flag = false;
        for (int i = str.size() - 1; i >= 0; i--) {
            if ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+') {
                throw Incorrect_Symbols("incorrect string");
            } else {
                std::vector<char> string_number = {'0', '1', '2', '3', '4',
                                                   '5', '6', '7', '8', '9'};
                for (unsigned int k = 0; k < string_number.size(); k++) {
                    if (!flag && i == 0) {
                        break;
                    } else {
                        if (string_number[k] == str[i]) {
                            number.push_back(k);
                            break;
                        }
                    }
                    // иными словами в number лежат все цифры строки в обратном порядке
                }
            }
        }
        //перезапишем из вектора числа каждый раз умножая след на еще раз на 10
        int a = 0;
        for (unsigned int i = 0; i < number.size(); ++i) {
            a += number[i] * pow(10, i);
        }
        if (str[0] == '-') a *= -1;
        if (a >= std::numeric_limits<int>::max() ||
            a <= std::numeric_limits<int>::min())
            throw Bigger_or_lower_than_can("incorrect string");
        return a;
    } else {
        if (std::is_same<T, bool>::value) {
            std::string a = "False";
            if (str == a) {
                return false;
            }
            std::string b = "false";
            if (str == b) {
                return false;
            }
            std::string c = "True";
            if (str == c) {
                return true;
            }
            std::string d = "true";
            if (str == d) {
                return true;
            }
            throw Incorrect_Symbols("incorrect string");
        } else {
            throw IncorrectTYPE("not int or bool");
        }
    }
}
#endif  // INCLUDE_CAST_FROM_STRING_HPP_