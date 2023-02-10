
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <Windows.h>

#define _USE_MATH_DEFINES

using namespace std;

void n1() {
    int  x, y, z;
    cout << "x=";
    cin >> x;
    cout << "y=";
    cin >> y;
    cout << "z=";
    cin >> z;

    int ost5 = 0;
    if (x % 2 == 1 && y % 2 == 1)
    {
        cout << "condition is true " << endl;
    }
    else cout << "condition is false" << endl;

    if ((x < 20 && y > 20) || (x > 20 && y < 20)) {
        cout << "condition is true " << endl;
    }
    else cout << " condition is false" << endl;

    if (x == 0 || y == 0)
    {
        cout << "condition is true " << endl;
    }
    else cout << "condition is false" << endl;

    if (x < 0 && y < 0 && z < 0)
    {
        cout << "condition is true " << endl;
    }
    else cout << " condition is false" << endl;
    if (x % 5 == 0) { ost5 = ost5 + 1; }
    if (y % 5 == 0) { ost5 = ost5 + 1; }
    if (z % 5 == 0) { ost5 = ost5 + 1; }
    if (ost5 == 1)
    {
        cout << "condition is true " << endl;
    }
    else cout << " condition is false" << endl;
    if (x > 100 || y > 100)
    {
        cout << "condition is true " << endl;
    }
    else cout << " condition is false" << endl;

}

void n2()
{
    int ladya = 0;
    using byte = unsigned char;
    pair<byte, byte> position;
    pair<byte, byte> position2;
    cout << "position a=";
    cin >> position.first >> position.second;
    cout << "position b=";
    cin >> position2.first >> position2.second;
    if (position.first == position2.first || position.second == position2.second)
    {
        cout << "LADYA A mojet ydarit B" << endl;
        ladya = 1;
    }
    int slon = 0;

    //slon
    if (fabs(position.first - position2.first) == fabs(position.second - position2.second))
    {
        cout << "slon mojet bit B" << endl;
        slon = 1;
    }
    //король
    if ((position.first + 1 == position2.first) && (position.second + 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;// диагонпль вправо  вниз
    }
    if ((position.first - 1 == position2.first) && (position.second + 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;// диагонпль  вправо вверъ
    }
    if ((position.first + 1 == position2.first) && (position.second - 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;// диагонпль влево вниз

    }
    if ((position.first - 1 == position2.first) && (position.second - 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;// диагонпль влево
    }
    if ((position.first + 1 == position2.first) && (position.second + 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;
    }
    if ((position.first - 1 == position2.first) || (position.second - 1 == position2.second))
    {
        cout << "KOROL IZ A V B MOJET ODNIM HODOM" << endl;// диагонпль влево
    }



    // ферзь
    if ((ladya == 1) || (slon == 1)) { cout << " ferz, mojet na b popasti" << endl; }

    // пешка
    if (position.second + 1 == position2.second) { cout << " BELAY peshka mojet poiti na b "; }
    if (position2.second > position.second && fabs(position.first - position2.first))
    {
        cout << " Peshka mojet s a na b ydarom ";
    }
}
void n3()
{
    int a;
    for (a = 1; a < 10; a++)
    {
        cout << a * 7 << endl;
    }
    int T = 0;
    cout << "T=";
    cin >> T;
    for (a = 1; a < 10; a++)
    {
        cout << a * T << endl;
    }
}
void n4()
{
    int h;

    int proiz = 1;
    for (h = 8; h < 16; h++)
    {
        proiz *= h;
        cout << proiz;
    }
    int b;
    proiz = 1;
    cout << "(1-20)B=";
    cin >> b;
    for (b; b < 21; b++) {
        proiz *= b;
    }

    int B = 0, A;
    cout << "A=";
    cin >> A;
    cout << "   B=";
    cin >> B;
    proiz = 1;
    if (B >= A)
    {
        for (B; B <= A; B++)
            proiz = proiz * B;
    }
    else { cout << "incorrect vvod a b "; }
}
int main()
{
    n1();
    n2();
    n3();
    n4();
}