#include "Control.h"

//enemies
#include "Enemy.h"
#include "meleeCreature.h"
#include "meleeHumanoid.h"
#include "rangedMagic.h"
#include "rangedArcher.h"

Control::Control() : currentFloor(1), currentEnemies(0), enemyCap(10), numberOfTurns(0), floorWidth(200), floorHeight(200),
                     mapHeight(19),mapWidth(51),logHeight(6),logWidth(51),statusHeight(25),statusWidth(29),
                     mapStartX(0),mapStartY(0),logStartX(0),logStartY(19),statusStartX(51),statusStartY(0)
{
    screenState = MAPSCREEN;

    //initialize the floor map to all walls
    for(int i = 0;i<200;i++)
    {
        for(int j = 0;j<200;j++)
        {
            floorMap[i][j] = ACS_BLOCK;
        }
    }

    //Set intial level load statuses to false
    for(int i = 0;i<10;i++)
    {
        floorFlags[i] = false;
    }

    for(int i = 0;i<10;i++)
    {
        floorNames.push_back("testlevel1.txt");
    }
}

Control::~Control()
{

}

void Control::startCurses()
{
    initscr();
    noecho();
    start_color();
    curs_set(0);
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_CYAN);
    init_pair(3,COLOR_WHITE,COLOR_GREEN);
    init_pair(4,COLOR_CYAN,COLOR_BLACK);
    mapWin = newwin(mapHeight,mapWidth,mapStartY,mapStartX);
    logWin = newwin(logHeight,logWidth,logStartY,logStartX);
    statusWin = newwin(statusHeight,statusWidth,statusStartY,statusStartX);
    cbreak();
    nodelay(mapWin,true);
    keypad(mapWin,true);
    wbkgd(mapWin,COLOR_PAIR(1));
    wbkgd(logWin,COLOR_PAIR(2));
    wbkgd(statusWin,COLOR_PAIR(3));
}

void Control::endCurses()
{
    endwin();
}

void Control::printMapScreen()
{
    /////////////////
    //Print the map//
    /////////////////

    int centerX = (mapWidth - 1)/2;
    int centerY = (mapHeight - 1)/2;

    for(int i = 0;i<mapHeight;i++)
    {
        for(int j = 0;j<mapWidth;j++)
        {
            wmove(mapWin,i,j);
            waddch(mapWin,' ');
        }
    }

    player.calculateSightRange(floorMap);

    for(int i = 0;i<2*player.sightRange + 1;i++)
    {
        for(int j = 0;j<2*player.sightRange + 1;j++)
        {
            if(player.sightArray[i][j] == 1)
            {
                wmove(mapWin,centerY-player.sightRange+i,centerX-player.sightRange+j);
                waddch(mapWin,floorMap[player.y-player.sightRange+i][player.x-player.sightRange+j]);
            }
        }
    }

    wmove(mapWin,centerY,centerX);
    waddch(mapWin,ACS_LANTERN | COLOR_PAIR(4));

    /////////////////
    //Print the log//
    /////////////////

    //First, clear the log
    for(int i = 0;i<logHeight;i++)
    {
        for(int j = 0;j<logWidth;j++)
        {
            wmove(logWin,i,j);
            waddch(logWin,' ');
        }
    }

    char *tempCStr;
    string tempStr;
    for(int i = 0;i<logHeight;i++)
    {
        if(i == log.size())
        {
            break;
        }
        tempStr = log.at(log.size()-1-i);
        tempCStr = new char[tempStr.length()+1];
        strcpy(tempCStr,tempStr.c_str());
        wmove(logWin,logHeight-1-i,0);

        waddstr(logWin,tempCStr);
    }

    //Print status window

    wrefresh(mapWin);
    wrefresh(logWin);
    wrefresh(statusWin);
}

