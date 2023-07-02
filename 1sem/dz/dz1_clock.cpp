#include <iostream>
#include <cmath>
#include <string>
#include <conio.h> //Этот заголовочный файл объявляет несколько библиотечных функций для работы с «консольным вводом и выводом»
#include <stdio.h>
#include <Windows.h>





// ЧТО ОНА ДЕЛАЕТ ?????    МЫ ПИШИМ ЕЙ МИНУТЫ ЛЮБЫЕ ОНА ПОКАЗЫВАЕТ КУДА БУДЕТ НАПРАВЛЕНА СТРЕЛКА ЧАСОВ

#define _USE_MATH_DEFINES
using namespace std;

int hours;
int  minute;
int ost;
int i = 0, j = 0;
int konstrelkaY = 2, konstrelkaX = 7; // координаты конца стрелки // у 12 часов стоит вначале
int strelkaY = 3, strelkaX = 7;
/*
################
#      R       #
#              #
#              #
#9            3#
#              #
#              #
#      6       #
################  */


void clock()
{
	for (int i = 0; i < 9; i++) { //высота
		for (int j = 0; j < 16; j++) { // ширина
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			switch (i)
			{
			case 1:
			{
				switch (j)
				{
				case 8: cout << "R"; break;
				}
			}
			break;
			/*case i== strelkaY:
			{
				switch (j)
				{
				case j==strelkaX: cout << "X";
				}
			}break;/*///????????
			case 4:
			{
				switch (j)
				{
				case 13: cout << "3"; break;
				case 1: cout << "9"; break;
				}
			}
			break;
			case 7:
			{
				switch (j)
				{
				case 8: cout << "6"; break;
				}
			}
			break;
			}

			if (j == 0 || j == 16 - 1)
				cout << "#";
			else
			{
				if (i == 0 || i == 8) cout << "#"; else
					cout << " ";
			}
			if (i == konstrelkaY && j == konstrelkaX)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));//4 red  //2 = green // 0 black фон   //где находится оттуда и  красит

				cout << "X";
			};
			if (i == strelkaY && j == strelkaX)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));//4 red  //2 = green // 0 black фон   //где находится оттуда и  красит

				cout << "X";
			};
			if (i == 4 && j == 6)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
				cout << "X";
			}
		}
		cout << endl;
	}
}
void player()
{
	cout << "minutes=";
	cin >> minute;
	if (minute != 45)
	{

		minute = minute % 60; // чтобы было меньше часа
		ost = minute % 8;
		minute = (minute / 8);// целая часть  //0 8 `16 24 32 48 60 // сколько восьмых часа
		if (ost > 4 && minute < 7) { minute = minute + 1; } // 6 к примеру минут ближе к 8 но целая часть =ноль
		minute = minute * 8;// перевод в 60 минутный формат //переход от целых частей
	}
}
void trip()
{
	switch (minute)
	{
	case 8: // 1/8
		konstrelkaX = konstrelkaX + 3;
		strelkaX = strelkaX + 2;
		break;
	case 16: // 15 минут
		konstrelkaX = konstrelkaX + 3;
		konstrelkaY = konstrelkaY + 2;
		strelkaX = strelkaX + 2;
		strelkaY = strelkaY + 1;
		break;
	case 24: // =3/8
		konstrelkaX = konstrelkaX + 4;
		konstrelkaY = konstrelkaY + 4;
		strelkaX = strelkaX + 2;
		strelkaY = strelkaY + 2;
		break;
	case 32: // эквивалент 30 минут
		//strelkaX = strelkaX + 3;
		konstrelkaY = konstrelkaY + 4;
		strelkaY = strelkaY + 2;
		break;
	case 40:    //  5/8
		konstrelkaX = konstrelkaX - 4;
		konstrelkaY = konstrelkaY + 4;
		strelkaX = strelkaX - 2;
		strelkaY = strelkaY + 2;
		break;
	case 48:
		konstrelkaX = konstrelkaX - 4;
		strelkaX = strelkaX - 2;
		break;
	case 56:   // near 60
		konstrelkaX = konstrelkaX - 2;
		strelkaX = strelkaX - 1;
		break;
	case 45:    //  5/8
		konstrelkaX = konstrelkaX - 4;
		konstrelkaY = konstrelkaY + 2;
		strelkaX = strelkaX - 4;
		strelkaY = strelkaY + 1;
		break;
	}
}
int main()
{
	clock();
	player();
	trip();
	clock();

}
