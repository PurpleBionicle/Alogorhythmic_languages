#ifndef INCLUDE_STRING_HPP_
#define INCLUDE_STRING_HPP_

#include <utility>
#include <iostream>
#include <cstring>

int Strlen(const char* a) {
    int length = 0;
    while (a[length] != '\0') length++;
    return length;
}

class String {
public:
    /// Деструктор
    ~String() { delete[] Data; }

    /// Конструктор по умолчанию
    String() : Data(nullptr) { std::cout << "standart constructor\n"; }

    ///Конструктор копирования
    ///< param name="rhs"> Объект, который копируем </param>
    String(const String& rhs) {
        std::cout << "copy constructor \n";
        unsigned int length = Strlen(rhs.Data);
        Data = new char[length + 1];
        memcpy(Data, rhs.Data, length);
        Data[length] = '\0';
    }

    /// Пользовательский конструктор
    /*<param name="data"> Данные, которые требуется поместить в создаваемый
     объект </param>*/
    explicit String(const char* data) {
        std::cout << "user constructor\n";
        unsigned int length = Strlen(data);
        Data = new char[length + 1];
        for (unsigned int j = 0; j < length; ++j) {
            Data[j] = data[j];
        }
        this->Data[length] = '\0';
    }

    /// Оператор присваивания
    /* <param name="data">Объект, который копируем </param>
       <returns>Возвращаем ссылку на себя</returns>*/
    String& operator=(const String& rhs) {
        if (this != &rhs) {
            unsigned int length = Strlen(rhs.Data);
            //осталось перезаписать строку
            Data = new char[length + 1];
            memcpy(Data, rhs.Data, length);
            Data[length] = '\0';
        }
        return *this;
    }

    /// Оператор +=
    /// <param name="rhs">Объект, который стоит после знака '+=' </param>
    /// <returns>Возвращаем ссылку на себя</returns>
    String& operator+=(const String& rhs) {
        int length_data = Strlen(Data);
        int length_rhs = Strlen(rhs.Data);
        char* a = new char[length_data + length_rhs + 1];
        for (int i = 0; i < length_data; i++) {
            a[i] = Data[i];
        }
        for (int j = 0; j < length_rhs; j++) {
            a[length_data + j] = rhs.Data[j];
        }
        delete[] Data;
        Data = new char[length_data + length_rhs + 1];
        for (int h = 0; h < length_data + length_rhs; h++) {
            Data[h] = a[h];
        }
        delete[] a;
        Data[length_data + length_rhs] = '\0';
        return *this;
    }

