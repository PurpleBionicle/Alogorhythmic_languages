
#ifndef INCLUDE_BOOLEAN_FUNCTION_HPP_
#define INCLUDE_BOOLEAN_FUNCTION_HPP_

#include <header.hpp>
#include <string>
#include <vector>
class boolean_function {
public:
    using value_type = bool;
    using size_type = size_t;
    using reference = std::vector<value_type>::reference;
    using const_reference = std::vector<value_type>::const_reference;

    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

public:
    ~boolean_function() = default;
    boolean_function() = default;
    // Cоздаёт функцию от dimension переменных, равную переменной Xn
    // Пример 1 (n = 0, dimension = 3):
    // вернёт "01010101"
    // пример 2 (n = 1, dimension = 4):
    // вернёт "0011001100110011"
    static boolean_function var(size_t n, size_t dimension) {
        boolean_function buffer;
        for (unsigned int i = 0; i < dimension + 1; ++i) {
            for (unsigned int j = 0; j < pow(2, n); ++j) {
                buffer.Data.push_back(false);
            }
            for (unsigned int j = 0; j < pow(2, n); ++j) {
                buffer.Data.push_back(true);
            }
        }

        return buffer;
    }

    // Тождественный ноль "от dimension переменных"
    static boolean_function zero(size_t dimension) {
        boolean_function a;
        for (int i = 0; i < pow(2, dimension); ++i) {
            a.Data.push_back(false);
        }
        return a;
    }

    // Тождественная единица "от dimension переменных"
    static boolean_function one(size_t dimension) {
        boolean_function a;
        for (unsigned int i = 0; i < pow(2, dimension); ++i) {
            a.Data.push_back(true);
        }
        return a;
    }

    static boolean_function from_anf(std::vector<value_type> v) {
        boolean_function buf(v);
        bool k = false;
        for (size_t i = 0; i < buf.dimension(); ++i) {
            for (int j = 0; j < pow(2, buf.dimension()); ++j) {
                if (k) {
                    buf[j] = buf[j - pow(2, i)] ^ buf[j];
                }
                if ((j + 1) % static_cast<int>(pow(2, i)) == 0 && (j != 0 || i == 0)) {
                    if (!k) {
                        k = true;
                    } else {
                        k = false;
                    }
                }
            }
        }
        return buf;
    }

    // Создаёт функцию тождественного нуля от n переменных
    explicit boolean_function(size_t n) {
        for (unsigned int i = 0; i < pow(2, n); ++i) Data.push_back(false);
    }

    // Создаёт функцию от n переменных. Вектор значений представляется числом
    // value Пример: пусть value = 14, т.е. 0...00001110 в двоичной системе а n =
    // 3 тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
    boolean_function(int64_t value, size_type n) {
        while (value != 0) {
            int64_t c = value % 2;  // остаток
            value /= 2;
            Data.push_back(c);
        }
        Data.push_back(0);
        // добавим нули в начало
        while (Data.size() < pow(2, n)) Data.insert(Data.begin(), 0);
    }

    // Создаёт функцию из строки, содержащей вектор значений
    // пусть table = "01110000"
    // тогда АНФ boolean_function будет равна x + y + xy + zx + zy + zyx
    explicit boolean_function(const std::string& table) {
        for (unsigned int i = 0; i < table.length(); ++i) {
            if (table[i] == '0')
                Data.push_back(false);
            else
                Data.push_back(true);
        }
    }

    // Создаёт функцию из вектора значений
    // пусть table = {true, false, false, true};
    // тогда АНФ boolean_function будет равна x + y + 1
    explicit boolean_function(const std::vector<value_type>& table) {
        for (unsigned int i = 0; i < table.size(); ++i) {
            Data.push_back(table[i]);
        }
    }
    boolean_function(const std::initializer_list<bool> vars) {
        auto iter = vars.begin();
        while (iter != vars.end())  // пока не дойдем до конца
        {
            Data.push_back(*iter);
            ++iter;
        }
    }

    boolean_function(const boolean_function& table) {
        for (bool i : table.Data) {
            Data.push_back(i);
        }
    }

