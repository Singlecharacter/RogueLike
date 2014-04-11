#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "Wall.h"
#include "Player.h"
#include "utility.cpp"
#include "map loader.h"
#include "Item.h"
#include "Chest.h"

using namespace std;

int main()
{
    int levelArray[200][200];
    for(int i = 0;i<200;i++)
    {
        for(int j = 0;j<200;j++)
        {
            levelArray[i][j] = ACS_BLOCK;
        }
    }

    ifstream level;
    level.open("testlevel1.txt");

    string inString;
    char inChar;

    int lineCounter = 0;
    getline(level,inString);

    int width = inString.length();

    while(level.good())
    {
        for(int i = 0;i<inString.length();i++)
        {
            inChar = inString[i];
            if(inChar == '#')
            {
                levelArray[lineCounter][i] = ACS_BLOCK;
            }
            else
            {
                levelArray[lineCounter][i] = inChar;
            }
        }
        getline(level,inString);
        lineCounter++;
    }

    int height = lineCounter;

    int spawnX = -1, spawnY = -1;

    for(int i = 0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            if(levelArray[i][j] != ACS_BLOCK)
            {
                spawnX = j;
                spawnY = i;
                break;
            }
        }
        if(spawnX != -1)
        {
            break;
        }
    }

    Player player(spawnX,spawnY);

    vector<Wall> walls;
    for(int i = 0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            if(levelArray[i][j] == ACS_BLOCK)
            {
                walls.push_back(Wall(i,j));
            }
        }
    }

    vector<Chest> chests;
    for(int i = 0;i<height;i++)
    {
        for(int j = 0;j<width;j++)
        {
            if(levelArray[i][j] == '@')
            {
                chests.push_back(Chest(j,i,2,1,"Chest"));
            }
        }
    }

    initscr();
    noecho();
    start_color();
    curs_set(0);
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    WINDOW *win = newwin(25,79,0,0);
    cbreak();
    nodelay(win,true);
    keypad(win,true);
    wbkgd(win,COLOR_PAIR(1));
    int topLeftX = player.x - 39,topLeftY = player.y - 12,newX = player.x,newY = player.y;
    int ch = ' ';

    int centerX = 39;
    int centerY = 12;

    while(true)
    {
        for(int i = 0;i<25;i++)
        {
            for(int j = 0;j<79;j++)
            {
                wmove(win,i,j);
                waddch(win,' ');
            }
        }

        player.calculateSightRange(levelArray);

        for(int i = 0;i<11;i++)
        {
            for(int j = 0;j<11;j++)
            {
                if(player.sightArray[i][j] == 1)
                {
                    wmove(win,centerY - 5 + i,centerX - 5 + j);
                    waddch(win,levelArray[player.y - 5 + i][player.x - 5 + j]);
                }
            }
        }

        wmove(win,centerY,centerX);
        waddch(win,ACS_LANTERN | COLOR_PAIR(2));

        wrefresh(win);

        ch = wgetch(win);

        if(ch == KEY_LEFT)
        {
            newX = player.x - 1;
        }
        else if(ch == KEY_RIGHT)
        {
            newX = player.x + 1;
        }
        else if(ch == KEY_UP)
        {
            newY = player.y - 1;
        }
        else if(ch == KEY_DOWN)
        {
            newY = player.y + 1;
        }
        else if(ch == 'q' || ch == 'Q')
        {
            break;
        }
        else if(ch == 'o' || ch == 'O')
        {
            int foundIndex = place_meeting(player.y,player.x,chests);
            if(foundIndex >= 0)
            {
                chests.at(foundIndex).generateItem();
                player.equipItem(chests.at(foundIndex).getItem());
                levelArray[chests.at(foundIndex).y][chests.at(foundIndex).x] = '.';
                chests.erase(chests.begin()+foundIndex);
            }
        }

        if(place_meeting(newY,newX,walls) != -1)
        {
            newX = player.x;
            newY = player.y;
        }

        player.x = newX;
        player.y = newY;

        topLeftX = player.x - 39;
        topLeftY = player.y - 12;

        if(topLeftX < 0)
        {
            topLeftX = 0;
        }
        else if(topLeftX > width - 79)
        {
            topLeftX = width - 79;
        }

        if(topLeftY < 0)
        {
            topLeftY = 0;
        }
        else if(topLeftY > height - 25)
        {
            topLeftY = height - 25;
        }
    }

    ofstream genLog;

    genLog.open("log.txt",ofstream::app);

    genLog << "Player Y: " << player.y << endl;
    genLog << "Player X: " << player.x << endl;
    genLog << "Tile at player's location: " << levelArray[player.y][player.x] << endl;
    genLog << "Number of walls: " << walls.size() << endl;
    genLog << "Number of chests: " << chests.size() << endl;

    genLog << endl;

    genLog.close();

    player.logStats();
    player.logItems();

    return 0;
}
