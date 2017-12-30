#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <cstdlib>
using namespace std;

void textColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
int width, height;
void line()
{
	for (int i = 0; i <= width; i++)
	{
		cout << "--";
	}
}
void clearScreen() //czyszczenie ekranu
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void hidecursor() //fix for bliking
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
string name = "";
int HP;
int points, playerX, playerY, enemyX, enemyY, shotX, shotY, speed;
int button; //button used to move
int fall; //var for falling 
bool isFlying; //to check if shot is flyfing

void menu()
{
	string x;
	if (name == "")
	{
		cout << "       Sterowanie\n# A - w lewo \n# D - w prawo \n# W - strzal" << endl << endl;
		cout << "Podaj swoja nazwe" << endl << endl;
		cin >> name;
	}
	cout << "Jesli chcesz skonfigurowac swoja gre wpisz tak, jesli nie-wpisz nie" << endl;
	cin >> x;
	if (x == "tak" || x == "TAK" || x == "Tak")
	{
		cout << "Podaj predkosc gry od 1 do 100 (zalecane 20)\n";
		cin >> speed;

		if (speed < 1 || speed > 100)
		{
			cout << name << ", glupi jestes? Warotsc speed ustwaiona na 20" << endl;
			speed = 20;
			Sleep(1000);
		}

		cout << "Podaj szerokosc gry od 10 do 50 (zalecane 25)\n";
		cin >> width;

		if (width < 10 || width > 50)
		{
			cout << name << ", glupi jestes? Warotsc width ustwaiona na 25" << endl;
			width = 25;
			Sleep(1000);
		}

		cout << "Podaj wysokosc gry od 10 do 50 (zalecane 25)\n";
		cin >> height;

		if (height < 10 || height > 50)
		{
			cout << name << ", glupi jestes? Warotsc height ustwaiona na 25" << endl;
			height = 25;
			Sleep(1000);
		}
	}
	else
	{
		height = 25;
		width = 25;
		speed = 20;
	}
}

int main()
{
	char map[50][50];
	SetConsoleTitle(TEXT("Spaceship Game"));
		srand(time(NULL));
		menu();//starts a menu
	fall = 0;
	HP = 3;
	points = 0;
	playerX = width / 2;
	playerY = height - 1;
	enemyX = rand() % 24;
	enemyY = 1;
	shotX = playerX;
	shotY = playerY - 1;
		system("cls");
		hidecursor();
	bool work = true;
	string confirm;
	while (work) //drawing board
	{

		gotoxy(0, 0);
		map[playerX][playerY] = 'x';
		map[playerX + 1][playerY] = 'x';
		map[playerX - 1][playerY] = 'x';
		map[enemyX][enemyY] = 'e';
		map[shotX][shotY] = 'd';

		if (enemyY == height - 1)
		{
			map[enemyX][enemyY] = 'p';
			enemyX = rand() % (width - 1);
			enemyY = 1 + points;
			HP--;
		}
		if (HP == 0)work = false;
		textColor(255);
		line(); //upper line
		cout << endl;
		for (int i = 0; i <= height; i++) //left and right walls 
		{
			cout << "|";
			for (int j = 0; j<width; j++)
			{
				if (map[j][i] == 'x') //darwing player's positon
				{
					textColor(255);
					cout << "xx";
					textColor(7);
				}
				else if (map[j][i] == 'e') //darwing enemy's positon
				{
					textColor(12);
					cout << "oo";
					textColor(7);
				}
				else if (map[j][i] == 'd') //darwing shot's positon
				{
					textColor(7);
					cout << "ii";
					textColor(255);
				}
				else
				{
					textColor(7);
					cout << "  ";
					textColor(255);
				}

			}
			cout << "|" << endl;
		}
		line();//lower line
		textColor(7);
		cout << endl << "Punkty ";
		textColor(10);
		cout << points;
		textColor(7);
		cout << "|HP ";
		textColor(4);
		cout << HP;
		textColor(7);
		cout << "|Gracz:";
		textColor(10);
		cout << name;
		textColor(7);
		if (fall % 2 == 0)
		{
			map[enemyX][enemyY] = 'p';
			enemyY++;
		}
		if (isFlying)
		{
			if (shotY < 2 || ((shotY == enemyY - 1 || shotY == enemyY) && shotX == enemyX))
			{
				isFlying = false;
				if ((shotY == enemyY - 1 || shotY == enemyY) && shotX == enemyX) //when enemy got a hit
				{
					points++;
					enemyX = rand() % (width - 1);
					enemyY = 1 + points;

				}
				map[shotX][shotY] = 'p';
				shotX = playerX;
				shotY = playerY;

			}
			map[shotX][shotY] = 'p';
			shotY--;
		}

		if (_kbhit())
		{
			button = _getch();
			switch (button)
			{
			case 97: //moving left 
			{
				if (playerX > 0)
				{
					map[playerX][playerY] = 'p';
					map[playerX + 1][playerY] = 'p';
					map[playerX - 1][playerY] = 'p';
					playerX--;
					if (!isFlying)
					{
						map[shotX][shotY] = 'p';
						shotX = playerX;

					}
				}
			}
			break;
			case 100: //moving right
			{
				if (playerX < 24)
				{
					map[playerX][playerY] = 'p';
					map[playerX + 1][playerY] = 'p';
					map[playerX - 1][playerY] = 'p';
					playerX++;
					if (!isFlying)
					{
						map[shotX][shotY] = 'p';
						shotX = playerX;
					}
				}
			}
			break;
			case 119: // for shoting
			{
				if (!isFlying)
				{
					map[shotX][shotY] = 'p';
					isFlying = true;
				}
			}
			break;
			}
		}

		fall++;
		Sleep(speed * 10);
	}
		system("cls");
	cout << "GAME OVER" << endl;
		textColor(7);
	cout << endl << "Punkty ";
		textColor(10);
	cout << points;
		textColor(7);
	cout << "|Gracz:";
		textColor(10);
	cout << name;
		textColor(7);
	cout << endl << "chcesz zagrac ponownie? wpisz tak by zagrac, nie by wyjsc" << endl;
	cin >> confirm;
	if (confirm == "tak")
	{
		system("cls");
		main();
	}
	return 0;
}
