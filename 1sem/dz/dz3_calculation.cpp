#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Operation {
    int location; // место действия
    int priority; // приоритет по системе описанной в мейне
    char what_do; //      * or / or + or -
};

bool prior(Operation a, Operation b)//сортировка действий  по очереди выполнения
{
    if (a.priority != b.priority)
        return a.priority > b.priority; // true если приоритет больше
    else return a.location < b.location; // если стоит раньше
}

bool localsort(Operation a, Operation b) {
    return a.location < b.location;
}

double MULTI(double a, double b) { return a * b; }

double MINUS(double a, double b) { return a - b; }

double DEL(double a, double b) { return a / b; }

double PLUS(double a, double b) { return a + b; }

std::string rewrite(std::string& a) {
    std::string unar_minus = "0-";
    bool x_byl_yze = false;
    std::string x; //  x когда в строке
    for (unsigned int k = 0; k < a.size(); k++) {
        if (a[k] == 'x') {
            if (!x_byl_yze) {
                std::cout << "Введите x=";
                std::cin >> x;
            }
            x_byl_yze = true;
            std::string vremyanka = a.substr(k + 1, a.size() - k);
            a.insert(k, x);
            a.erase(k + x.size(), 1);// Удаление x
            std::cout << "Теперь выражение имеет вид :" << a << std::endl;
            k += x.size() - 1;
        }
        // унарный минус
        if (a[k] == '-' && (k == 0 || (a[k - 1] == '(' && k != a.size() - 1))) {
            a.erase(k, 1);
            a.insert(k, std::string("0-"));
            std::cout << "Теперь выражение имеет вид :" << a << std::endl;
        }

    }
    return a;
}

bool ERROR(std::string a)// для проверки ошибок
{
    int kolvo_open_skobok = 0;
    int kolvo_close_skobok = 0;
    for (unsigned int k = 0; k < a.size(); k++) {
        if (a[k] == 's' && k != a.size() - 2 && (a[k + 1] != 'i' || a[k + 2] != 'n'))
            return false; // Тут и след два ошибка в
        if (a[k] == 'c' && k != a.size() - 2 && (a[k + 1] != 'o' || a[k + 2] != 's')) return false;// правописании
        if (a[k] == 't' && k != a.size() - 1 && a[k + 1] != 'g') return false;
        if (a[k] == '/' && k != a.size() - 1 && a[k + 1] == '0') return false; // если деление на ноль
        if (a[k] == '(') kolvo_open_skobok++;
        if (a[k] == ')') kolvo_close_skobok++;
        if (a[k] == '(' && k != a.size() - 2 &&
            (a[k + 1] == '-' || a[k + 1] == '+' || a[k + 1] == '/' || a[k + 1] == '*'))
            return false; // что после скобки не идет действие
        // для унарного минуса не будет работать тк перезапишется к этому моменту в вид: 0-a
        if (a[k] == ')' && k != 0 && (a[k - 1] == '-' || a[k - 1] == '+' || a[k - 1] == '/' || a[k - 1] == '*'))
            return false; // что перед закрытием действие
        if (a[k] == '(' && k != a.size() - 2 &&
            (a[k + 1] == '-' || a[k + 1] == '+' || a[k + 1] == '/' || a[k + 1] == '*'))
            return false;
        if (a[k] == ')' && k != a.size() - 1 &&
            (a[k + 1] != '-' || a[k + 1] != '+' || a[k + 1] != '/' || a[k + 1] != '*'))
            return false;
    }
    if (kolvo_open_skobok != kolvo_close_skobok) return false;
    return true;
}

