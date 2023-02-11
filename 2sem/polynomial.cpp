
#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_
#include <cmath>
#include <iostream>
#include <vector>
////// 1 коэффициент в векторе ,который параметром приход  показывает коэфф у
///макс степени
template <typename T>
class Polynomial {
private:
    std::vector<T> koef;

public:
    ~Polynomial() { koef.clear(); }
    Polynomial() = default;

    explicit Polynomial(const std::vector<T> a) {
        koef = a;
        for (int i = static_cast<int>(a.size()) - 1; i >= 0; i--) {
            koef[static_cast<int>(a.size()) - 1 - i] = a[i];
        }
    }
    Polynomial(const Polynomial &a) { koef = a.koef; }

    T operator[](size_t index) { return koef[index]; }
    T operator[](size_t index) const { return koef[index]; }

    size_t size() { return koef.size(); }

    Polynomial operator=(const Polynomial &pol) {
        koef.clear();
        for (unsigned int i = 0; i < pol.koef.size(); ++i) {
            koef.push_back(pol.koef[i]);
        }
        return *this;
    }
    bool operator==(const Polynomial &pol) const {
        if (koef.size() != pol.koef.size()) return false;
        for (unsigned int i = 0; i < koef.size(); ++i) {
            if (koef[i] != pol.koef[i]) return false;
        }
        return true;
    }

    Polynomial operator+(const Polynomial &p) const {
        Polynomial res;
        if (koef.size() >= p.koef.size()) {
            res.koef = koef;
            for (unsigned int i = 0; i < p.koef.size(); i++) {
                res.koef[i] += p.koef[i];
            }
        } else {
            res.koef = koef;
            for (unsigned int i = 0; i < koef.size(); i++) {
                res.koef[i] += p.koef[i];
            }
            for (unsigned int i = koef.size(); i < p.koef.size(); i++) {
                res.koef.push_back(p.koef[i]);
            }
        }
        return res;
    }

    Polynomial operator+=(const Polynomial &pol) {
        if (koef.size() >= pol.koef.size()) {
            for (unsigned int i = 0; i < pol.koef.size(); ++i) koef[i] += pol.koef[i];
        } else {
            for (unsigned int i = 0; i < koef.size(); ++i) koef[i] += pol.koef[i];
            for (unsigned int i = koef.size(); i < pol.koef.size(); ++i)
                koef.push_back(pol.koef[i]);
        }
        return *this;
    }

    Polynomial operator-(const Polynomial &p) const {
        Polynomial res;
        if (koef.size() >= p.koef.size()) {
            res.koef = koef;
            for (unsigned int i = 0; i < p.koef.size(); i++) {
                res.koef[i] -= p.koef[i];
            }
        } else {
            res.koef = koef;
            for (unsigned int i = 0; i < koef.size(); i++) {
                res.koef[i] -= p.koef[i];
            }
            for (unsigned int i = koef.size(); i < p.koef.size(); i++) {
                res.koef.push_back(p.koef[i] * (-1));
            }
        }
        return res;
    }

    Polynomial operator-=(const Polynomial &pol) {
        if (koef.size() >= pol.koef.size()) {
            for (unsigned int i = 0; i < pol.koef.size(); ++i) koef[i] -= pol.koef[i];
        } else {
            for (unsigned int i = 0; i < koef.size(); ++i) koef[i] -= pol.koef[i];
            // а те которые не от чего вычитать ,пушим с другим знаком
            for (unsigned int i = koef.size(); i < pol.koef.size(); ++i)
                koef.push_back(pol.koef[i] * (-1));
        }

        return *this;
    }

    //Умножение на константу типа T;
    Polynomial operator*(const T a) const {
        Polynomial result;
        for (unsigned int i = 0; i < koef.size(); ++i)
            result.koef.push_back(koef[i] * a);

        return result;
    }
    Polynomial operator*=(const T a) {
        for (unsigned int i = 0; i < koef.size(); ++i) koef[i] *= a;
        return *this;
    }
    //Степень полинома;
    int degree() { return koef.size() - 1; }

