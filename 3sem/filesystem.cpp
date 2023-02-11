
#include "filesystem.hpp"

#include <header.hpp>

void printAccountsInfo(const bf::path &path_to_dir,
                       std::vector<Accounts> &acc) {
    for (const bf::directory_entry &obj :
            bf::recursive_directory_iterator(path_to_dir)) {
        if (is_regular_file(obj.path())) {
            std::string name = obj.path().stem().string();

            std::string number;
            std::string date;
            std::cmatch result;
            std::regex regular("([\\w]{8})([\\d]{8})(_)([\\d]{8})(.)([\\w]{3})");
            if (std::regex_match(name.c_str(), result, regular)) {
                number = result[2];
                date = result[4];
            }
            int repeat = -1;
            for (size_t i = 0; i < acc.size(); ++i) {
                if (acc[i].getNumber() == number) repeat = static_cast<int>(i);
            }

            if (std::regex_match(name.c_str(), result, regular)) {
                Accounts current_acc;
                current_acc.ChangeDate(date);
                std::cout << "broker:"
                          << obj.path().string().substr(
                                  0, obj.path().string().length() -
                                     obj.path().filename().string().length())
                          << " account:" + number + " files:" << acc[repeat].getCount()
                          << " lastdate:" + acc[repeat].getDate() + '\n';
            }
        }
    }
}

void printFinFile(const bf::path &p, std::vector<Accounts> &acc) {
    std::string name = p.stem().string();


    std::string number;
    std::string date;
    std::cmatch result;
    std::regex regular("([\\w]{8})([\\d]{8})(_)([\\d]{8})");
    //(.)([\\w]{3})");
    if (std::regex_match(name.c_str(), result, regular)) {
        number = result[2];
        date = result[4];
    }

    if (std::regex_match(name.c_str(), result, regular)) {
        std::cout << p.parent_path().string() + " " + p.filename().string() +
                     '\n';

        Accounts current_acc;
        int repeat = -1;
        for (size_t i = 0; i < acc.size(); ++i) {
            if (acc[i].getNumber() == number) repeat = static_cast<int>(i);
        }
        if (repeat == -1 || acc.empty()) {
            current_acc.ChangeNumber(number);
            current_acc.ChangeDate(date);
            current_acc.ChangeCount();
            acc.push_back(current_acc);
        } else {
            //такой есть
            acc[repeat].ChangeDate(date);
            acc[repeat].ChangeCount();
        }
    }
}


void analyse(const bf::path &p, std::vector<Accounts> &acc) {
    if (exists(p)) {
        if (is_regular_file(p)) {
            printFinFile(p, acc);
        } else if (is_directory(p)) {
            std::cout << "\n" << p << " is a directory containing:\n";
        } else if (is_symlink(p)) {
            bf::path symlinkPath = read_symlink(p);
            analyse(symlinkPath, acc);
        }
    }
}

void iterate(const bf::path &pathToDir) {
    std::vector<Accounts> accounts1;
    for (bf::directory_entry &obj : bf::recursive_directory_iterator(pathToDir)) {
        analyse(obj.path(), accounts1);
    }
    printAccountsInfo(pathToDir, accounts1);
}