int main() {   // буду использовать систему приоритета
    // + - 0 баллов
    // * /  1 балл
    // () по 2 балла каждому действию внутри них
    // (())  4 балла (2+2) и тд
    setlocale(LC_ALL, "Russian");
    std::string expression;
    std::cout << "Калькулятор, можете посчитать такие результаты для операций : +-*/ ,а также унарный минус "
        << std::endl;
    std::cout << "Вещественные пишите через . " << std::endl;
    std::cout << "Напишите выражение: ";
    getline(std::cin, expression);
    rewrite(expression);
    int skobok_open = 0;
    if (!ERROR(expression)) {
        std::cerr << "ERROR";
    }
    else {
        std::vector<Operation> skobki;
        std::vector<char> operation = { '+', '-', '*', '/', '(', ')' };

        // формирую вектор операций по приоритетности
        std::vector<Operation> vec_priority;// вектор действий  сортированный по приоритетности
        for (unsigned int k = 0; k < expression.size(); k++) {
            if (expression[k] == '(') {
                skobok_open++;
                Operation w;
                w.location = k;
                w.what_do = operation[4];
                w.priority = -1; // ну просто чтобы были отличать
                vec_priority.push_back(w);
            }
            if (expression[k] == ')') {
                skobok_open--;
                Operation w;
                w.location = k;
                w.what_do = operation[5];
                w.priority = -1; // ну просто чтобы были отличать
                vec_priority.push_back(w);
            }
            for (unsigned int u = 0; u < operation.size() - 2; u++) { // тут не хочу скобки
                if (expression[k] == operation[u]) // рассматриваемый символ-это действие
                {
                    Operation e;
                    e.location = k;
                    if (u > 1)e.priority = 1 + 2 * skobok_open;//  * /
                    else e.priority = 0 + 2 * skobok_open;// + -
                    e.what_do = operation[u];
                    vec_priority.push_back(e);
                }
            }
        }
        sort(vec_priority.begin(), vec_priority.end(), prior);
        std::vector<Operation> vec_location = vec_priority; // вектор действий сортированный по позициям
        sort(vec_location.begin(), vec_location.end(), localsort);

        // разбиение на числа

        std::vector<double> chisla;
        for (unsigned int r = 0; r < vec_location.size(); r++) {
            std::string t;
            if (r != 0)  // я выделяю подстроки между действиями ,
                //а у первого с одной стороны нет действия
            {
                if (vec_location[r].location - vec_location[r - 1].location > 1) {
                    t = expression.substr(vec_location[r - 1].location + 1,
                        vec_location[r].location - vec_location[r - 1].location - 1);
                    chisla.push_back(stod(t));
                }
            }
            if (r == 0 && vec_location[0].what_do != '(') {
                t = expression.substr(0, vec_location[0].location);// c начала и до первого действия
                //cout << t << endl; проверки
                chisla.push_back(stod(t));
            } // часть строки перевел в число // уже в порядке в каком и стоят изначально
            if (r == vec_location.size() - 1 && vec_location[r].what_do != ')') {
                t = expression.substr(vec_location[r].location + 1);// C ПОЗИЦИИ след от ЛАСТА и ДО КОНЦА
                chisla.push_back(stod(t));
            }
        }
        // for (unsigned int z = 0; z < chisla.size(); z++) cout <<"now in int: "<< chisla[z] << endl;// проверки

        // удалим скобки из вектора действий , тк ниже действие каждое привязано по номеру к своей паре чисел ( по номер позиций )
        for (unsigned int o = 0; o < vec_location.size(); o++) {
            if (vec_location[o].what_do == ')') {
                vec_location.erase(vec_location.begin() + o);
                o--;
            }
            if (vec_location[o].what_do == '(') {
                vec_location.erase(vec_location.begin() + o);
                o--;
            }
        }
        for (unsigned int o = 0; o < vec_priority.size(); o++) {
            if (vec_priority[o].what_do == '(') {
                vec_priority.erase(vec_priority.begin() + o);
                o--;
            }
            if (vec_priority[o].what_do == ')') {
                vec_priority.erase(vec_priority.begin() + o);
                o--;
            }
        }

        // начинаем выполнять действия

        int er = 0; // переменная доп ошибки , когда деление на ноль оказалось после других действий
        while (!vec_priority.empty()) {
            unsigned int p = 0;
            for (unsigned int m = 0; m < vec_location.size(); m++) {
                if (vec_priority[p].location == vec_location[m].location) // для подбора чисел для операции
                {
                    switch (vec_priority[p].what_do) // надо отдельно для первого действия и ласт
                    {
                    case '*':
                        chisla[m] = MULTI(chisla[m],
                            chisla[m + 1]);  // 1 числу из пары присваиваем результат , второе удаляем
                        chisla.erase(chisla.begin() + m + 1);
                        vec_priority.erase(
                            vec_priority.begin() + p); // удаляем тут и в векторе по позициям это действие
                        vec_location.erase(vec_location.begin() + m);
                        break;
                    case '-':
                        chisla[m] = MINUS(chisla[m], chisla[m + 1]);
                        chisla.erase(chisla.begin() + m + 1);
                        vec_priority.erase(vec_priority.begin() + p);
                        vec_location.erase(vec_location.begin() + m);
                        break;
                    case '/':
                        if (chisla[m + 1] == 0) {
                            er++;
                            vec_priority.clear();
                        }
                        else {
                            chisla[m] = DEL(chisla[m],
                                chisla[m +
                                1]);  // 1 числу из пары присваиваем результат , второе удаляем
                            chisla.erase(chisla.begin() + m + 1);
                            vec_priority.erase(
                                vec_priority.begin() + p); // удаляем тут и в векторе по позициям это действие
                            vec_location.erase(vec_location.begin() + m);
                        }
                        break;
                    case '+':
                        chisla[m] = PLUS(chisla[m],
                            chisla[m + 1]);  // 1 числу из пары присваиваем результат , второе удаляем
                        chisla.erase(chisla.begin() + m + 1);
                        vec_priority.erase(
                            vec_priority.begin() + p); // удаляем тут и в векторе по позициям это действие
                        vec_location.erase(vec_location.begin() + m);
                        break;
                    }
                    if (vec_priority.empty() && er == 0)std::cout << "ОТВЕТ:" << chisla[m];// что последнее действие
                    if (er != 0) std::cerr << "ERROR нельзя на 0 делить ";
                    break;
                }
            }
        }
    }
}


