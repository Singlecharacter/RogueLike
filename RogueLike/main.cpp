#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include "Wall.h"

using namespace std;

template<typename T>
bool place_meeting(int,int,vector<T>&);

int main()
{
    srand(time(NULL));
    int x, y, ch, newX, newY;
    int h, w;

    initscr();
    getmaxyx(stdscr,h,w);
    x = rand() % w;
    y = rand() % h;
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
    for(int i = 0;i < 10;i++)
    {
        walls.push_back(Wall(rand() % h,rand() % w));
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

        /*ch = (rand() % 4) + 1;

        if(ch == 1)
        {
            y--;
        }
        if(ch == 2)
        {
            y++;
        }
        if(ch == 3)
        {
            x--;
        }
        if(ch == 4)
        {
            x++;
        }*/

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
    endwin();

    return 0;
}

template<typename T>
bool place_meeting(int y, int x, vector<T>& objs)
{

    for(int i = 0;i<objs.size();i++)
    {
        if(objs.at(i).x == x && objs.at(i).y == y)
        {
            return true;
        }
    }
    return false;
}