    boolean_function& operator=(const boolean_function& rhs) {
        Data.clear();
        for (unsigned int i = 0; i < rhs.Data.size(); ++i) {
            Data.push_back(rhs[i]);
        }
        return *this;
    }

    // Сложение по модулю 2
    // если разное количество переменных - исключение
    boolean_function& operator+=(const boolean_function& rhs) {
        if (Data.size() != rhs.Data.size()) {
            throw std::logic_error("incomparable");
        }
        boolean_function buf;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            buf.Data.push_back((Data[i] + rhs.Data[i]) % 2);
        }
        *this = buf;
        return *this;
    }

    // Конъюнкция
    // если разное количество переменных - исключение
    boolean_function& operator*=(const boolean_function& rhs) {
        if (Data.size() != rhs.Data.size()) {
            throw std::logic_error("incomparable");
        }
        boolean_function buf;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i] && rhs.Data[i])  // оба true
                buf.Data.push_back(true);
            else
                buf.Data.push_back(false);
        }
        *this = buf;
        return *this;
    }

    // Дизъюнкция
    // если разное количество переменных - исключение
    boolean_function& operator|=(const boolean_function& rhs) {
        if (Data.size() != rhs.Data.size()) {
            throw std::logic_error("incomparable");
        }
        boolean_function buf;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (!Data[i] && !rhs.Data[i])  // оба false
                buf.Data.push_back(false);
            else
                buf.Data.push_back(true);
        }
        *this = buf;
        return *this;
    }

    // Побитовое отрицание
    boolean_function operator~() {
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i]) {
                Data[i] = false;
            } else {
                Data[i] = true;
            }
        }
        return *this;
    }

    // true если функции равны
    // иначе false
    bool operator==(const boolean_function& rhs) const {
        if (Data.size() != rhs.Data.size()) return false;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i] != rhs.Data[i]) return false;
        }
        return true;
    }

    // true если одна функция сравнима и больше или равна rhs
    // false если сравнима и меньше rhs
    // logic_error если фунции не сравнимы
    bool operator>=(const boolean_function& rhs) const {
        if (Data.size() != rhs.Data.size())
            throw std::logic_error("different size");
        int count_bigger = 0;
        int count_lower = 0;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i] && !rhs.Data[i]) count_bigger++;
            if (!Data[i] && rhs.Data[i]) count_lower++;
            if (count_lower != 0 && count_bigger != 0) {
                throw std::logic_error("incomparable");
            }
        }
        if (count_bigger >= 0 && count_lower == 0)
            return true;
        else
            return false;
    }

    reference operator[](size_type ind) { return Data[ind]; }
    const_reference operator[](size_type ind) const { return Data[ind]; }

    reference at(size_type ind) { return Data.at(ind); }
    [[nodiscard]] const_reference at(size_type ind) const { return Data.at(ind); }

    iterator begin() { return Data.begin(); }
    iterator end() { return Data.end(); }

    [[nodiscard]] const_iterator cbegin() const { return Data.begin(); }
    [[nodiscard]] const_iterator cend() const { return Data.end(); }

    // Длина столбца функции
    [[nodiscard]] size_type size() const throw() { return Data.size(); }

    // Количество переменных
    [[nodiscard]] size_type dimension() const throw() {
        return std::log2(Data.size());
    }

    // Возвращает значение функции на наборе значений переменных
    // пусть boolean_function задает функцию f(x, y, z)
    // тогда функция вернет f(vars[0], vars[1], vars[2])
    bool operator()(const std::vector<bool>& vars) const {
        int64_t g = 0;
        for (int i = vars.size() - 1; i >= 0; --i) {
            g += pow(2, i) * vars[vars.size() - 1 - i];
        }
        //надо g перевести в двоичную систему теперь
        return Data[g];
    }
    bool operator()(const std::initializer_list<bool> vars) const {
        int64_t g = 0;
        int count = 0;
        auto iter = vars.begin();
        while (iter != vars.end())  // пока не дойдем до конца
        {
            g += pow(2, vars.size() - 1 - count) * (*iter);
            ++count;
            ++iter;
        }
        return Data[g];
    }

    // T(x1, x2, ..., xN) - текущая функция
    // operator вернет новую функцию, которая равна композиции G = T(fs[0], fs[1],
    // ..., fs[N-1])
    boolean_function operator()(const std::vector<boolean_function>& fs) const {
        boolean_function result(fs[0].dimension());
        for (unsigned int i = 0; i < fs[0].size(); ++i) {
            int64_t g = 0;
            for (unsigned int j = 0; j < fs.size(); ++j) {
                g += pow(2, fs.size() - 1 - j) * fs[j][i];
            }
            result[i] = Data[g];
        }
        return result;
    }
    boolean_function operator()(
            const std::initializer_list<boolean_function> vars) const {
        boolean_function result(vars.begin()->dimension());
        auto iter = vars.begin();
        for (unsigned int i = 0; i < iter->Data.size(); ++i) {
            int64_t g = 0;
            for (unsigned int j = 0; j < vars.size(); ++j) {
                g += pow(2, vars.size() - 1 - j) * (*iter)[i];
            }
            result[i] = Data[g];
            ++iter;
        }
        return result;
    }

    bool is_monotone() const  // монотонная
    {
        if (!this->is_T0() && !this->is_T1()) return false;
        if (!this->is_T0() && this->weight() != Data.size()) return false;
        if (!this->is_T1() && this->weight() != 0) return false;
        int p = 1 << this->dimension();
        for (int i = 0; i < p - 1; i++)
            for (int j = i + 1; j < p; j++)
                if ((i & j) == i &&
                    Data[i] >
                    Data[j])  // i является подмаской j и нарушается монотонность
                    return false;
        return true;
    }
    bool is_selfdual() const  // самодвойственная
    {
        for (unsigned int i = 0; i < Data.size() / 2; ++i) {
            if (Data[i] == Data[Data.size() - i - 1]) return false;
        }
        return true;
    }
    bool is_linear() const  // линейная
    {
        std::vector<bool> a(pow(2, this->dimension()));
        a = this->anf();
        for (unsigned int i = 1; i < a.size(); i++) {
            if (a[i]) {
                unsigned int k = 0;
                for (; k < this->dimension() + 1;) {
                    if (i != pow(2, k))
                        k++;
                    else
                        break;
                }
                if (k == this->dimension() + 1) return false;
            }
        }
        return true;
    }
    bool is_T1() const  // сохраняет единицу
    {
        if (Data[Data.size() - 1]) return true;
        return false;
    }
    bool is_T0() const  // сохраняет ноль
    {
        if (!Data[0]) return true;
        return false;
    }
    bool is_balanced() const  // равновесная
    {
        size_t weigh = 0;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i]) weigh++;
        }
        if (weigh == (Data.size() / 2)) return true;
        return false;
    }
    bool is_symmetric() const  // симметричная
    {
        boolean_function a = *this;
        for (unsigned int i = 0; i < a.size() - 1; ++i) {
            if (a.var(i, a.size()) == a.var(i + 1, a.size())) {
            } else {
                return false;
            }
        }
        return true;
    }
    size_t weight() const {
        size_t weigh = 0;
        for (unsigned int i = 0; i < Data.size(); ++i) {
            if (Data[i]) weigh++;
        }
        return weigh;
    }

    [[nodiscard]] bool is_functionally_complete_system() const {
        boolean_function a = *this;
        if (!a.is_T0() && !a.is_T1() && !a.is_linear() && !a.is_monotone() &&
            !a.is_selfdual())
            return true;
        return false;
    }

    //Возвращает АНФ функции
    [[nodiscard]] std::vector<value_type> anf() const {
        std::vector<value_type> a(pow(2, this->dimension()));
        for (int k = 0; k < pow(2, this->dimension()); ++k) {
            a[k] = Data[k];
        }
        for (size_t i = 1; i < this->dimension() + 1; ++i) {
            for (int s = 0; s < pow(2, this->dimension() - i); ++s) {
                for (int l = 0; l < pow(2, i - 1); ++l) {
                    if (a[pow(2, i) * s + pow(2, i - 1) + l] && a[pow(2, i) * s + l]) {
                        a[pow(2, i) * s + pow(2, i - 1) + l] = false;
                    } else {
                        if (!a[pow(2, i) * s + pow(2, i - 1) + l] &&
                            !a[pow(2, i) * s + l]) {
                            a[pow(2, i) * s + pow(2, i - 1) + l] = false;
                        } else {  // в ином случае
                            a[pow(2, i) * s + pow(2, i - 1) + l] = true;
                        }
                    }
                }
            }
        }
        return a;
    }

