
#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_
#include <cmath>
#include <limits>
#include <type_traits>
template <typename T>
class Matrix {
private:
    unsigned int columns;  // count столбцов
    unsigned int str;      // kolvo strok
    T** Data;

public:
    ~Matrix() {
        for (size_t i = 0; i < str; i++) {
            delete[] Data[i];
        }
        delete[] Data;
    }

    Matrix() : columns(0), str(0), Data(nullptr) {}

    Matrix(int a, int b) {
        columns = b;
        str = a;
        Data = new T*[str];
        for (unsigned int i = 0; i < str; i++) {
            Data[i] = new T[columns];
        }
        for (unsigned int i = 0; i < str; i++) {
            for (unsigned int j = 0; j < columns; ++j) {
                Data[i][j] = 0;
            }
        }
    }

    Matrix(const Matrix& a) {
        columns = a.columns;
        str = a.str;
        Data = new T*[str];
        for (unsigned int i = 0; i < str; ++i) {
            Data[i] = new T[columns];
            for (unsigned int j = 0; j < columns; ++j) {
                Data[i][j] = a.Data[i][j];
            }
        }
    }

    T* operator[](size_t a) const { return Data[a]; }
    T* operator[](size_t a) { return Data[a]; }

    //// оператор присваивания
    Matrix& operator=(const Matrix& m) {
        columns = m.columns;
        str = m.str;
        Data = new T*[str];
        for (unsigned int i = 0; i < str; i++) {
            Data[i] = new T[columns];
            for (unsigned int j = 0; j < columns; j++) {
                Data[i][j] = m.Data[i][j];
            }
        }
        return *this;
    }
    bool operator==(const Matrix& a) const {
        bool flag = std::is_arithmetic<T>::value;
        if (columns != a.columns || a.str != str) {
            return false;
        }
        for (unsigned int i = 0; i < str; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                if (flag && (abs(Data[i][j] - a.Data[i][j]) >
                             std::numeric_limits<T>::epsilon()))
                    return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix& a) const {
        if (columns != a.columns || a.str != str) {
            return true;
        }
        bool flag = std::is_arithmetic<T>::value;
        for (unsigned int i = 0; i < str; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                if (!flag || (abs(Data[i][j] - a.Data[i][j]) <
                              2 * std::numeric_limits<T>::epsilon()))
                    return false;
            }
        }
        return true;
    }
    Matrix<T> operator+(const Matrix& a) const {
        if (columns == a.columns && str == a.str) {
            Matrix f(str, columns);
            for (unsigned int i = 0; i < str; ++i) {
                for (unsigned int j = 0; j < columns; ++j) {
                    f.Data[i][j] = Data[i][j] + a.Data[i][j];
                }
            }
            return f;
        }
        Matrix x;
        return x;
    }
    Matrix<T> operator-(const Matrix& a) const {
        if (columns == a.columns && str == a.str) {
            Matrix m(str, columns);
            for (unsigned int i = 0; i < str; ++i) {
                for (unsigned int j = 0; j < columns; ++j) {
                    m.Data[i][j] = Data[i][j] - a.Data[i][j];
                }
            }
            return m;
        }
        Matrix x;
        return x;
    }
    size_t Rows() { return str; }

    size_t Cols() { return columns; }

    Matrix<T> operator*(const Matrix& a) const {
        Matrix x;
        if (columns == a.str) {
            Matrix r(str, columns);
            for (unsigned int i = 0; i < str; i++) {
                for (unsigned int j = 0; j < a.columns; j++) {
                    r.Data[i][j] = 0;
                    for (unsigned int k = 0; k < columns; k++)
                        r.Data[i][j] += Data[i][k] * a.Data[k][j];
                }
            }
            return r;
        }
        return x;
    }
    Matrix<T> Inverse() {
        Matrix extend(str, 2 * columns);
        if (str == columns) {
            // перезапишем изначальную матрицу в первую половину расширенной
            for (unsigned int i = 0; i < str; ++i) {
                for (unsigned int j = 0; j < columns; ++j) {
                    extend.Data[i][j] = Data[i][j];
                }
            }
            // во вторую часть  единичную матрицу
            for (unsigned int i = 0; i < str; ++i) {
                extend.Data[i][str + i] = 1;
            }
            // если нулевой элемент на диагонали  то меняем строку с соседней
            for (unsigned int i = 0; i < extend.str; ++i) {
                if (extend.Data[i][i] == 0) {
                    for (unsigned int j = i; j < extend.str; ++j) {
                        if (extend.Data[j][i] != 0) {
                            T* sWap = extend.Data[j];
                            extend.Data[j] = extend.Data[i];
                            extend.Data[i] = sWap;
                            sWap = nullptr;
                        }
                    }
                }
            }
            // Метод Гаусса
            for (unsigned int i = 0; i < str; ++i) {
                // надо всю строку поделить на коэфф у диагонального элемента
                for (unsigned int g = 0; g < columns * 2; ++g) {
                    extend.Data[i][g] /= extend.Data[i][i];
                }
                // теперь в текущем столбце столбце сделать все нули кроме текущей
                for (unsigned int k = 0; k < str; ++k) {
                    if (k != i) {
                        double koef = extend.Data[k][i] / extend.Data[i][i];
                        for (unsigned int u = 0; u < 2 * columns; ++u) {
                            extend.Data[k][u] -= koef * extend.Data[i][u];
                        }
                    }
                }
            }
            // отщипываем правую часть расширенной
            Matrix reverse(str, columns);
            for (unsigned int i = 0; i < str; ++i) {
                for (unsigned int j = 0; j < columns; ++j) {
                    reverse.Data[i][j] = extend.Data[i][columns + j];
                }
            }
            return reverse;
        } else {
            // если неквадратная возвращаем пустую
            Matrix a;
            return a;
        }
    }
};

#endif  // INCLUDE_MATRIX_HPP_