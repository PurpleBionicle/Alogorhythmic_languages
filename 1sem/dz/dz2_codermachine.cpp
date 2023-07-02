
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int main(int argc, const char* argv[]) {
    if (argc != 3) {
        cerr << "Error: Use three parameters\n";
        return 5;
    }

    const string mode(argv[1]); // Режим работы
    const string file_name(argv[2]); // Имя файла
    ofstream file; // ofstream предназначен для вывода или записи файлов.
    ifstream file1; //ifstream предназначен для ввода или чтения файлов.

    if (mode == "encryption")
    {
        string  text;
        int password;
        cout << "write text which we will encrypt:";
        getline(cin, text);
        if (text.size() % 2 != 0) { text.push_back(0u); }
        cout << endl << "write password key :";
        cin >> password;
        srand(password);
        //cout << "text.size()=" << text.size();// для проверки дозаписи нуля 

        const  char* data = text.data(); // разбитие на байты 


        std::vector<char> bytes(text.size());
        for (unsigned int i = 0; i < text.size(); i++) {
            bytes[i] = data[i];
        }
        // пробовал сразу char* назвать bytes  и без цикла этого
        //но тогда дальше не поулчается взять размер от него 



        file.open(file_name, ios::binary);
        for (unsigned int i = 0; i < bytes.size(); i += 2)
        {
            // unsigned int gamma = rand();
            unsigned char b1 = bytes[i];
            unsigned char b2 = bytes[i + 1];
 

         
            unsigned int chislo = (static_cast <unsigned int>  (b1) << 8u) | (static_cast <unsigned int> (b2));
           // cout << chislo; // proverka
            chislo = chislo ^ rand();// гаммирование
            int kray = chislo % 2; // иначе при сдвиге потеряется последний
            int predkray = (chislo % 4 - kray) / 2; //  остатком от 4 получим последнии два вычтем последний и
            // и теперь либо 00  либо 10 и возьмем целую часть от 2 >> либо 0 либо 1 соответственно
            chislo = chislo >> 2;
            chislo = (predkray * pow(2, 15)) + (kray * pow(2, 14)) + chislo; // крайний станет вторым, предкрай ( второй с конца ) первым



            //теперь осталось записать в файл
            
            char r1 = chislo >> 8;
            char r2 = chislo;
            file.write(&r1, sizeof(r1));
            file.write(&r2, sizeof(r2));
        }

        file.close();

    }
    
    else if (mode == "decryption")
    {
        int password2;
        cout << endl << "write password key :";
        cin >> password2;
        srand(password2);
        
        file1.open(file_name, std::ios::binary);

        std::vector<char> encryptbytes((std::istreambuf_iterator<char>(file1)),
            std::istreambuf_iterator<char>()); // зашифр байты 
        file1.close(); // забрали все из файла 

        cout << "kolvo bytes=" << encryptbytes.size() << endl; // проверка четности (для себя)

        std::vector<char> decryptbytes(encryptbytes.size());  //de..bytes расшифр 
        
        for (int i = 0; i < encryptbytes.size(); i += 2) {
            unsigned char b1 = encryptbytes [i];
            unsigned char b2 =  encryptbytes[i + 1] ;

            unsigned int chislo =
                ((static_cast<unsigned int>(b1) << 8u) | static_cast<unsigned int>(b2));

            int first = chislo / (int)pow(2, 15);
            int second = (int)(chislo / pow(2, 14)); // 2 первые получили при делении на 2^14  поэтому возьмем остаток 
            second = second % 2;
            chislo = chislo << 2; // справа 00 
            chislo = chislo + (first * 2) + second; // first станет вторым с конца поэтому на 2 умножение 


            chislo = chislo ^ rand();

          

            unsigned char r1 = chislo >> 8;
            unsigned char r2 = chislo;
            decryptbytes[i] = r1;
            decryptbytes[i + 1] = r2;
            

        }

        for (unsigned int i = 0; i < decryptbytes.size(); i++) 
        {
            std::cout << decryptbytes[i];
        }
    }

}