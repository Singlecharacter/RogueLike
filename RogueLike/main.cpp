#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "Wall.h"
#include "Player.h"

using namespace std;

template<typename T>
bool place_meeting(int,int,vector<T>&);

int main()
{
    int levelArray[25][80];
    srand(time(NULL));
    int ch, newX, newY;
    int h, w;
    int damage = 10;

    Player player(10,10);//Creates a player objecct at position (10,10)

    ifstream level;

    ofstream damageTest;

    level.open("level.txt");

    char inChar;

    /*
    Reads in map data from a file. Assumes fixed dimensions of 80x25. Testing purposes only.
    */
    for(int i = 0;i<25;i++)
    {
        for(int j=0;j<80;j++)
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

    level.close();

    damageTest.open("damagelog.txt", ofstream::app); //Damage log file, see below
    damageTest << endl;

    initscr(); //Start curses
    WINDOW * win = newwin(25,80,0,0);//Create a new window
    getmaxyx(win,h,w);//Set h and w to the height and width of the new window, respectively
    curs_set(0);//Hide the cursor
    keypad(win,TRUE);//Allow SPECIAL keys (They're special)
    nodelay(win,TRUE);//Makes SEIZUREMODE more seizurey
    cbreak();//Prevents characters being stored in a buffer instead of passed by getch
    start_color();//Allows the use of color

    //The color pairs used in SEIZUREMODE
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
    init_pair(2,COLOR_BLACK,COLOR_GREEN);
    init_pair(3,COLOR_BLACK,COLOR_CYAN);
    init_pair(4,COLOR_BLACK,COLOR_BLUE);
    init_pair(5,COLOR_BLACK,COLOR_YELLOW);
    init_pair(6,COLOR_BLACK,COLOR_RED);
    init_pair(7,COLOR_BLACK,COLOR_MAGENTA);

    //The default color pair
    init_pair(8,COLOR_WHITE,COLOR_BLACK);

    wbkgd(win,COLOR_PAIR(8));
    noecho();


    //Fills a vector with all of the wall locations for use in collision checking
    vector<Wall> walls;
    for(int i = 0;i < 25;i++)
    {
        for(int j = 0;j<80;j++)
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
        //Prints the level array to the window
        for(int i=0;i<25;i++)
        {
            for(int j=0;j<80;j++)
            {
                wmove(win,i,j);
                waddch(win,levelArray[i][j]);
            }
        }

        //Checks if you want seizures. If you do, it gives them to you.
        if(SEIZUREMODE)
        {
            wbkgd(win,COLOR_PAIR(rand() % 7 + 1));
        }
        else
        {
            wbkgd(win,COLOR_PAIR(8));
        }

        //Print the player to the window
        wmove(win,player.y,player.x);
        waddch(win,ACS_LANTERN);
        wmove(win,player.y,player.x);

        wrefresh(win); //wrefresh updates changes to the window

        ch = wgetch(win); //gets a character input from the keyboard

        newX = player.x;
        newY = player.y;

        /*
        The next section checks for movement or special actions.
        Arrow keys and numpad digits can both move the character.
        The game loop quits on a q or Q.
        SEIZUREMODE starts on a capital S.
        */

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

        //Makes sure the desired new location of the player isn't a wall
        if(!place_meeting(newY,newX,walls))
        {
            player.x = newX;
            player.y = newY;
        }

        //Make sure the player doesn't go off the screen

        if(player.y < 0)
        {
            player.y = 0;
        }
        else if(player.y >= h)
        {
            player.y = h - 1;
        }

        if(player.x < 0)
        {
            player.x = 0;
        }
        else if(player.x >= w)
        {
            player.x = w - 1;
        }
    }

    //////////////////
    //DAMAGE LOGGING//
    //////////////////

    /*
    This performs a lot of damage actions on the player and logs the results.
    It has the capability to generate massive walls of text. Use with caution.
    */

    /*damage = 10;
    player.setAC(0);

    int damageNum = 0;
    int biggestDamage = -1;
    int smallestDamage = -1;
    int damageAverage = 0;
    int damageSum = 0;

    for(int k = 0;k<50;k++)
    {
        damage = 10;
        for(int j = 0;j<50;j++)
        {
            damageNum = 0;
            biggestDamage = -1;
            smallestDamage = -1;
            damageAverage = 0;
            damageSum = 0;

            for(int i = 0; i < 1000; i++)
            {
                damageNum = player.hurt(damage);

                if(biggestDamage == -1 && smallestDamage == -1)
                {
                    biggestDamage = damageNum;
                    smallestDamage = damageNum;
                }
                else
                {
                    if(damageNum > biggestDamage)
                    {
                        biggestDamage = damageNum;
                    }

                    if(damageNum < smallestDamage)
                    {
                        smallestDamage = damageNum;
                    }
                }
                damageSum += damageNum;

                player.fullHeal();
            }
            damageAverage = damageSum/1000;
            damageTest << "Base Damage: " << damage << "\tAverage Actual: " << damageAverage
                       << "\tLowest: " << smallestDamage << "\t Highest: " << biggestDamage
                       << "\tAC: " << player.getAC() << endl;

            damage += 1;
        }
        player.setAC(player.getAC()+1);
    }*/

    damageTest.close();
    endwin();

    return 0;
}

/*
place_meeting takes a vector of game objects and checks if any of those objects are at a given point.
If one is, it returns true. Otherwise, it returns false.
*/

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