    // Получение/установка коэффициента при одночлене степени i полинома;
    int Get_koef(int n) {
        if (n > ((*this).degree())) {
            std::cout << "значение превышает максимальную степень" << std::endl;
            return 0;
        } else {
            return koef[n];
        }
    }
    void Set_koef(unsigned int degree, unsigned int new_koef) {
        unsigned int max_degree = (*this).degree();
        if (degree > max_degree) {
            for (unsigned int i = koef.size(); i <= degree; ++i) {
                koef.push_back(0);
            }
        }
        koef[degree] = new_koef;
    }
    //Вычисление значение полинома в точке x;
    T Get_value(T x) {
        T value = 0;
        for (unsigned int i = 0; i < koef.size(); ++i) {
            value += koef[i] * pow(x, koef.size() - 1 - i);
        }
        return value;
    }
    //Умножение на другой полином (*=,*);
    Polynomial operator*(const Polynomial &m) const {
        std::vector<T>

                mult_koef(koef.size() + m.koef.size() - 1);
        Polynomial result(mult_koef);
        for (unsigned int i = 0; i < koef.size(); i++) {
            for (unsigned int j = 0; j < m.koef.size(); j++) {
                result.koef[i + j] += koef[i] * m.koef[j];
            }
        }
        return result;
    }
    Polynomial operator*=(const Polynomial &m) {
        std::vector<T> mult_koef(koef.size() + m.koef.size() - 1);
        Polynomial result(mult_koef);
        for (unsigned int i = 0; i < koef.size(); i++) {
            for (unsigned int j = 0; j < m.koef.size(); j++) {
                result.koef[i + j] += koef[i] * m.koef[j];
            }
        }
        *this = result;
        return *this;
    }
    //Деление на другой полином (/=,/)

    Polynomial operator/(const Polynomial &p2) const {
        std::vector<T> a(koef.size() - p2.koef.size() + 1);
        Polynomial res(a);
        Polynomial temp = *this;
        //если деление невозможно
        if (koef.size() < p2.koef.size()) {
            return Polynomial<T>(std::vector<T>{0});
        } else {
            for (unsigned int i = 0; i < res.koef.size(); ++i) {
                //коэффициент при делении
                //тк -i то двигаемся от большей степени к меньшей
                unsigned int k = 1;
                while (p2.koef[p2.koef.size() - k] == 0) {
                    ++k;
                }
                res.koef[res.koef.size() - i - 1] =
                        temp.koef[temp.koef.size() - 1 - i] / p2.koef[p2.koef.size() - k];
                for (unsigned int j = 0; j < p2.koef.size(); ++j) {
                    // то что осталось после деления на пред шаге
                    temp.koef[temp.koef.size() - j - i - 1] -=
                            p2.koef[p2.koef.size() - j - 1] *
                            res.koef[res.koef.size() - i - 1];
                }
            }
            return res;
        }
    }
    Polynomial operator/=(const Polynomial p2) {
        std::vector<T> a(koef.size() - p2.koef.size() + 1);
        Polynomial res(a);
        //если деление невозможно
        if (koef.size() < p2.koef.size()) {
            *this = Polynomial<T>(std::vector<T>{0});
            return *this;
        } else {
            for (unsigned int i = 0; i < res.koef.size(); ++i) {
                //коэффициент при делении
                //тк -i то двигаемся от большей степени к меньшей
                unsigned int k = 1;
                while (p2.koef[p2.koef.size() - k] == 0) {
                    ++k;
                }
                res.koef[res.koef.size() - i - 1] =
                        koef[koef.size() - 1 - i] / p2.koef[p2.koef.size() - k];
                for (unsigned int j = 0; j < p2.koef.size(); ++j) {
                    // то что осталось после деления на пред шаге
                    koef[koef.size() - j - i - 1] -= p2.koef[p2.koef.size() - j - 1] *
                                                     res.koef[res.koef.size() - i - 1];
                }
            }
            *this = res;
            return *this;
        }
    }
    //Получения остатка от деления на другой полином (%=,%)
    Polynomial operator%(const Polynomial p2) const {
        if (koef.size() < p2.koef.size()) {
            return *this;
        }
        Polynomial temp = *this;
        temp /= p2;
        temp *= p2;
        temp = *this - temp;
        return temp;
    }
    Polynomial &operator%=(const Polynomial p) {
        if (koef.size() < p.koef.size()) {
            return *this;
        }
        Polynomial temp = *this;
        temp /= p;
        temp *= p;
        temp = *this - temp;
        *this = temp;
        return *this;
    }
};

#endif  // INCLUDE_POLYNOMIAL_HPP_