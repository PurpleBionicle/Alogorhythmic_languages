#include <algorithm>
#include <header.hpp>
bool namesort(Student s1, Student s2) { return s1.Name < s2.Name; }
void SortByName(std::vector<Student>& stud) {
    std::sort(stud.begin(), stud.end(), namesort);
}

bool ball(Student a, Student b) {
    unsigned int u = 0;
    unsigned int q = 0;
    for (unsigned int Rating : a.Ratings) {
        u += Rating;
    }
    for (unsigned int Rating : b.Ratings) {
        q += Rating;
    }
    return u > q;
}
void SortByRating(std::vector<Student>& points) {
    std::sort(points.begin(), points.end(), ball);
}

bool check(Student a) {
    for (unsigned int Rating : a.Ratings) {
        if (Rating == 2) {
            return true;
        }
    }
    return false;
}
size_t CountTwoness(const std::vector<Student>& dva) {  // двойка
    return std::count_if(dva.begin(), dva.end(), check);
}

bool chet(Student a) {
    for (unsigned int i = 0; i < a.Ratings.size(); i++) {
        if (a.Ratings[i] != 5) {
            return false;
        }
        if (i == a.Ratings.size() - 1 && a.Ratings[i] == 5) {
            return true;
        }
    }
    return false;
}
size_t CountExcellent(const std::vector<Student>& otlich) {
    return std::count_if(otlich.begin(), otlich.end(), chet);
}

std::vector<Student> VectorMathExcellent(
        const std::vector<Student>& math_y_studentov) {
    //создаст массив std::vector<Student>, в который войдут студенты имеющие
    //отметку отлично, по предмету "Math";
    std::vector<Student> v_math_5;
    for (const auto & i : math_y_studentov) {
        auto iter = std::find(i.Subjects.begin(),
                              i.Subjects.end(), "Math");
        if (iter != i.Subjects.end()) {
            for (unsigned int j = 0; j < i.Ratings.size(); j++) {
                if (i.Subjects[j] == "Math" &&
                    i.Ratings[j] == 5)
                    v_math_5.push_back(i);
            }
        }
    }
    return v_math_5;
}

std::vector<std::string> uniq_group;
bool uniqalnosti(const Student& a) {
    for (auto& i : uniq_group) {
        if (a.GroupId == i) return 1 < 0;
    }
    return a.GroupId != uniq_group[0];
}
std::vector<std::string> GroupsId(const std::vector<Student>& studenti) {
    Student a;
    uniq_group.clear();
    if (!studenti.empty()) uniq_group.push_back(studenti[0].GroupId);
    auto it = studenti.begin();
    while (it != studenti.end()) {
        if (std::find_if(it, studenti.end(), uniqalnosti) != studenti.end()) {
            a = *(std::find_if(it, studenti.end(), uniqalnosti));
            it = std::find_if(it, studenti.end(), uniqalnosti);
            uniq_group.push_back(a.GroupId);
        } else {
            break;
        }
    }
    return uniq_group;
}

bool name_group_sort(std::string c, std::string d) { return c < d; }
bool name_stud_sort(Student a, Student b) { return a.Name < b.Name; }
std::vector<Group> Groups(
        const std::vector<Student>&
        v_stud) {  //сформирует список групп, т.е. создаст массив структур Group
    std::vector<std::string> group_bez_stud;
    group_bez_stud = GroupsId(v_stud);
    std::sort(group_bez_stud.begin(), group_bez_stud.end(), name_group_sort);
    std::vector<Group> Groupi(group_bez_stud.size());
    for (unsigned int t = 0; t < group_bez_stud.size(); t++) {
        Groupi[t].Id = group_bez_stud[t];
    }
    //осталось добавить студентов
    for (unsigned int i = 0; i < v_stud.size(); i++) {
        auto iter = std::find(group_bez_stud.begin(), group_bez_stud.end(),
                              v_stud[i].GroupId);
        if (v_stud[i].GroupId == *iter) {
            Groupi[iter - group_bez_stud.begin()].Students.push_back(v_stud[i]);
        }
    }  // sort по именам
    for (unsigned int u = 0; u < Groupi.size(); ++u) {
        std::sort(Groupi[u].Students.begin(), Groupi[u].Students.end(),
                  name_stud_sort);
    }
    return Groupi;
}