    /// Оператор *=
    /// <returns> Возвращаем ссылку на себя </returns>
    String& operator*=(unsigned int m) {
        unsigned int length_data = strlen(Data);
        char* a = new char[length_data * m + 1];
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < length_data; ++j) {
                a[i * length_data + j] = Data[j];
            }
        }
        delete[] Data;
        Data = new char[length_data * m + 1];
        for (unsigned int h = 0; h < length_data * m; h++) {
            Data[h] = a[h];
        }
        delete[] a;
        Data[length_data * m] = '\0';
        return *this;
    }

    /// Оператор ==
    /* <param name="rhs"> Объект, который стоит после знака '=='  </param>
    /// <returns> Возвращаем значения равенства двух строк </returns>*/
    bool operator==(const String& rhs) const {
        if (strlen(rhs.Data) != strlen(this->Data)) {
            return false;
        } else {
            for (unsigned int i = 0; i < strlen(rhs.Data); ++i) {
                if (rhs.Data[i] != this->Data[i]) return false;
            }
        }
        return true;
    }

    /// Оператор &lt;
    /* <param name="rhs">Объект, который стоит после знака "&lt;" </param>
    /// <returns>Возвращаем значения сравнения двух строк</returns>*/
    bool operator<(const String& rhs) const {
        int min_length = strlen(Data) <= strlen(rhs.Data) ? strlen(this->Data)
                                                          : strlen(rhs.Data);
        if (min_length == Strlen(Data) && min_length == Strlen(rhs.Data))
            return false;
        for (int i = 0; i < min_length; ++i) {
            if (Data[i] > rhs.Data[i]) return false;
            if (Data[i] < rhs.Data[i]) return true;
        }
        //если дошли до конца одного из слов ,то оно и будет меньше
        if (min_length == Strlen(Data)) return true;
        return false;
    }

    /// Функция поиска подстроки
    /* <param name="substr">Подстрока, которую необходимо найти </param>
    /// <returns>Возвращаем позицию substr. Если подстрока не найдена, то
    /// возвратить -1</returns> */
    size_t Find(const String& substr) const {
        // возвращает первый индекс подстроки или -1
        for (int i = 0; i < Strlen(Data); ++i) {
            int j = 0;
            while (Data[i] == substr.Data[j] && i < Strlen(Data)) {
                j++;
                i++;
            }
            int sub_strlen = strlen(substr.Data);
            if (sub_strlen > 0) {
                if (j == sub_strlen) return i - sub_strlen;
            } else {
                return i - sub_strlen;
            }
        }
        return -1;
    }

    /// Функция замены символов, заменяет все символы oldSymbol на newSymbol.
    /* <param name="oldSymbol">Символ, который требуется заменить </param>
    /// <param name="newSymbol">Символ, на который требуется заменить </param>*/
    void Replace(char oldSymbol, char newSymbol) {
        for (int i = 0; i < Strlen(Data); ++i) {
            if (Data[i] == oldSymbol) Data[i] = newSymbol;
        }
    }

    /// Функция возвращает длину строки
    /// <returns>Возвращаем длину строки</returns>
    size_t Size() const { return Strlen(Data); }

    /// Функция для определения пуста ли строка
    bool Empty() const {
        if (Data == nullptr)
            return true;
        else
            return false;
    }
    /// Оператор []
    /* <example>
    /// <code>
    /// String str = "some string";
    /// char symbol = str[2]; // symbol == 'm'
    /// </code>
    /// </example>
    /// <param name="index"> Индекс символа </param>
    /// <returns> Значение символа в строке с индексом index</returns>*/
    char operator[](size_t index) const { return Data[index]; }

    /// Оператор []
    /* <example>
    /// <code>
    /// String str = "some string";
    /// str[0] = 'S'; // теперь переменная str равна "Some string"
    /// </code>
    /// </example>
    /// <param name="index"> Индекс символа </param>
    /// <returns> Ссылка на символ в строке с индексом index</returns>*/
    char& operator[](size_t index) { return Data[index]; }

    /// Смотри пример
    /* <example>
    /// <code>
    /// String str = "___some string___";
    /// str.RTrim('_'); // теперь переменная str равна "___some string"
    /// </code>
    /// </example>
    /// <param name="symbol"> Значение символов, которе отрезаем </param>*/
    void RTrim(char symbol) {
        int length = Strlen(Data);
        for (int i = length; i > 0; --i) {
            while (Data[i] == symbol) {
                Data[i] = '\0';
            }
        }
    }

    /// Смотри пример
    /* <example>
    /// <code>
    /// String str = "___some string___";
    /// str.LTrim('_'); // теперь переменная str равна "some string___"
    /// </code>
    /// </example>
    /// <param name="symbol"> Значение символов, которе отрезаем </param>*/
    void LTrim(char symbol) {
        int length = Strlen(Data);
        int i = 0;
        while (Data[i] == symbol) {
            char* a = new char[length];  // без первого
            for (int j = 1; j < length; ++j) {
                a[j - 1] = Data[j];
            }
            a[length - 1] = '\0';
            delete[] Data;
            Data = new char[Strlen(a) + 1];
            for (int k = 0; k < Strlen(a); ++k) {
                Data[k] = a[k];
            }
            Data[Strlen(a)] = '\0';
            delete[] a;
        }
    }

    void swap(String& oth) {
        int length_data = Strlen(Data);
        int length_oth = Strlen(oth.Data);
        char* a = new char[length_data + 1];
        for (int i = 0; i < length_data; i++) {
            a[i] = Data[i];
        }
        delete[] Data;
        Data = new char[length_oth + 1];
        for (int i = 0; i < length_oth; ++i) {
            Data[i] = oth.Data[i];
        }
        Data[length_oth] = '\0';
        delete[] oth.Data;
        oth.Data = new char[length_data + 1];
        for (int i = 0; i < length_data; ++i) {
            oth.Data[i] = a[i];
        }
        oth.Data[length_data] = '\0';
        delete[] a;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str);

private:
    char* Data;
};

/// Оператор +
/* <example>
/// <code>
/// String a = "Hello";
/// String b = "World";
/// String c = a + b; // c равна "HelloWorld"
/// </code>
/// </example>
/// <returns>Возвращаем строку равную a + b</returns>*/
String operator+(const String& a, const String& b) {
    String c;
    c = a;
    c += b;
    return c;
}

/// Оператор *
/* <example>
/// <code>
/// String a = "A";
/// String c = a * 5; // c равна "AAAAA"
/// </code>
/// </example>*/
String operator*(const String& a, unsigned int b) {
    String c;
    c = a;
    c *= b;
    return c;
}

/// Оператор !=
bool operator!=(const String& a, const String& b) {
    if (a == b) {
        return false;
    }
    return true;
}

/// Оператор &gt;
bool operator>(const String& a, const String& b) {
    if (a < b || a == b) return false;
    return true;
}

/// Оператор вывода
/*<param name="out">Поток куда выводим строку </param>
// <param name="str">Строка, которую выводим </param>
 //<returns>Возвращаем ссылку на поток</returns>*/
std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.Data;
    return out;
}

#endif  // INCLUDE_STRING_HPP_