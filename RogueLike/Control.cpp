#include "Control.h"


void printTitle();            //Control object doesn't use these; the intromenu method does
void wait(int sec);
void clearScreen();



Control::Control() : currentFloor(1), currentEnemies(0), enemyCap(10), numberOfTurns(0), floorWidth(200), floorHeight(200),
                     mapHeight(19),mapWidth(51),logHeight(6),logWidth(51),statusHeight(25),statusWidth(29),invHeight(25),invWidth(80),
                     mapStartX(0),mapStartY(0),logStartX(0),logStartY(19),statusStartX(51),statusStartY(0),invStartX(0),invStartY(0)
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

    floorNames.push_back("level1.txt");
    floorNames.push_back("level2.txt");
    floorNames.push_back("level3.txt");
    floorNames.push_back("level4.txt");
    floorNames.push_back("level5.txt");
    floorNames.push_back("level6.txt");
    floorNames.push_back("level7.txt");
    floorNames.push_back("level8.txt");
    floorNames.push_back("level9.txt");
    floorNames.push_back("level10.txt");
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
    invWin = newwin(invHeight,invWidth,invStartY,invStartX);
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

    ///////////////////////
    //Print status window//
    ///////////////////////



    wrefresh(mapWin);
    wrefresh(logWin);
    wrefresh(statusWin);
}

void Control::printInvScreen()
{

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
    std::string inString;

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
        input = wgetch(invWin);
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
        printInvScreen();
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


void Control::introMenu()
{
    int raceChoice = 1;
    int typeChoice = 1;

    std::string racePrint = "";
    std::string typePrint = "";
    std::string playerName = "";                   //Stores player name

    Player characterPlayer;

    printTitle();
    clearScreen();

    std::cout << endl;
    std::cout << endl;
    std::cout << "Enter your name: ";
    std::cin >> playerName;
    std::cout << endl;
    std::cout << endl;
    std::cout << "Select Your Race" << endl;
    std::cout << "_______________________________" << endl;
    std::cout << "1. Human" << endl;
    std::cout << endl;
    std::cout << "2. Dwarf" << endl;
    std::cout << endl;
    std::cout << "3. Elf" << endl;
    std::cout << endl;
    std::cin >> raceChoice;

    switch (raceChoice)                                         //Race Switch Statement
    {
        case 1     :std::cout << "You have chosen Human." << endl;
                    //Human gets no special attributes.
                    racePrint = " a Human ";
                    break;

        case 2     :std::cout << "You have chosen Dwarf." << endl;
                    //set dwarf attributes
                    racePrint = " a Dwarf ";
                    break;

        case 3     :std::cout << "You have chosen Elf." << endl;
                    //set elf attributes
                    racePrint = " an Elven ";
                    break;

        default    :std::cout << "You have chosen Human by default." << endl;
                    raceChoice = 1;
                    //Humans suck...
                    racePrint = " a Human ";
                    break;
    }

    clearScreen();


    std::cout << "Select Your Type" << std::endl;
    std::cout << "_______________________________" << std::endl;
    std::cout << "1. Warrior" << endl;
    std::cout << std::string(' ',35) << "-Melee attributes..." << std::endl;
    std::cout << std::endl;
    std::cout << "2. Mage" << endl;
    std::cout << std::string(' ',35) << "-Mage attributes..." << std::endl;
    std::cout << std::endl;
    std::cout << "3. Thief" << endl;
    std::cout << std::string(' ',35) << "-Thief attributes..." << std::endl;
    std::cout << std::endl;
    std::cin >> typeChoice;



    switch (typeChoice)                                         //Class Switch Statement
    {
        case 1     :std::cout << "You are a Warrior." << endl;
                    //Set melee attributes...
                    typePrint = "Warrior.";
                    break;

        case 2     :std::cout << "You are a Mage." << endl;
                    //Set mage attributes...
                    typePrint = "Mage.";
                    break;

        case 3     :std::cout << "You are a Thief." << endl;
                    //Set thief attributes...
                    typePrint = "Thief.";
                    break;

        default    :std::cout << "You are a Warrior by default." << endl;
                    raceChoice = 1;
                    //Set warrior attributes...
                    typePrint = "Warrior.";
                    break;
    }


    clearScreen();

    std::cout << "You are" << racePrint << typePrint << endl;


    clearScreen();

    std::cout << std::string(' ',45) << "Map Screen Controls" << endl;                     //Controls
    std::cout << std::string(' ',45) << "___________________" << endl;
    std::cout << "Up Arrow - Move up" << endl;
    std::cout << "Down Arrow - Move down" << endl;
    std::cout << "Left Arrow - Move left" << endl;
    std::cout << "Right Arrow - Move right" << endl;
    std::cout << "A - Ranged attack" << endl;
    std::cout << "I - Open Inventory" << endl;
    std::cout << "E - Open equipment" << endl;
    std::cout << "< - Ascend a level" << endl;
    std::cout << "> - Descend a level" << endl;

    std::cout << std::string(' ',44) << "Inventory Controls" << endl;
    std::cout << std::string(' ',44) << "__________________" << endl;
    std::cout << "U - Use item" << endl;
    std::cout << "W - Equip item" << endl;
    std::cout << "D - Drop item" << endl;

    std::cout << std::string(' ',44) << "Equipment Controls" << endl;
    std::cout << std::string(' ',44) << "__________________" << endl;
    std::cout << "ESC - Return to map" << endl;
    std::cout << "W - Unequip item" << endl;

    std::cout << endl;


    std::cout << "Press enter to begin the game..." << endl;
    std::cin.sync();
    std::cin.get();

    return;
}

void clearScreen()
{
    wait(2);
    std::cout << std::string(SCREEN_HEIGHT, '\n');
    return;
}

void wait(int sec)
{
    clock_t endwait;
    endwait = clock() + sec * CLK_TCK;
    while (clock() < endwait)
        {
        }
    return;
}

void printTitle()                                           //Slightly fancier title :)
{
    char title[25][80];

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            title[i][j] = '#';
            if ((i == 12 && (j <= 46 && j >= 33))
                || (i == 14 && (j <= 46 && j >= 33)))
            {
                title[i][j] = ' ';
            }
        }
    }
    title[13][33] = ' ';
    title[13][34] = 'S';
    title[13][35] = 'E';
    title[13][36] = 'I';
    title[13][37] = 'Z';
    title[13][38] = 'U';
    title[13][39] = 'R';
    title[13][40] = 'E';
    title[13][41] = ' ';
    title[13][42] = 'T';
    title[13][43] = 'I';
    title[13][44] = 'M';
    title[13][45] = 'E';
    title[13][46] = ' ';

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            cout << title[i][j];
        }
    }
}

 /***************
 * Enemy Stuff! *
 ***************/

