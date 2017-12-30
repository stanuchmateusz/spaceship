#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <cstdlib>
using namespace std;

void textColor (int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void gotoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}
void line()
{
    for (int i=0;i<=25;i++)
    {
        cout<<"--";
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
void hidecursor() //naprawa migania
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
string name;
int HP=3;
int points=0;
int playerX=12;
int playerY=24;
int enemyX;
int enemyY=1;
int shotX,shotY;
int button; //przycisk do streowania
int fall=0; //zmienna sterujaca spadamiem
bool isFlying;


int main()
{
    srand(time(NULL));
    enemyX = rand()%24;
    shotX=playerX;
    shotY=playerY-1;
    char map [25][25];
    cout << "A - w lewo \n D - w prawo \n W - strzal"
    cout << "Podaj swoja nazwe" << endl;
    cin>>name;
    system("cls");
    hidecursor();
    bool work =true;
    while (work) //rworzenie planszy
  {

    gotoxy(0,0);
    map [playerX][playerY]='x';
    map [enemyX][enemyY]='e';
    map [shotX][shotY]='d';

        if (enemyY==24)
        {
            map [enemyX][enemyY]='p';
            enemyX = rand()%24;
            enemyY = 1 + points;
            HP--;
        }
        if (HP==0)work=false;
    textColor(255);
    line(); //robi gorna scianke
    cout<<endl;
        for (int i=0;i<=25;i++) //robi scianki boczne
        {
        cout<<"|";
                for(int j=0;j<25;j++)
                {
                    if(map[j][i] =='x')
                        {
                            cout<<"xx";
                            textColor(7);
                        }
                        else if(map[j][i] =='e')
                        {   textColor(12);
                            cout<<"oo";
                            textColor(7);
                        }
                        else if(map[j][i] =='d')
                        {   textColor(7);
                            cout<<"ii";
                            textColor(255);
                        }
                        else
                        {
                            textColor(7);
                            cout<<"  ";
                            textColor(255);
                        }

                }
        cout<<"|"<<endl;
        }
    line();//robi dolna scianke
    textColor(7);
    cout<<endl<<"Punkty ";
    textColor(10);
    cout<<points;
    textColor(7);
    cout<<"|HP ";
    textColor(4);
    cout<<HP;
    textColor(7);
    cout<<"|Gracz:";
    textColor(10);
    cout<<name;
    textColor(7);
    if (fall%2==0)
        {
            map [enemyX][enemyY]='p';
            enemyY++;
        }
    if (isFlying)
    {
        if (shotY < 2 || ((shotY == enemyY-1 || shotY == enemyY)&& shotX == enemyX))
                {
                isFlying=false;
                if ((shotY == enemyY-1 || shotY == enemyY)&& shotX == enemyX) //gdy enemy zostanie trafiony
                 {
                    points++;
                    enemyX = rand()%24;
                    enemyY = 1 + points;

                }
                map [shotX][shotY]='p';
                shotX=playerX;
                shotY=playerY;

            }
        map [shotX][shotY]='p';
        shotY --;
    }

    if(kbhit())
    {
        button=getch();
            switch (button)
            {
                case 97: //dla klawisza a chodzi w lewo  i odopiedio ustala amunicje
            {
                if(playerX > 0)
                {
                    map [playerX][playerY]='p';
                    playerX--;
                        if(!isFlying)
                    {
                        map [shotX][shotY]='p';
                        shotX=playerX;

                    }
                }
            }
                break;
                case 100: //dla kaliwsza d chodzi w prawo i odopiedio ustala amunicje
            {
                if(playerX < 24)
                {
                    map [playerX][playerY]='p';
                    playerX++;
                       if(!isFlying)
                    {
                        map [shotX][shotY]='p';
                        shotX=playerX;
                    }
                }
            }
                break;
                case 119: // dla w strzela
            {
                if(!isFlying)
                {
                    map [shotX][shotY]='p';
                    isFlying=true;
                }
            }
                break;
            }
    }

    fall++;
    Sleep(200);
  }
system("cls")
    cout<<"GAME OVER"<<endl;
textColor(7);
    cout<<endl<<"Punkty ";
textColor(10);
    cout<<points;
textColor(7);
    cout<<"|Gracz:";
textColor(10);
    cout<<name;
textColor(7);
system("pause");
return 0;
}
/*
x=gracz
e=enemy
p=puste
d=strzal
*/
