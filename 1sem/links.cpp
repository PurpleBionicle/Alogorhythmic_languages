
#include <vector>
#include <limits>
#include <iostream>
#include <string>

float mean(const std::vector<float> &a) {
    int count = 0;
    float sum = 0;
    for (unsigned int i = 0; i < a.size(); i++) {
        count++;
        sum += a[i];
    }
    return count > 0 ? (sum / count) : 0;
}

std::pair<float, float> minMax(const std::vector<float>& b) {
    if (b.empty()) {
        return std::make_pair(std::numeric_limits<float>::min(),
                              std::numeric_limits<float>::max());
    } else {
        float max = b[0];
        float min = b[0];
        for (unsigned int i = 0; i < b.size(); i++) {
            if (max < b[i]) max = b[i];
            if (min > b[i]) min = b[i];
        }
        return std::make_pair(min, max);
    }
}

float argmax(const std::vector<float> &c) {
    //индекс максимума
    if (c.empty()) {
        return -1;
    } else {
        float maxC = c[0];  // число макс
        //
        float max = 0;
        // индекс макса
        for (unsigned int i = 0; i < c.size(); i++) {
            if (c[i] > maxC) {
                max = i;
                maxC = c[i];
            }
        }
        return max;
    }
}

void sort(std::vector<float> &t4) {
    for (unsigned int i = 0; i < t4.size(); ++i)  //   методом пузырька
    {
        for (unsigned int k = i + 1; k < t4.size(); k++) {
            float tempor;
            if (t4[i] > t4[k]) {
                tempor = t4[k];
                t4[k] = t4[i];
                t4[i] = tempor;
            }
        }
    }
}

bool remove_first_negative_element(std::vector<int> &vec,
                                   int &removed_element) {
    removed_element = 0;
    int count = 0;  // счетчик
    for (unsigned int i = 0; i < vec.size(); i++) {
        if ((vec[i] < 0) && (count == 0)) {
            count++;
            removed_element = vec[i];

            vec.erase(vec.begin() + i);
        }
    }
    if (removed_element != 0) {
        return true;
    } else {
        return false;
    }
}

std::string replace(const std::string &str, const std::string &old,
                    const std::string &new_string) {
    std::string zamena = str;  // str менять нельзя тк конст
    int f = str.find(old);
    while (f != -1) {
        zamena.replace(f, new_string.length(), new_string);  // old.lenhgt
        f = zamena.find(old);
    }
    return zamena;
}

std::vector<std::string> split(const std::string &word, char sep) {
    std:: vector<std::string> s;  // сюда сплитуем //++
    std::string word2 = word;
    int k = word2.find(sep);
    while (k != -1 && word2.length() != 1) {
        std:: string nahodka = word2.substr(0, word2.find(sep));
        s.push_back(nahodka);  // теперь до нового  пробела ( или символа иного =sep
        // смотпя что в тестах) вернули в вектор стрингов
        word2.erase(0, nahodka.size() + 1);
        k = word2.find(sep);
    }
    if (!word.empty() &&
        word2[0] !=
        sep)  //!= для условия когда состоиt только из разделительного символа
    {  // приписывает последнюю часть строки
        s.push_back(word2);
    }

    return s;
}

std::string join(const std::vector<std::string> &party,
                 const std::string &sep) {
    std:: string t8;
    for (unsigned int i = 0; i < party.size(); i++) {
        t8 += party.at(i);
        t8 += sep;
    }
    t8.erase(t8.length() - sep.size());  // sep в конце убираем
    return t8;
}
