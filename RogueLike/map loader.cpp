#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "Wall.h"

using namespace std;

template<typename T>
bool place_meeting(int,int,vector<T>&);
void levelLoad(int levelArray[200][200], bool levelFlagArray[10]);  //opens filestream and loads text level onto array
void levelCreate(int levelArray[200][200]);                                                 //initializes and displays screen with current level


/*
COMMENTED OUT
USED FOR TESTING

DO NOT DELETE UNTIL WE'RE IN THE FINAL
STAGES OF WORK

int main()
{
    int levelArray[200][200];                         //Changed this to 200x200 levels
    srand(time(NULL));
    bool levelFlagArray[10];                         //Used to flag whether or not a level has already been loaded


    for (int i = 0; i < 10; i++)                    //Initialized all flag values to false
    {
        levelFlagArray[i] = false;
    }

    levelLoad(levelArray, levelFlagArray);          //Load and display a random level

    return 0;
}
*/



//___________________ FUNCTION DEFINITIONS____________________

void levelLoad(int levelArray[200][200], bool levelFlagArray[10])
{
    int levelChoice = 1 + (rand()% 10);                                               //Random level selection


    if (levelChoice == 1 && levelFlagArray[0] == false)                               //open level 1
    {
        ifstream level;
        level.open("level1.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);                                                    //displays level
        levelFlagArray[0] = true;                                                   //flags level as already loaded
    }

    if (levelChoice == 2 && levelFlagArray[1] == false)                               //open level 2
    {
        ifstream level;
        level.open("level2.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[1] = true;
    }

    if (levelChoice == 3 && levelFlagArray[2] == false)                               //open level 3
    {
        ifstream level;
        level.open("level3.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[2] = true;
    }

    if (levelChoice == 4 && levelFlagArray[3] == false)                               //open level 4
    {
        ifstream level;
        level.open("level4.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[3] = true;
    }

    if (levelChoice == 5 && levelFlagArray[4] == false)                               //open level 5
    {
        ifstream level;
        level.open("level5.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[4] = true;
    }

    if (levelChoice == 6 && levelFlagArray[5] == false)                               //open level 6
    {
        ifstream level;
        level.open("level6.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[5] = true;
    }

    if (levelChoice == 7 && levelFlagArray[6] == false)                               //open level 7
    {
        ifstream level;
        level.open("level7.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[6] = true;
    }

    if (levelChoice == 8 && levelFlagArray[7] == false)                               //open level 8
    {
        ifstream level;
        level.open("level8.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[7] = true;
    }

    if (levelChoice == 9 && levelFlagArray[8] == false)                               //open level 9
    {
        ifstream level;
        level.open("level9.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[8] = true;
    }

    if (levelChoice == 10 && levelFlagArray[9] == false)                               //open level 10
    {
        ifstream level;
        level.open("level10.txt");
        char inChar;

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                inChar = level.get();
                if(inChar == '#')
                {
                    levelArray[i][j] = ACS_BLOCK;
                }
                else
                {
                    levelArray[i][j] = '.';
                }
            }
            level.ignore();
        }
        levelCreate(levelArray);
        levelFlagArray[9] = true;
    }
}



void levelCreate(int levelArray[200][200])                //initializes and prints the level after levelArray is passed to it
{
    int x, y, ch, newX, newY;
    int h, w;

    x = 1;
    y = 1;
    initscr();
    getmaxyx(stdscr,h,w);
    //x = rand() % w;
    //y = rand() % h;
    curs_set(0);
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_GREEN);
    init_pair(3,COLOR_BLACK,COLOR_CYAN);
    init_pair(4,COLOR_BLACK,COLOR_BLUE);
    init_pair(5,COLOR_BLACK,COLOR_YELLOW);
    init_pair(6,COLOR_BLACK,COLOR_RED);
    init_pair(7,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(8,COLOR_WHITE,COLOR_BLACK);

    wbkgd(stdscr,COLOR_PAIR(8));
    noecho();

    vector<Wall> walls;
    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            if(levelArray[i][j] == ACS_BLOCK)
            {
                walls.push_back(Wall(i,j));
            }
        }
    }

    bool SEIZUREMODE = false;

    while(true)
    {
        clear();
        for(int i = 0;i<walls.size();i++)
        {
            wmove(stdscr,walls.at(i).y,walls.at(i).x);
            addch(ACS_BLOCK);
        }

        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < 200; j++)
            {
                wmove(stdscr,i,j);
                addch(levelArray[i][j]);
            }
        }

        if(SEIZUREMODE)
        {
            wbkgd(stdscr,COLOR_PAIR(rand() % 7 + 1));
        }
        else
        {
            wbkgd(stdscr,COLOR_PAIR(8));
        }

        wmove(stdscr,y,x);
        addch(ACS_LANTERN);
        wmove(stdscr,y,x);

        ch = getch();

        newX = x;
        newY = y;

        if(ch == KEY_UP || ch == '8')
        {
            newY--;
        }
        else if(ch == KEY_DOWN || ch == '2')
        {
            newY++;
        }
        else if(ch == KEY_LEFT || ch == '4')
        {
            newX--;
        }
        else if(ch == KEY_RIGHT || ch == '6')
        {
            newX++;
        }
        else if(ch == '7')
        {
            newX--;
            newY--;
        }
        else if(ch == '9')
        {
            newX++;
            newY--;
        }
        else if(ch == '1')
        {
            newX--;
            newY++;
        }
        else if(ch == '3')
        {
            newX++;
            newY++;
        }
        else if(ch == 'q' || ch == 'Q')
        {
            break;
        }
        else if(ch == 'S')
        {
            SEIZUREMODE = !SEIZUREMODE;
        }

        if(!place_meeting(newY,newX,walls))
        {
            x = newX;
            y = newY;
        }

        if(y < 0)
        {
            y = 0;
        }
        else if(y >= h)
        {
            y = h - 1;
        }

        if(x < 0)
        {
            x = 0;
        }
        else if(x >= w)
        {
            x = w - 1;
        }
        refresh();
    }
    //endwin();
}




template<typename T>
bool place_meeting(int checkY, int checkX, vector<T>& objs)
{

    for(int i = 0;i<objs.size();i++)
    {
        if(objs.at(i).x == checkX && objs.at(i).y == checkY)
        {
            return true;
        }
    }
    return false;
}