private:
    std::vector<value_type> Data;
};

boolean_function operator+(const boolean_function& a,
                           const boolean_function& b) {  //по модулю сложение
    if (a.size() != b.size()) {
        throw std::invalid_argument("incomparable");
    }
    boolean_function buf(a.dimension());
    for (unsigned int i = 0; i < a.size(); ++i) {
        buf[i] = ((a[i] + b[i]) % 2);
    }
    return buf;
}

boolean_function operator*(const boolean_function& a,
                           const boolean_function& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("incomparable");
    }
    boolean_function buf(a.dimension());
    for (unsigned int i = 0; i < a.size(); ++i) {
        if (a[i] && b[i])  // оба true
            buf[i] = true;
        else
            buf[i] = false;
    }
    return buf;
}

boolean_function operator|(const boolean_function& a,
                           const boolean_function& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("incomparable");
    }
    boolean_function buf(a.dimension());
    for (unsigned int i = 0; i < a.size(); ++i) {
        if (!a[i] && !b[i])  // оба false
            buf[i] = false;
        else
            buf[i] = true;
    }
    return buf;
}
// Пусть boolean_function задаётся вектором значений "01110000"
// тогда get_polynom вернет строку "x0 + x1 + x0x1 + x0x2 + x1x2 + x0x1x2"
std::string get_polynom(const boolean_function& a) {
    std::vector<bool> anf = a.anf();
    std::string result;
    for (unsigned int i = 0; i < anf.size(); ++i) {
        if (anf[i])  // то это число надо перевести в двоичную сс
        {
            std::vector<bool> res;
            int f = i;
            while (f != 0) {
                int64_t c = f % 2;  // остаток
                f /= 2;
                res.push_back(c);
            }
            // res.push_back(0);
            for (unsigned int k = 0; k < res.size(); ++k) {
                if (res[k]) {
                    result += 'x';
                    if (k != 0)
                        result += std::to_string(k);
                    else
                        result += '0';
                }
            }
            if (i != anf.size() - 1) result += " + ";
        }
    }
    return result;
}
bool operator!=(const boolean_function& a, const boolean_function& b) {
    if (a == b) return false;
    return true;
}

bool is_functionally_complete_system(const std::vector<boolean_function>& fs) {
    // все  минусы для того чтобы была не ФПС
    bool t1 = false, t0 = false, s = false, l = false, m = false;
    for (unsigned int i = 0; i < fs.size(); ++i) {
        if (!fs[i].is_T1()) t1 = true;
        if (!fs[i].is_T0()) t0 = true;
        if (!fs[i].is_selfdual()) s = true;
        if (!fs[i].is_monotone()) m = true;
        if (!fs[i].is_linear()) l = true;
    }
    if (s && t0 && t1 && l && m) return true;
    return false;
}
bool is_functionally_complete_system(
        const std::initializer_list<boolean_function> vars) {
    auto iter = vars.begin();
    bool t1 = false, t0 = false, s = false, l = false, m = false;
    while (iter != vars.end()) {
        if (iter->is_T1()) t1 = true;
        if (iter->is_T0()) t0 = true;
        if (iter->is_linear()) l = true;
        if (iter->is_monotone()) m = true;
        if (iter->is_selfdual()) s = true;
        ++iter;
    }
    if (s && t0 && t1 && l && m) return true;
    return false;
}

#endif  // INCLUDE_BOOLEAN_FUNCTION_HPP_