void Control::loadNewFloor()
{
    ifstream level;

    char * filename;
    std::string temp = "";

    if(currentFloor < 10)
    {
        while(!level.is_open())
        {
            temp = "";
            int levelChoice = 1 + (rand()% 10);                                               //Random level selection

            if (levelChoice == 1 && floorFlags[0] == false)                               //open level 1
            {
                temp = floorNames.at(0);
                floorFlags[0] = true;                                                   //flags level as already loaded
            }

            else if (levelChoice == 2 && floorFlags[1] == false)                               //open level 2
            {
                temp = floorNames.at(1);
                floorFlags[1] = true;
            }

            else if (levelChoice == 3 && floorFlags[2] == false)                               //open level 3
            {
                temp = floorNames.at(2);
                floorFlags[2] = true;
            }

            else if (levelChoice == 4 && floorFlags[3] == false)                               //open level 4
            {
                temp = floorNames.at(3);
                floorFlags[3] = true;
            }

            else if (levelChoice == 5 && floorFlags[4] == false)                               //open level 5
            {
                temp = floorNames.at(4);
                floorFlags[4] = true;
            }

            else if (levelChoice == 6 && floorFlags[5] == false)                               //open level 6
            {
                temp = floorNames.at(5);
                floorFlags[5] = true;
            }

            else if (levelChoice == 7 && floorFlags[6] == false)                               //open level 7
            {
                temp = floorNames.at(6);
                floorFlags[6] = true;
            }

            else if (levelChoice == 8 && floorFlags[7] == false)                               //open level 8
            {
                temp = floorNames.at(7);
                floorFlags[7] = true;
            }

            else if (levelChoice == 9 && floorFlags[8] == false)                               //open level 9
            {
                temp = floorNames.at(8);
                floorFlags[8] = true;
            }

            else if (levelChoice == 10 && floorFlags[9] == false)                               //open level 10
            {
                temp = floorNames.at(9);
                floorFlags[9] = true;
            }

            filename = new char[temp.length()+1];
            strcpy(filename,temp.c_str());
            level.open(filename);
        }
    }
    else
    {
        //Load the puzzle level
    }

    char inChar;
    string inString;

    int lineCounter = 0;
    getline(level,inString);

    floorWidth = inString.length();

    while(level.good())
    {
        for(int i = 0;i<inString.length();i++)
        {
            inChar = inString[i];
            if(inChar == '#')
            {
                floorMap[lineCounter][i] = ACS_BLOCK;
            }
            else
            {
                floorMap[lineCounter][i] = inChar;
            }
        }
        getline(level,inString);
        lineCounter++;
    }

    floorHeight = lineCounter;
}

void Control::spawnPlayer()
{
    int spawnX = -1,spawnY = -1;
    for(int i = 0;i<200;i++)
    {
        for(int j = 0;j<200;j++)
        {
            if(floorMap[i][j] != ACS_BLOCK)
            {
                spawnX = j;
                spawnY = i;
                break;
            }
        }
        if(spawnX >= 0)
        {
            break;
        }
    }

    Player temp(spawnX,spawnY);
    player = temp;
}

bool Control::processInput()
{
    bool validInput = true;
    int input = ERR;
    if(screenState == MAPSCREEN)
    {
        int newX = player.x;
        int newY = player.y;

        input = wgetch(mapWin);

        if(input == KEY_DOWN)
        {
            newY += 1;
        }
        else if(input == KEY_UP)
        {
            newY -= 1;
        }
        else if(input == KEY_LEFT)
        {
            newX -= 1;
        }
        else if(input == KEY_RIGHT)
        {
            newX += 1;
        }
        else if(input == 'q' || input == 'Q')
        {
            return false;
        }
        else if(input == 'o' || input == 'O')
        {

        }
        else
        {
            validInput = false;
        }

        if(place_meeting(newY,newX,walls) >= 0)
        {
            newX = player.x;
            newY = player.y;
        }

        player.x = newX;
        player.y = newY;
    }
    else if(screenState == INVENTORY)
    {
        //input = wgetch(invWin);
    }



    if(validInput)
    {
        gameFrame();
    }

    if(screenState == MAPSCREEN)
    {
        printMapScreen();
    }
    else if(screenState == INVENTORY)
    {
        //printInvScreen();
    }

    return true;
}

void Control::gameFrame()
{

    //meleeAIFrame();
    //rangedAIFrame();

}

void Control::getObjects()
{
    for(int i = 0;i<200;i++)
    {
        for(int j = 0;j<200;j++)
        {
            if(floorMap[i][j] == ACS_BLOCK)
            {
                walls.push_back(Wall(i,j));
            }
            else if(floorMap[i][j] == '@')
            {
                chests.push_back(Chest(j,i,2,1,"Chest"));
            }
        }
    }
}

void Control::debugLog()
{
    player.logStats();
    player.logItems();

    ofstream genLog;
    genLog.open("log.txt",std::ofstream::app);

    string tile = "Unknown";

    if(floorMap[player.y][player.x] == ACS_BLOCK)
    {
        tile = "Wall";
    }
    else if(floorMap[player.y][player.x] == '@')
    {
        tile = "Chest";
    }
    else if(floorMap[player.y][player.x] == '.')
    {
        tile = "Floor";
    }

    genLog << "Player Y: " << player.y << std::endl;
    genLog << "Player X: " << player.x << std::endl;
    genLog << "Tile at player's location: " << tile << std::endl;
    genLog << "Number of walls: " << walls.size() << std::endl;
    genLog << "Number of chests: " << chests.size() << std::endl;
    genLog << std::endl;
}

void Control::logMessage(std::string message)
{
    log.push_back(message);
}