void Control::enemyPatrol(int& x, int& y)
{
    int moveChoice; //what way to move
    //chose a move and check if it is valid, if not, choose again
    while (floorMap[y][x] != ACS_BLOCK)
    {
        moveChoice = rand() % 7; //0 - 7

        switch (moveChoice)
        {
        case 0: //up
            y -= 1;
        case 1: //u-r
            y -= 1;
            x += 1;
        case 2: //right
            x += 1;
        case 3: //d-r
            y += 1;
            x += 1;
        case 4: //down
            y += 1;
        case 5: //d-l
            y += 1;
            x -= 1;
        case 6: //left
            x -= 1;
        case 7: //u-l
            y -= 1;
            x -= 1;
        default: //move up on default
            y -= 1;
        }
    }
}

bool Control::checkNextTiles(int x, int y)
{
    bool ATTACK = false; //return true if attacking is possible for melee

    //check for the player's display char (not player obj!)
    if (floorMap[y - 1][x] == ACS_LANTERN) //if player is U
    {
        ATTACK = true;
    }
    else if (floorMap[y - 1][x + 1] == ACS_LANTERN) //if player is UR
    {
        ATTACK = true;
    }
    else if (floorMap[y][x + 1] == ACS_LANTERN) //if player is R
    {
        ATTACK = true;
    }
    else if (floorMap[y + 1][x + 1] == ACS_LANTERN) //if player is DR
    {
        ATTACK = true;
    }
    else if (floorMap[y + 1][x] == ACS_LANTERN) //if player is D
    {
        ATTACK = true;
    }
    else if (floorMap[y + 1][x - 1] == ACS_LANTERN) //if player is DL
    {
        ATTACK = true;
    }
    else if (floorMap[y][x - 1] == ACS_LANTERN) //if player is L
    {
        ATTACK = true;
    }
    else if (floorMap[y - 1][x - 1] == ACS_LANTERN) //if player is UL
    {
        ATTACK = true;
    }

    return ATTACK;
}

void Control::enemyPursuit(int& enemyX, int& enemyY, int playerX, int playerY)
{
    bool horizMove = false, vertMove = false, diagMove = false;
    int horiz = 0, vert = 0; //this will be a +1 or -1

    //first check if horizontal move can be made
    if (enemyX != playerX)
    {
        if(enemyX > playerX) //enemy is to the right of the player
        {
            if(floorMap[enemyY][enemyX-1] == '.') //if space is empty, horiz bool is good
            {
                horiz = -1;
                horizMove = true;
            }
        }
        else //enemy is to the left of the player
        {
            if(floorMap[enemyY][enemyX+1] == '.') //if space is empty, horiz bool is good
            {
                horiz = 1;
                horizMove = true;
            }
        }
    } //end horizontal check

    //second, check if vertical move can be made
    if (enemyY != playerY)
    {
        if(enemyY > playerY) //enemy is below the player
        {
            if(floorMap[enemyY-1][enemyX] == '.') //if space is empty, vert bool is good
            {
                vert = -1;
                vertMove = true;
            }
        }
        else //enemy is above the player
        {
            if(floorMap[enemyY+1][enemyX] == '.') //if space is empty, vert bool is good
            {
                vert = 1;
                vertMove = true;
            }
        }
    }//end of vert check

    //third, check if diagnol move can be made(has to pass both horizontal and vertical tests)
    if (horizMove && vertMove) //if both those moves were legal, check if a diagnol move is allowed
    {
        if (floorMap[enemyY + vert][enemyX + horiz] =='.') //if diagnol move is good, set diagnol bool
        {
            diagMove = true;
        }
    }//end of diag check

    if (diagMove) //if diagnol move is legal, move
    {
        enemyX += horiz;
        enemyY += vert;
    }
    else if (horizMove) //if no diagnol, but horizontal move is legal, move
    {
        enemyX += horiz;
    }
    else if (vertMove) //if no diagnol, but vert move is legal, move
    {
        enemyY += vert;
    }
    //should not be an else, because if no move is valid, nothing will happen
}

void Control::meleeAIFrame()
{
    /**
    parts are commented out to show what they do, but have not been implemented yet

    int damageDone = 0;

    if(enemy.isSeenByPlayer()) //player is seen
    {
        if( checkNextTiles(enemy.x, enemy.y)) //is melee next to player? if so, attack!
        {
            damageDone = enemy.attack();
        }
        else //chase the player
        {
            enemyPursuit(enemy.x, enemy.y, player.x, player.y);
        }
    }
    else
    {
        enemyPatrol(enemy.x, enemy.y)
    }
    */
}
