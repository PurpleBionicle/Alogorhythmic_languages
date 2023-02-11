#include <header.hpp>
#include <string>
#include <vector>
#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_
struct Student {
    std::string name;
    std::any group;
    std::any avg;
    std::any debt;
};

auto get_name(const json& j) -> std::string { return j.get<std::string>(); }

auto get_debt(const json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_array())
        return j.get<std::vector<std::string>>();
    else
        throw std::invalid_argument("items is not array");
}

auto get_avg(const json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number_float())
        return j.get<double>();
    else if (j.is_number())
        return j.get<std::size_t>();
    else
        throw std::invalid_argument("items is not array");
}

auto get_group(const json& j) -> std::any {
    if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number())
        return j.get<std::size_t>();
    else
        throw std::invalid_argument("items is not array");
}

void from_json(const json& j, Student& s) {
    s.name = get_name(j.at("name"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = get_debt(j.at("debt"));
}

int size_group(const Student& student) {
    int size;
    if (student.group.type() == typeid(std::nullptr_t)) {
        size = 4;  // strlen("null")=4
    } else if (student.group.type() == typeid(std::string) ||
               student.group.type() == typeid(char)) {
        size = std::any_cast<std::string>(student.group).length();
    } else {
        size = std::to_string(std::any_cast<size_t>(student.group)).length();
    }

    return size;
}

int size_avg(const Student& student) {
    int size;

    if (student.avg.type() == typeid(std::nullptr_t)) {
        size = 4;  // strlen("null")=4
    } else if (student.avg.type() == typeid(std::string)) {
        size = std::any_cast<std::string>(student.avg).length();
    } else if (student.avg.type() == typeid(double)) {
        double a = std::any_cast<double>(student.avg);
        size = std::to_string(static_cast<int>(a)).length() + 3;
    } else {
        size = std::to_string(std::any_cast<size_t>(student.avg)).length();
    }
    return size;
}

int size_debt(const Student& student) {
    int size;
    if (student.debt.type() == typeid(std::nullptr_t)) {
        size = 4;  // strlen("null")=4
    } else if (student.debt.type() == typeid(std::string) ||
               student.debt.type() == typeid(char)) {
        size = std::any_cast<std::string>(student.debt).length();
    } else {
        size = std::to_string(
                std::any_cast<std::vector<std::string>>(student.debt).size())
                       .length() +
               6;  //" items" =6
    }
    return size;
}

std::vector<int> find_sep(const Student& student) {
    // "| name          | group  | avg  | debt          |"
    std::vector<int> sep;  // сепараторы |
    sep.push_back(0);
    sep.push_back(sep[0] + student.name.length() +
                  3);  // +3 - 2 пробела в начале + сам сепаратор

    sep.push_back(sep[1] + 3 + size_group(student));
    sep.push_back(sep[2] + 3 + size_avg(student));
    sep.push_back(sep[3] + 3 + size_debt(student));
    return sep;
}
void make_line(std::vector<int> sep, std::ostream& os) {
    //|---------------|--------|------|---------------|
    int k = 0;
    for (int i = 0; i < sep.back(); ++i) {
        if (i == sep[k]) {
            os << "|";
            ++k;
        } else {
            os << "-";
        }
    }
    os << "|" << std::endl;
}

void make_title(std::vector<int> sep, std::ostream& os) {
    //| name          | group  | avg  | debt          |
    int j = 0;
    for (int i = 0; i < sep.back(); ++i) {
        if (i == sep[j]) {
            os << "|";
            ++j;
        } else {
            if (i >= sep[0] + 2 && i <= sep[0] + 5) {
                os << "name";
                i += 4;
            }
            if (i >= sep[1] + 2 && i <= sep[1] + 6) {
                os << "group";
                i += 5;
            }
            if (i >= sep[2] + 2 && i <= sep[2] + 4) {
                os << "avg";
                i += 3;
            }
            if (i >= sep[3] + 2 && i <= sep[3] + 5) {
                os << "debt";
                i += 4;
            }
            os << " ";
        }
    }
    os << "|" << std::endl;
    make_line(sep, std::cout);
}

void make_void_line(const int sep, const int last_sep, std::ostream& os,
                    const int size) {
    for (int t = 0; t < sep - last_sep - 2 - size; ++t) {
        os << " ";
    }
    os << "|";
}

void print(const Student& student, std::ostream& os, std::vector<int> sep) {
    os << "| " << student.name;
    make_void_line(sep[1], sep[0], os, student.name.length());
    if (student.group.type() == typeid(std::nullptr_t)) {
        os << " null";
    } else if (student.group.type() == typeid(std::string) ||
               student.group.type() == typeid(char)) {
        os << " " << std::any_cast<std::string>(student.group);
    } else {
        os << " " << std::any_cast<size_t>(student.group);
    }
    make_void_line(sep[2], sep[1], os, size_group(student));

    if (student.avg.type() == typeid(std::nullptr_t)) {
        os << " null ";
    } else if (student.avg.type() == typeid(std::string)) {
        os << " " << std::any_cast<std::string>(student.avg);
    } else if (student.avg.type() == typeid(double)) {
        os << " " << std::any_cast<double>(student.avg);
    } else {
        os << " " << std::any_cast<size_t>(student.avg);
    }
    make_void_line(sep[3], sep[2], os, size_avg(student));

    if (student.debt.type() == typeid(std::nullptr_t)) {
        os << " null";
    } else if (student.debt.type() == typeid(std::string)) {
        os << " " << std::any_cast<std::string>(student.debt);
    } else {
        os << " " << std::any_cast<std::vector<std::string>>(student.debt).size()
                                                          << " items";
    }
    make_void_line(sep[4], sep[3], os, size_debt(student));
    os << std::endl;
    make_line(sep, std::cout);
}

void print(const std::vector<Student>& students, std::ostream& os,
           const std::vector<int>& sep) {
    for (auto const& student : students) {
        print(student, os, sep);
    }
}

int meta_check(const std::vector<Student>& students, const json& data) {
    size_t count;
    count = data.at("_meta").at("count");
    if (count != students.size()) {
        throw std::invalid_argument("_meta.count != len(items)");
    }
    return count;
}

// bool file_check(const std::string& a) {
//   std::ifstream file{a};
//   if (!file) {
//     throw std::runtime_error{"unable to open json:" + a};
//   }
//   return true;
// }

#endif  // INCLUDE_STUDENT_HPP_