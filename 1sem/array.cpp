#include <tasks.hpp>
#include <vector>
#include <iostream>
#include <string>
//#include "tasks.hpp"
// task1

void multi_2(std::vector<int> &input) {
    for (unsigned int i = 0; i < input.size(); i++) {
        input.at(i) *= 2;
    }
}

void reduce_a(std::vector<int> &input, int a) {
    for (unsigned int i = 0; i < input.size(); i++) {
        input[i] -= a;
    }
}

void div_on_first(std::vector<int> &v) {
    for (int i = v.size() - 1; i >= 0; --i) {
        v.at(i) /= v[0];
    }
}

// Task 2.
int sum(const std::vector<int> &input) {
    int SUMMA = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        SUMMA += input[i];
    }
    return SUMMA;
}

int square_sum(const std::vector<int> &input) {
    int sumsquare = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        sumsquare += (input[i]) * (input[i]);
    }
    return sumsquare;
}

int sum_six(const std::vector<int> &input) {
    int sum6 = 0;
    for (int i = 0; i < 6; i++) {
        sum6 += input[i];
    }
    return sum6;
}

int sum_k(const std::vector<int> &input, int k1, int k2) {
    int sumk = 0;
    if (k2 >= k1) {
        for (int i = k1; i < k2 + 1; i++) {
            sumk += input[i];
        }
        return sumk;
    } else {
        std::cout << "incorrect vvod";
        return sumk = 0;
    }
}

int mean(const std::vector<int> &input) {
    double sredn;
    int summm = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        summm += input[i];
    }
    sredn = summm / input.size();
    return sredn;
}

int mean_k(const std::vector<int> &input, unsigned int s1, unsigned int s2) {
    int summss = 0;
    double srednee;
    if (s2 >= s1) {
        for (unsigned int i = s1; i <= s2; i++) {
            summss += input[i];
        }
        if (s1 != s2) {
            srednee = summss / (s2 - s1 + 1);
        } else {
            srednee = summss;
        }
        return srednee;
    } else {
        std::cout << "incorrect vvod";
        return srednee = 0;
    }
}

// task3

void swap_el(std::vector<int> &input) {
    int a1, a2, a3;

    a1 = input[0];
    a2 = input[1];
    a3 = input[2];
    input[0] = input[17];
    input[1] = input[18];
    input[2] = input[19];
    input[17] = a1;
    input[18] = a2;
    input[19] = a3;
}


// Task 4.
void remove_negative(std::vector<int> &input) {
    unsigned int j = 0;
    int count = 0;  // счетчик отриц , удалять только первый будем
    for (unsigned int i = 0; i < input.size(); i++) {
        if ((input[i] < 0) && (count == 0)) {
            count++;  // то есть выполнится для одного отрицательного
            j = i;
        }
    }
    if (j == 0 && input[0] < 0) {
        input.erase(input.begin() + j);
    }
    if (j != 0) {
        input.erase(input.begin() + j);
    }
}

void remove_last_even(std::vector<int> &input) {
    unsigned int h = 0;
    for (unsigned int i = 0; i < input.size(); i++) {
        if ((input[i] % 2 == 0)) {
            h = i;
        }
    }
    if (h == 0 && input[0] % 2 == 0) {
        input.erase(input.begin() + h);
    }
    if (h != 0) {
        input.erase(input.begin() + h);
    }
}

// task5

bool name_is_even(const std::string &name) {
    if (name.length() % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

// Task 6.
bool first_is_longer(const std::string &name_one, const std::string &name_two) {
    std::cout << std::endl;
    if (name_two.length() < name_one.length()) {
        return true;
    } else {
        return false;
    }
}

// Task 7.
void longest_shortest(const std::string &name_one, const std::string &name_two,
                      const std::string &name_three, std::string &the_longest,
                      std::string &the_shortest) {
    if (name_one.length() > name_two.length()) {
        // 1>2
        if (name_one.length() > name_three.length())
            the_longest = name_one;
        else
            the_longest = name_three;  // 1>3
        if (name_two.length() > name_three.length())
            the_shortest = name_three;
        else
            the_shortest = name_two;
    } else {
        // 2>1
        if (name_two.length() > name_three.length())
            the_longest = name_two;
        else
            the_longest = name_three;
        if (name_one.length() > name_three.length())
            the_shortest = name_three;
        else
            the_shortest = name_one;
    }
}

// Task 8.
std::string sub_str(const std::string &word, int m, int n) {
    std::string g = "";
    if (n >= 0 && m >= 0) {
        return word.substr(m, n - m + 1);
    } else {
        return g;
    }
}

// Task 9.

void add_stars(std::string &word) {
    std::string word2 = word;
    word.insert(word.begin(), word.size(), '*');
    word.insert(word.end(), word2.size(), '*');
}

// Task 10.
int percent_of_a(const std::string &word) {
    double chasti;
    double counta = 0;  // kolvo букв а
    for (unsigned int i = 0; i < word.length(); i++) {
        if (word[i] == 'a') {
            counta++;
        }
    }
    chasti = counta / word.length();
    chasti *= 100;
    return chasti;
}

// Task 11.
std::string replace_can(const std::string &new_word) {
    std::string sentense = "Can you can a can as a canner can can a can?";

    for (unsigned int i = 0; i < sentense.length(); i++) {
        if (sentense[i] == 'c' && sentense[i + 1] == 'a' &&
            sentense[i + 2] == 'n') {
            sentense.erase(i, 3);
            sentense.insert(i, new_word);
        }
    }
    return sentense;
}
