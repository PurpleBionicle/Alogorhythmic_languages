// labo1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cmath>
#define _USE_MATH_DEFINES
using namespace std;

void task1234()
{
    cout << "1 13 49" << endl;
    char r;
    cin >> r;
    cout << "1" << r << "13" << r << "49" << r << endl;
    cout << "14  23  56" << endl;
    double a, x;
    cin >> a;
    x = 12 * a * (a)+7 * a - 12;
    cout << x << endl;
    cin >> x;
    double y;
    y = x * x * x * 3 + 4 * x * x - 11 * x + 1;
    cout << y << endl;
}
void task1()
{
    double plot,massa,V;
    cout << "massa=";
    cin >> massa;
    cout << endl;
    cout << "V=";
    cin >> V;
    cout << endl;
    plot = massa / V;
    cout << "plotnost="<<plot<<endl;
}
void task2() {
    double a, x, b;
    cout << "a=";
    cin >> a;
    cout << endl;
    cout << "b=";
    cin >> b;
    cout << endl;
    x = -b / a;
    cout << "x=" << x << endl;
}
void task3() {
    double x1, x2, y1, y2;
    double rasst;
    cout << "koordinat 1 tochki=";
    cin >> x1;
    cin >> y1;
    cout << "koordinat 2 tochki=";
    cin >> x2;
    cin >> y2;
    rasst =sqrt ( (abs(x1 - x2)) * (abs(x1 - x2)) + (abs(y1 - y2)) * (abs(y1 - y2)) ) ;
    cout << "rasst=" << rasst;
}
void task4() {
    double h, osn1,osn2;
    cout << "h=";
    cin >> h;
    cout << endl;
    cout << "osnovanie1=";
    cin >> osn1;
    cout << endl;
    cout << "osnovanie2=";
    cin >> osn2;
    cout << endl;
    double bok, perimtr;
    bok = sqrt(abs(osn1 - osn2) * abs(osn1 - osn2)+h*h        );
    perimtr = osn1 + osn2 + 2 * bok;
    cout << "perimetr=" << perimtr << endl;
}
void task5() {
    double ploshring; // площадь кольца
    double vnutrring, vneshring;// внеш и внутр радиусы
    cout << "vnutrennee=";
    cin >> vnutrring;
    cout << endl;
    cout << "vnesh=";
    cin >> vneshring;
    cout << endl;
    if (vneshring>vnutrring)
    { // M_PI не работает почему-то
        ploshring = 3.14 * (vneshring * vneshring - vnutrring * vnutrring);
        cout << ploshring << endl;
    }
    else { cout << " incorect vvod " << endl; }
}
void task6() {
    double rebro, V, Spoverh;
    cout << "rebro=";
    cin >>rebro ;
    cout << endl;
    V = rebro * rebro * rebro;
    Spoverh = 6 * rebro * rebro;
    cout << "V=" << V << endl;
    cout << "Spoverh=" << Spoverh << endl;

}
void task7() {
    double s, per;
    cout << "storona kvadrata=";
    cin >> s;
    cout << endl;
    per = 4 * s;
    cout << "perimetr=" << per<<endl;

}
void task8() {
    double rad, diam;
    cout << "radiys=";
    cin >> rad;
    cout << endl;
    diam = 2 * rad;
    cout << "diametr=" << diam<< endl;
}
void task9(){
    string name;
    cout << "WHATS U NAME=";
    cin >> name;
    cout << endl;
    cout << "HEllo " << name << "!My name is c++";
}
void task10() {
    string word;
    cout << "word=";
    cin >> word;
    cout << endl;
    int count = 0; // счетчик совпадений
    if (word.length() % 2 == 0)
    {
        for (int i = 0; i < word.length() / 2; i++) {
            if (word[i] == word[word.length() - i - 1]) {
                count++;
            }
        }
    }
    else
    {
        for (int i = 0; i < (word.length() / 2); i++) {
            if (word[i] == word[word.length() - i - 1]) {
                count++;
            }
        }
    }

    if (word.length() % 2 == 0)
    {

        if (count == word.length() / 2 ) { cout << "its polyndrom" << endl; }
        else { cout << "its NOT polyndrom" << endl; }
    }
    else {
        if (count > (word.length() /2) -1) { cout << "its polyndr0m" << endl; }
        else { cout << "its NOT polyndrom" << endl; }
    }
}
int main()
{
    task1234();
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();

    task10();
}