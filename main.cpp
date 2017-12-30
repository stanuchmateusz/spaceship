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
void hidecursor() //fix for bliking
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
int button; //button used to move
int fall=0; //var for falling 
bool isFlying; //to check if shot is flyfing
int speed;

int main()
{
    SetConsoleTitle( TEXT( "Spaceship Game" ) );
    srand(time(NULL));
    enemyX = rand()%24;
    shotX=playerX;
    shotY=playerY-1;
    char map [25][25];
    cout << "       Sterowanie\n# A - w lewo \n# D - w prawo \n# W - strzal"<<endl<<endl;
    cout << "Podaj swoja nazwe" << endl<<endl;
    cin>>name;
    cout << "Podaj predkosc gry od 1 do 100 (zalecane 20)\n";
    cin >> speed;
    if (speed < 1 || speed > 100)
    {
        cout<<name<<", glupi jestes? Warotsc speed ustwaiona na 20"<<endl;
        speed=20;
        Sleep(1000);
    }
    system("cls");
    hidecursor();
    bool work =true;
    while (work) //drawing board
  {

    gotoxy(0,0);
    map [playerX][playerY]='x';
    map [playerX+1][playerY]='x';
    map [playerX-1][playerY]='x';
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
    line(); //upper line
    cout<<endl;
        for (int i=0;i<=25;i++) //left and right walls 
        {
        cout<<"|";
                for(int j=0;j<25;j++)
                {
                    if(map[j][i] =='x') //darwing player's positon
                        {
                            textColor(255);
                            cout<<"xx";
                            textColor(7);
                        }
                        else if(map[j][i] =='e') //darwing enemy's positon
                        {   textColor(12);
                            cout<<"oo";
                            textColor(7);
                        }
                        else if(map[j][i] =='d') //darwing shot's positon
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
    line();//lower line
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
                if ((shotY == enemyY-1 || shotY == enemyY)&& shotX == enemyX) //when enemy got a hit
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
                case 97: //moving left 
            {
                if(playerX > 0)
                {
                    map [playerX][playerY]='p';
                    map [playerX+1][playerY]='p';
                    map [playerX-1][playerY]='p';
                    playerX--;
                        if(!isFlying)
                    {
                        map [shotX][shotY]='p';
                        shotX=playerX;

                    }
                }
            }
                break;
                case 100: //moving right
            {
                if(playerX < 24)
                {
                    map [playerX][playerY]='p';
                    map [playerX+1][playerY]='p';
                    map [playerX-1][playerY]='p';
                    playerX++;
                       if(!isFlying)
                    {
                        map [shotX][shotY]='p';
                        shotX=playerX;
                    }
                }
            }
                break;
                case 119: // for shoting
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
    Sleep(speed*10);
  }
system("cls");
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
cout<<endl<<"aby wyjsc wpisz cokolwiek i potwierdz enterem!"<<endl;
cin>>name; // in case some1 holds bottom after game over

return 0;
}
/*
x=player
e=enemy
p=empty
d=shot
*/
