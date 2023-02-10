#include <fstream>
#include <header.hpp>
#include <string>
#include <vector>
void saveToFile(const std::string& filename,
                const std::vector<std::string>& data) {
    std::ofstream file;
    file.open(filename);
    if (file.is_open()) {
        for (const auto& i : data) {
            file << i << std::endl;
        }
    }
    file.close();
}
void loadFromFile(const std::string& filename,
                  std::vector<std::string>& outData) {
    outData.clear();  //чтобы убрать мусор
    std::fstream file1;
    file1.open(filename);
    if (file1.is_open()) {
        std::string w;
        while (getline(file1, w))  // 2 parametr куда извлекаем
        {
            outData.push_back(w);
        }
    }
    file1.close();
}

void saveToFile(const std::string& filename, const std::vector<Book>& data) {
    std::ofstream file;
    file.open(filename);
    for (unsigned int i = 0; i < data.size(); i++) {
        if (file.is_open()) {
            file << data[i].Author << std::endl;
            file << data[i].Title << std::endl;
            if (i != data.size() - 1)
                file << data[i].Year << std::endl;
            else
                file << data[i].Year;  // иначе  в конце пустая строка и он думает что
            // не дошел до конца
        }
    }
    file.close();
}
void loadFromFile(const std::string& filename, std::vector<Book>& outData) {
    outData.clear();
    std::ifstream file1;
    file1.open(filename);
    Book temp;
    std::string author;
    std::string title;
    std::string year;
    if (file1.is_open()) {
        while (!file1.eof()) {
            getline(file1, author);
            getline(file1, title);
            getline(file1, year);  /// Почему-то не дает инт взять из файла и чар
            int y = std::stoi(year);
            outData.push_back(Book{author, title, y});  // ???????
        }
    }
    file1.close();
}

void saveToFile(const std::string& filename, const Groups& groups) {
    std::ofstream file;
    file.open(filename);
    // КОЛВО групп >> название >> колво студентов >> колво оценок >> тип >> result
    if (file.is_open()) {  // итераторы для мар
        file << groups.size() << std::endl;
        auto groupIter = groups.begin();
        while (groupIter != groups.end()) {  // внутри группы
            file << groupIter->first << std::endl;  // через точку не дает ?
            file << groupIter->second.size() << std::endl;  //скок учеников
            for (unsigned int i = 0; i < groupIter->second.size(); i++) {
                Student chel = groupIter->second[i];
                file << chel.Name << std::endl;
                file << chel.Year << std::endl;
                file << chel.RecordBook.size() << std::endl;  // колво оценок
                auto markIter = chel.RecordBook.begin();
                // auto markIter= groupIter->second.at(i).RecordBook.begin();// для себя
                // )-) думал не вводить новые переменные  но очень длинные уж
                // поулчачются
                for (; markIter != chel.RecordBook.end(); ++markIter) {
                    //перебор оценок
                    file << markIter->first << std::endl;
                    file << markIter->second << std::endl;
                }
            }
            ++groupIter;
        }
    }
    file.close();
}
void loadFromFile(const std::string& filename, Groups& outGroups) {
    std::vector<Student> student;
    std::ifstream file;
    file.open(filename);
    outGroups.clear();  // от мусора
    // КОЛВО групп >> название >> колво студентов >> колво оценок >> тип >> result
    if (file.is_open()) {
        std::string kolvogroup;
        file >> kolvogroup;
        std::string group_name;
        for ( int i = 0; i < stoi(kolvogroup);
              i++) {  //внутри группы // i-1 номер группы
            student.clear();
            file >> group_name;
            unsigned int kolvostudentov;
            file >> kolvostudentov;
            for (unsigned int j = 0; j < kolvostudentov; j++) {
                std::string name_of_student;  // of student
                file >> name_of_student;
                int year;
                file >> year;
                std::map<std::string, Score> result;
                unsigned int count_of_marks;
                file >> count_of_marks;
                for (unsigned k = 0; k < count_of_marks; k++) {  // перебор оценок
                    std::string type_of_marks;
                    file >> type_of_marks;
                    int mark;
                    file >> mark;
                    result[type_of_marks] = static_cast<Score>(mark);
                }
                student.push_back(Student{name_of_student, year, result});
            }
            outGroups.emplace(group_name, student);
        }
    }
    file.close();
}
