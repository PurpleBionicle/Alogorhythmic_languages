#include <header.hpp>
#include <string>
#include <vector>
#include <algorithm>

void SortByName(std::vector<Student>& group) {
    for (unsigned int i = 0; i < group.size(); i++) {
        for (unsigned int j = i + 1; j < (group.size()); j++) {
            if (group[i].Name > group[j].Name) {
                Student t = group[i];
                group[i] = group[j];
                group[j] = t;
                // std::swap(group[i], group[j]);
            }
        }
    }
}

float mid(std::vector<unsigned int> marks) {
    float sum = 0.;  // почему-то когда инт сумма то тест валится
    for (unsigned int g = 0; g < marks.size(); g++) {
        sum += marks[g];
    }
    return (sum / marks.size());
}
void SortByRating(std::vector<Student>& list) {
    if (!list.empty()) {
        /// надо отсортировать структуры по средней оценке по убыванию
        /* std::vector<double> mid;  //вектор средних оценок
         for (unsigned int k = 0; k < list.size(); k++) {
           int sum = 0;
           for (int g = 0; g < list[k].Ratings.size(); g++) {
             sum += list[k].Ratings[g];
           }
           mid.push_back(sum / list[k].Ratings.size());
         }
     */
        ///не знаю почему не работает . ВОзможно из-за push_back .решил не через
        ///массив
        for (unsigned int i = 0; i < list.size() - 1; i++) {
            for (unsigned int j = i + 1; j < list.size(); j++) {
                if (mid(list[i].Ratings) < mid(list[j].Ratings)) {
                    Student vremynka = list[i];
                    list[i] = list[j];
                    list[j] = vremynka;
                }
            }
        }
    }
}

size_t CountTwoness(const std::vector<Student>& dvo) {
    int count = 0;
    int counthere = 0;
    for (unsigned int i = 0; i < dvo.size(); i++) {
        for (unsigned int g = 0; g < dvo[i].Ratings.size(); g++) {
            if (dvo[i].Ratings[g] == 2 && counthere == 0) {
                count++;
                counthere++;
            }
        }
        counthere = 0;
    }
    return count;
}

size_t CountExcellent(const std::vector<Student>& five) {
    int count = 0;
    unsigned int counthere = 0;
    for (unsigned int i = 0; i < five.size(); i++) {
        for (unsigned int g = 0; g < five[i].Ratings.size(); g++) {  // оценки
            if (five[i].Ratings[g] == 5) {
                counthere++;
            }
        }
        if (counthere == five[i].Ratings.size()) {
            count++;
            counthere = 0;
        }
    }

    return count;
}

// math prize
std::vector<Student> VectorMathExcellent(const std::vector<Student>& math) {
    std::vector<Student> v;
    for (unsigned int i = 0; i < math.size(); i++) {  // перебор структур
        for (unsigned int j = 0; j < math[i].Subjects.size(); j++) {
            if (math[i].Subjects[j] == "Math" && math[i].Ratings[j] == 5) {
                v.push_back(math[i]);
            }
        }
    }
    return v;
}

std::vector<std::string> GroupsId(const std::vector<Student>&imena){
    std::vector<std ::string> vec = {};
    unsigned int count = 0;
    for (unsigned int i = 0; i < imena.size(); i++)  // перебор структур
    {
        for (unsigned int j = 0; j < vec.size();
             j++)  // для массива  существующих групп
        {
            if (imena[i].GroupId != vec[j]) {
                count++;
            }  // count кол-во несовпадений с вектороом индивидуальных
        }
        if (count == vec.size()) {
            vec.push_back(imena[i].GroupId);
        }
        count = 0;
    }

    return vec;
}

std::vector<Group> Groups(
        const std::vector<Student>& ychen)  // вектор студентов с их оценками и тд
{
    std::vector<Group> grupi;
    std::vector<std::string> vec;  //вектор групп
    Group one;  // его пушать в вектор груп будем
    for (unsigned int e = 0; e < ychen.size(); e++) {
        if (find(vec.begin(), vec.end(), ychen[e].GroupId) == vec.end())
            vec.push_back(ychen[e].GroupId);
    }
    for (unsigned int i = 0; i < vec.size(); i++) {
        one = {};  // Без этой строки для новой группы эта структура студентов не
        // будет пустой
        //перебираем группы
        one.Id = vec[i];
        for (unsigned int l = 0; l < ychen.size(); ++l) {
            if (ychen[l].GroupId == one.Id) one.Students.push_back(ychen[l]);
        }  // проверяем всех студентов на принадлжежность для опр группы
        grupi.push_back(one);
    }
    return grupi;
}
