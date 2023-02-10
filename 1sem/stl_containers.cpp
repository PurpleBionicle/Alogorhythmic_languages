#include <header.hpp>
#include <vector>
#include <string>
#include <map>
#include <list>

std::vector<int>::iterator Find(std::vector<int>::iterator first,
                                std::vector<int>::iterator last, int el) {
    std::vector<int> v = {16, 17, 23, 56, 78, 90};
    auto it = first;  //= Find(first, last,el)
    while (it < last) {
        if (*it == el)  // ссылка на элемент
        {
            break;
        }
        ++it;
    }
    return it;
}

std::vector<int>::iterator findInSorted(std::vector<int>::iterator first,
                                        std::vector<int>::iterator last,
                                        int el) {
    auto it = first;  //= Find(first, last,el)
    while (it < last) {
        if (*it == el)  // ссылка на элемент
        {
            break;
        }
        ++it;
    }
    return it;
}

int wordsCounter(const std::string& str) {
    // будем все слова запоминать в вектор слов
    std::vector<std::string> words;               // push
    std::vector<char> unhappy = {' ', ',', '.'};  //разделители
    unsigned int k = 0;
    unsigned int count = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
        if ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
            (str[i] == unhappy[2]))  // нашли разделитель
        {
            if (str.substr(k, i - k).length() != 0)  // что не дошли до конца
            {
                count++;
            }
            k = i + 1;  // // тут i - индекс разделителя
            i++;        // переход с разделителя на след
            while ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
                   (str[i] == unhappy[2])) {
                k++;
                i++;
            }
        }
    }
    // теряю последнее слово
    if (str.substr(k, str.length() - k).length() != 0) count++;
    return count;
}

std::map<std::string, int> wordsMapCounter(const std::string &str) {
    // будем все слова запоминать в вектор слов
    std::vector<std::string> words;               // push
    std::vector<char> unhappy = {' ', ',', '.'};  //разделители
    std::map<std::string, int> word;
    unsigned int k = 0;  //  для индекса разделителя ласт
    for (unsigned int i = 0; i < str.length(); i++) {
        if ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
            (str[i] == unhappy[2]))  // нашли разделитель
        {
            if (str.substr(k, i - k).length() != 0)  // что не дошли до конца
            {
                words.push_back(str.substr(k, i - k));
            }
            k = i + 1;  // // тут i - индекс разделителя
            i++;        // переход с разделителя на след
            while ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
                   (str[i] == unhappy[2])) {
                k++;
                i++;
            }
        }
    }
    // теряю последнее слово
    if (str.substr(k, str.length() - k).length() != 0) {
        words.push_back(str.substr(k, str.length() - k));
    }
    std::vector<int> count;
    for (unsigned int r = 0; r < words.size(); r++) {
        int often = 1;
        for (unsigned int q = r; q < words.size(); q++) {
            if (words[r] == words[q] && r != q) {
                often++;
                words.erase(words.begin() + q);
                // q--;
            }
        }
        count.push_back(often);
    }
    for (unsigned int z = 0; z < words.size(); z++) {
        word.emplace(words[z], count[z]);
    }
    return word;
}

std::vector<std::string> uniqueWords(const std::string& str) {
    std::vector<std::string> uniq;                // push
    std::vector<char> unhappy = {' ', ',', '.'};  //разделители
    unsigned int k = 0;  //  для индекса разделителя ласт
    for (unsigned int i = 0; i < str.length(); i++) {
        if ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
            (str[i] == unhappy[2]))  // нашли разделитель
        {
            if (str.substr(k, i - k).length() != 0)  // что не дошли до конца
            {
                uniq.push_back(str.substr(k, i - k));
            }
            k = i + 1;  // // тут i - индекс разделителя
            i++;        // переход с разделителя на след
            while ((str[i] == unhappy[0]) || (str[i] == unhappy[1]) ||
                   (str[i] == unhappy[2])) {
                k++;
                i++;
            }
        }
    }
    // теряю последнее слово
    if (str.substr(k, str.length() - k).length() != 0) {
        uniq.push_back(str.substr(k, str.length() - k));
    }
    for (unsigned int r = 0; r < uniq.size(); r++) {
        int often = 1;
        for (unsigned int q = r; q < uniq.size(); q++) {
            if (uniq[r] == uniq[q] && r != q) {
                often++;
                uniq.erase(uniq.begin() + q);
                q--;
            }
        }
    }
    return uniq;
}  // от 4task  перебор + удалнение повторов

int diffWordsCounter(const std::string &str) {
    std::vector<std::string> uniq = uniqueWords(str);
    return uniq.size();
}

[[maybe_unused]] std::list<int> reverseNum(std::list<int> &l) {
    // emplace(pos, val)
    auto it = l.begin();  // iterator
    std::vector<int> v;
    while (it != l.end()) {
        if (*it != 0) {
            int d = -(*it);
            l.emplace(it, d);
        }
        it++;
    }
    return l;
}

std::vector<int> plusesDeleter(std::vector<int>& v) {
    //Реализуйте функцию, которая удалит все положительные числа.
    std::vector<int> v2;  // ego vernem
    for (unsigned int r = 0; r < v.size(); r++) {
        if (v[r] > 0) {
            v.erase(v.begin() + r);
            r--;
        }
    }
    return v;
}

std::list<int> Sort(
        std::list<int> &number) {  //Реализуйте функцию сортировки по убыванию.
    auto it = number.begin();    // iterator
    auto it2 = number.begin();   // iterator
    int tem;
    while (it != number.end()) {
        it2 = it;
        while (it2 != number.end()) {
            if (*it2 > *it) {
                tem = *it2;
                *it2 = *it;
                *it = tem;
            }
            if (it2 != number.end()) it2++;
        }
        it++;
    }
    return number;
}
