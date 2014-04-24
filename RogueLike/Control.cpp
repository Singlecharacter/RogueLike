#include "Control.h"


void printTitle();            //Control object doesn't use these directly; the introMenu method does
void wait(int sec);
void clearScreen();

std::string intToString(int);



Control::Control() : currentFloor(1), currentEnemies(0), enemyCap(10), numberOfTurns(0), floorWidth(200), floorHeight(200),
                     mapHeight(19),mapWidth(51),logHeight(6),logWidth(51),statusHeight(25),statusWidth(29),invHeight(25),invWidth(80),
                     mapStartX(0),mapStartY(0),logStartX(0),logStartY(19),statusStartX(51),statusStartY(0),invStartX(0),invStartY(0),
                     equipWidth(80),equipHeight(25),equipStartX(0),equipStartY(0),equippingItem(false),droppingItem(false)
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
    init_pair(2,COLOR_CYAN,COLOR_BLACK);
    mapWin = newwin(mapHeight,mapWidth,mapStartY,mapStartX);
    logWin = newwin(logHeight,logWidth,logStartY,logStartX);
    statusWin = newwin(statusHeight,statusWidth,statusStartY,statusStartX);
    invWin = newwin(invHeight,invWidth,invStartY,invStartX);
    equipWin = newwin(equipHeight,equipWidth,equipStartY,equipStartX);
    cbreak();
    nodelay(mapWin,true);
    keypad(mapWin,true);
    wbkgd(mapWin,COLOR_PAIR(1));
    wbkgd(logWin,COLOR_PAIR(1));
    wbkgd(statusWin,COLOR_PAIR(1));
    wbkgd(invWin,COLOR_PAIR(1));
    wbkgd(invWin,COLOR_PAIR(1));
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

    for(int i = 0;i<meleeCreatures.size();i++)
    {
        if(meleeCreatures.at(i).isSeenByPlayer(player))
        {
            wmove(mapWin,centerY+meleeCreatures.at(i).y-player.y,centerX+meleeCreatures.at(i).x-player.x);
            waddch(mapWin,meleeCreatures.at(i).getDisplayChar());
        }
    }

    wmove(mapWin,centerY,centerX);
    waddch(mapWin,ACS_LANTERN | COLOR_PAIR(2));

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

    char *tempStatCStr;

    for(int i = 0; i < statusHeight; i++)            //Clear Status Window
    {
        for(int j = 0; j < statusWidth; j++)
        {
            wmove(statusWin, i, j);
            waddch(statusWin, ' ');
        }
    }

    string health = "HP: ";
    string name = player.getName();
    string mana = "MP: ";
    string strength = "STR: ";
    string dexterity = "DEX: ";
    string intellect = "INT: ";
    string ac = "AC: ";
    string mr = "MR: ";

    health += intToString(player.getCurrentHP());        //Set Up Health Stat
    health += "/";
    health += intToString(player.getMaxHP());

    mana += intToString(player.getCurrentMP());         //Set Up Mana Stat
    mana += "/";
    mana += intToString(player.getMaxMP());

    strength += intToString(player.getSTR());           //...Strength

    dexterity += intToString(player.getDEX());         //...Dexterity

    intellect += intToString(player.getINT());         //...Intellect

    ac += intToString(player.getAC());                 //...AC

    mr += intToString(player.getMR());                 //...MR


    tempStatCStr = new char[name.length()+1];          //Output Name
    strcpy(tempStatCStr, name.c_str());
    wmove(statusWin, 1, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[health.length()+1];          //Output Health
    strcpy(tempStatCStr, health.c_str());
    wmove(statusWin, 2, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[mana.length()+1];          //Output Mana
    strcpy(tempStatCStr, mana.c_str());
    wmove(statusWin, 3, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[strength.length()+1];          //Output Strength
    strcpy(tempStatCStr, strength.c_str());
    wmove(statusWin, 5, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[dexterity.length()+1];          //Output Dexterity
    strcpy(tempStatCStr, dexterity.c_str());
    wmove(statusWin, 6, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[intellect.length()+1];          //Output Intellect
    strcpy(tempStatCStr, intellect.c_str());
    wmove(statusWin, 7, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[ac.length()+1];          //Output AC
    strcpy(tempStatCStr, ac.c_str());
    wmove(statusWin, 8, 0);
    waddstr(statusWin, tempStatCStr);

    tempStatCStr = new char[mr.length()+1];          //Output MR
    strcpy(tempStatCStr, mr.c_str());
    wmove(statusWin, 9, 0);
    waddstr(statusWin, tempStatCStr);

    wrefresh(logWin);
    wrefresh(mapWin);
    wrefresh(statusWin);
}

void Control::printInvScreen()
{
    for(int i = 0;i<player.invSize;i++)
    {
        wmove(invWin,i,0);
        std::string tempStr = intToString(i+1) + " - " + player.inventory[i].getName();
        char * temp = new char[tempStr.length()+1];
        strcpy(temp,tempStr.c_str());
        waddstr(invWin,temp);
    }
}

void Control::printEquipScreen()
{
    for(int i = 0;i<10;i++)
    {
        wmove(equipWin,i,0);
        std::string tempStr = intToString(i+1) + " - " + player.equipment[i].getName();
        char * temp = new char[tempStr.length()+1];
        strcpy(temp,tempStr.c_str());
        waddstr(equipWin,temp);
    }
}

void Control::clearWindows()
{
    for(int i = 0;i<mapHeight;i++)
    {
        for(int j = 0;j<mapWidth;j++)
        {
            wmove(mapWin,i,j);
            waddch(mapWin,' ');
        }
    }
    for(int i = 0;i<logHeight;i++)
    {
        for(int j = 0;j<logWidth;j++)
        {
            wmove(logWin,i,j);
            waddch(logWin,' ');
        }
    }
    for(int i = 0;i<statusHeight;i++)
    {
        for(int j = 0;j<statusWidth;j++)
        {
            wmove(statusWin,i,j);
            waddch(statusWin,' ');
        }
    }
    for(int i = 0;i<equipHeight;i++)
    {
        for(int j = 0;j<equipWidth;j++)
        {
            wmove(equipWin,i,j);
            waddch(equipWin,' ');
        }
    }
    for(int i = 0;i<invHeight;i++)
    {
        for(int j = 0;j<invWidth;j++)
        {
            wmove(invWin,i,j);
            waddch(invWin,' ');
        }
    }

    wrefresh(mapWin);
    wrefresh(logWin);
    wrefresh(statusWin);
    wrefresh(invWin);
    wrefresh(equipWin);
}

void Control::getEmptyTiles()
{
    emptyXList.clear();
    emptyYList.clear();

    for(int i = 0;i<floorHeight;i++)
    {
        for(int j = 0;j<floorWidth;j++)
        {
            if(floorMap[i][j] == '.')
            {
                emptyXList.push_back(j);
                emptyYList.push_back(i);
            }
        }
    }
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
                temp = floorNames.at(0);                                                  //flags level as already loaded
            }

            else if (levelChoice == 2 && floorFlags[1] == false)                               //open level 2
            {
                temp = floorNames.at(1);
            }

            else if (levelChoice == 3 && floorFlags[2] == false)                               //open level 3
            {
                temp = floorNames.at(2);
            }
            else if (levelChoice == 4 && floorFlags[3] == false)                               //open level 4
            {
                temp = floorNames.at(3);
            }

            else if (levelChoice == 5 && floorFlags[4] == false)                               //open level 5
            {
                temp = floorNames.at(4);
            }

            else if (levelChoice == 6 && floorFlags[5] == false)                               //open level 6
            {
                temp = floorNames.at(5);
            }

            else if (levelChoice == 7 && floorFlags[6] == false)                               //open level 7
            {
                temp = floorNames.at(6);
            }

            else if (levelChoice == 8 && floorFlags[7] == false)                               //open level 8
            {
                temp = floorNames.at(7);
            }

            else if (levelChoice == 9 && floorFlags[8] == false)                               //open level 9
            {
                temp = floorNames.at(8);
            }

            else if (levelChoice == 10 && floorFlags[9] == false)                               //open level 10
            {
                temp = floorNames.at(9);
            }

            filename = new char[temp.length()+1];
            strcpy(filename,temp.c_str());
            level.open(filename);
        }
    }
    else
    {
        temp = "sokoban.txt";
        filename = new char[temp.length()+1];
        strcpy(filename,temp.c_str());
        level.open(filename);
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

    level.close();

    floorHeight = lineCounter;

    getEmptyTiles();
    clearObjects();
    clearEnemies();
    getObjects();
    spawnPlayer();
    printMapScreen();
}

void Control::spawnPlayer()
{
    int spawnIndex = rand() % emptyXList.size();

    player.x = emptyXList.at(spawnIndex);
    player.y = emptyYList.at(spawnIndex);
    emptyXList.erase(emptyXList.begin()+spawnIndex);
    emptyYList.erase(emptyYList.begin()+spawnIndex);
}

bool Control::processInput()
{
    bool validInput = true;
    bool actionMade = false;
    int input = ERR;
    if(screenState == MAPSCREEN)
    {
        int newX = player.x;
        int newY = player.y;

        input = wgetch(mapWin);if(player.getCurrentHP() > player.getMaxHP())
    {
        player.fullHeal();
    }

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
            openChest();
            actionMade = true;
        }
        else if(input == 'i' || input == 'I')
        {
            screenState = INVENTORY;
            equippingItem = false;
        }
        else if(input == 'e' || input == 'E')
        {
            screenState = EQUIPSCREEN;
        }
        else if(input == '>' || input == '<')
        {
            loadNewFloor();
            spawnPlayer();
            //currentFloor++;
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
        else
        {
            actionMade = true;
            int enemyIndex = -1;
            enemyIndex = place_meeting(newY,newX,meleeCreatures);
            if(enemyIndex >= 0)
            {
                newX = player.x;
                newY = player.y;
                if(1 + rand() % 100 < player.getAccuracy())
                {
                    int damage = rand() % player.getMaxMeleeDamage() + 1;
                    meleeCreatures.at(enemyIndex).hurtEnemy(damage);
                    logMessage("You hit the " + meleeCreatures.at(enemyIndex).getName() + "!");
                    if(meleeCreatures.at(enemyIndex).isDead())
                    {
                        logMessage("You kill the " + meleeCreatures.at(enemyIndex).getName() + "!");
                        meleeCreatures.erase(meleeCreatures.begin()+enemyIndex);
                    }
                }
                else
                {
                    logMessage("You miss the " + meleeCreatures.at(enemyIndex).getName() + ".");
                }
            }
        }

        player.x = newX;
        player.y = newY;
    }
    else if(screenState == INVENTORY)
    {
        input = wgetch(invWin);
        if(input == 'q' || input == 'Q')
        {
            screenState = MAPSCREEN;
        }
        else if(input == 'w' || input == 'W')
        {
            equippingItem = true;
        }
        else if(input == 'd' || input == 'D')
        {
            droppingItem = true;
        }
        else if(equippingItem)
        {
            equippingItem = false;
            if(input == '1')
            {
               player.equipItem(0);
            }
            else if(input == '2')
            {
                player.equipItem(1);
            }
            else if(input == '3')
            {
                player.equipItem(2);
            }
            else if(input == '4')
            {
                player.equipItem(3);
            }
            else if(input == '5')
            {
                player.equipItem(4);
            }
            else if(input == '6')
            {
                player.equipItem(5);
            }
            else if(input == '7')
            {
                player.equipItem(6);
            }
            else if(input == '8')
            {
                player.equipItem(7);
            }
            else if(input == '9')
            {
                player.equipItem(8);
            }
            else
            {
                validInput = false;
                equippingItem = true;
            }
        }
        else if(droppingItem)
        {
            droppingItem = false;
            if(input == '1')
            {
               player.dropItem(0);
            }
            else if(input == '2')
            {
                player.dropItem(1);
            }
            else if(input == '3')
            {
                player.dropItem(2);
            }
            else if(input == '4')
            {
                player.dropItem(3);
            }
            else if(input == '5')
            {
                player.dropItem(4);
            }
            else if(input == '6')
            {
                player.dropItem(5);
            }
            else if(input == '7')
            {
                player.dropItem(6);
            }
            else if(input == '8')
            {
                player.dropItem(7);
            }
            else if(input == '9')
            {
                player.dropItem(8);
            }
            else
            {
                validInput = false;
                droppingItem = true;
            }
        }
        else
        {
            validInput = false;
        }
    }
    else if(screenState == EQUIPSCREEN)
    {
        input = wgetch(equipWin);
        if(input == 'q' || input == 'Q')
        {
            screenState = MAPSCREEN;
        }
        else if(input == 'w' || input == 'W')
        {
            equippingItem = true;
        }
        else if(equippingItem)
        {

            if(input == '1')
            {
               player.unequipItem(0);
            }
            else if(input == '2')
            {
                player.unequipItem(1);
            }
            else if(input == '3')
            {
                player.unequipItem(2);
            }
            else if(input == '4')
            {
                player.unequipItem(3);
            }
            else if(input == '5')
            {
                player.unequipItem(4);
            }
            else if(input == '6')
            {
                player.unequipItem(5);
            }
            else if(input == '7')
            {
                player.unequipItem(6);
            }
            else if(input == '8')
            {
                player.unequipItem(7);
            }
            else if(input == '9')
            {
                player.unequipItem(8);
            }
            else
            {
                validInput = false;
                equippingItem = true;
            }
        }
        else
        {
            validInput = false;
        }
    }

    bool isNotDone = true;

    if(validInput)
    {
        clearWindows();

        if(screenState == MAPSCREEN)
        {
            if(actionMade)
            {
                isNotDone = gameFrame();
            }
            printMapScreen();
        }
        else if(screenState == INVENTORY)
        {
            printInvScreen();
        }
        else if(screenState == EQUIPSCREEN)
        {
            printEquipScreen();
        }
    }

    return isNotDone;
}

void Control::openChest()
{
    int foundIndex = place_meeting(player.y,player.x,chests);

    if(foundIndex < 0)
    {
        logMessage("There's nothing here to open.");
    }
    else
    {
        int emptyIndex = -1;
        for(int i = 0;i<player.invSize;i++)
        {
            if(player.inventory[i].getName() == "")
            {
                emptyIndex = i;
                break;
            }
        }

        if(emptyIndex >= 0)
        {
            chests.at(foundIndex).generateItem();
            player.inventory[emptyIndex] = chests.at(foundIndex).getItem();
            logMessage("You found a " + player.inventory[emptyIndex].getName());
            floorMap[player.y][player.x] = '.';
            clearObjects();
            getObjects();
        }
        else
        {
            logMessage("You don't have room for any more items.");
        }
    }
}

bool Control::gameFrame()
{
    //Player health and mana regeneration
    player.regenTimer++;
    if(player.regenTimer % 10 == 0)
    {
        player.hurt(-1);
    }

    if(player.regenTimer % 5 == 0)
    {
        player.hurtMana(-1);
    }

    if(player.getCurrentHP() > player.getMaxHP())
    {
        player.fullHeal();
    }

    if(player.getCurrentMP() > player.getMaxMP())
    {
        player.fullManaHeal();
    }

    getEmptyTiles();

    if(rand() % 10 == 4)
    {
        spawnEnemies();
    }

    for(int i = 0;i<meleeCreatures.size();i++)
    {
        meleeAIFrame(meleeCreatures.at(i));
    }

    if(player.getCurrentHP() <= 0)
    {
        return false;
    }

    return true;

    /**
        To run ai, run meleeAIFrame() for ALL melee enemies
        run rangedAIFrame() for ALL ranged enemies

        differentate using enemy.getEnemyType()
        will return mc or mh for melee & ra or rm for ranged
    */
}

void Control::spawnEnemies()
{
    if(currentEnemies < enemyCap)
    {
        int newEnemies = rand() % (enemyCap-currentEnemies);
        while(newEnemies > 0)
        {
            int tileIndex = rand() % emptyXList.size();
            meleeCreatures.push_back(meleeCreature(player.getLevel(),emptyXList.at(tileIndex),emptyYList.at(tileIndex),currentFloor));
            emptyXList.erase(emptyXList.begin()+tileIndex);
            emptyYList.erase(emptyYList.begin()+tileIndex);
            newEnemies--;
        }
        currentEnemies += newEnemies;
    }
}

void Control::clearObjects()
{
    walls.clear();
    chests.clear();
}

void Control::clearEnemies()
{
    meleeCreatures.clear();
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
    genLog << "Number of enemies: " << meleeCreatures.size() << std::endl;
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

void Control::enemyPatrol(int& enemyx, int& enemyy)
{
    int moveChoice; //what way to move
    //chose a move and check if it is valid, if not, choose again
    while (floorMap[enemyy][enemyx] != ACS_BLOCK)
    {
        moveChoice = rand() % 7; //0 - 7

        switch (moveChoice)
        {
        case 0: //up
            enemyy -= 1;
            break;
        case 1: //u-r
            enemyy -= 1;
            enemyx += 1;
            break;
        case 2: //right
            enemyx += 1;
            break;
        case 3: //d-r
            enemyy += 1;
            enemyx += 1;
            break;
        case 4: //down
            enemyy += 1;
            break;
        case 5: //d-l
            enemyy += 1;
            enemyx -= 1;
            break;
        case 6: //left
            enemyx -= 1;
            break;
        case 7: //u-l
            enemyy -= 1;
            enemyx -= 1;
            break;
        default: //move up on default
            enemyy -= 1;
        }
    }
}

bool Control::checkNextTiles(meleeCreature enemy)
{
    bool ATTACK = false; //return true if attacking is possible for melee

    //check for the player's display char (not player obj!)
    if (enemy.y - 1 == player.y && enemy.x == player.x) //if61299998790625884883 player is U
    {
        ATTACK = true;
    }
    else if (enemy.y - 1 == player.y && enemy.x + 1 == player.x) //if player is UR
    {
        ATTACK = true;
    }
    else if (enemy.y - 1 == player.y && enemy.x - 1 == player.x) //if player is R
    {
        ATTACK = true;
    }
    else if (enemy.y + 1 == player.y && enemy.x == player.x) //if player is DR
    {
        ATTACK = true;
    }
    else if (enemy.y + 1 == player.y && enemy.x + 1 == player.x) //if player is D
    {
        ATTACK = true;
    }
    else if (enemy.y + 1 == player.y && enemy.x - 1 == player.x) //if player is DL
    {
        ATTACK = true;
    }
    else if (enemy.y == player.y && enemy.x + 1 == player.x) //if player is L
    {
        ATTACK = true;
    }
    else if (enemy.y == player.y && enemy.x - 1 == player.x) //if player is UL
    {
        ATTACK = true;
    }

    return ATTACK;
}

void Control::enemyPursuit(meleeCreature &enemy)
{
    bool horizMove = false, vertMove = false, diagMove = false;
    int horiz = 0, vert = 0; //this will be a +1 or -1

    //first check if horizontal move can be made
    if (enemy.x != player.x)
    {
        if(enemy.x > player.x) //enemy is to the right of the player
        {
            if(floorMap[enemy.y][enemy.x-1] == '.') //if space is empty, horiz bool is good
            {
                horiz = -1;
                horizMove = true;
            }
        }
        else //enemy is to the left of the player
        {
            if(floorMap[enemy.y][enemy.x+1] == '.') //if space is empty, horiz bool is good
            {
                horiz = 1;
                horizMove = true;
            }
        }
    } //end horizontal check

    //second, check if vertical move can be made
    if (enemy.y != player.y)
    {
        if(enemy.y > player.y) //enemy is below the player
        {
            if(floorMap[enemy.y-1][enemy.x] == '.') //if space is empty, vert bool is good
            {
                vert = -1;
                vertMove = true;
            }
        }
        else //enemy is above the player
        {
            if(floorMap[enemy.y+1][enemy.x] == '.') //if space is empty, vert bool is good
            {
                vert = 1;
                vertMove = true;
            }
        }
    }//end of vert check

    //third, check if diagnol move can be made(has to pass both horizontal and vertical tests)
    if (horizMove && vertMove) //if both those moves were legal, check if a diagnol move is allowed
    {
        if (floorMap[enemy.y + vert][enemy.x + horiz] =='.') //if diagnol move is good, set diagnol bool
        {
            diagMove = true;
        }
    }//end of diag check

    if (diagMove) //if diagnol move is legal, move
    {
        enemy.x += horiz;
        enemy.y += vert;
    }
    else if (horizMove) //if no diagnol, but horizontal move is legal, move
    {
        enemy.x += horiz;
    }
    else if (vertMove) //if no diagnol, but vert move is legal, move
    {
        enemy.y += vert;
    }
    //should not be an else, because if no move is valid, nothing will happen
}

void Control::meleeAIFrame(meleeCreature enemy)
{
    int damageDone = 0;

    if(enemy.isSeenByPlayer(player)) //player is seen
    {
        if(checkNextTiles(enemy)) //is melee next to player? if so, attack!
        {
            damageDone = enemy.attackPlayer();
            logMessage(enemy.getEnemyAttackTurn());
        }
        else //chase the player
        {
            enemyPursuit(enemy);
        }
    }
    else
    {
        enemyPatrol(enemy.x, enemy.y);
    }

    player.hurt(player.calculatePhysicalDamage(damageDone));
}


void Control::rangedAIFrame()
{
    /**
    parts are commented out to show what they do, but have not been implemented yet

    int damageDone = 0;

    if (enemy.isSeenByPlayer) //if enemy is seen by the player
    {
        damageDone = enemy.attack(); //attack!
    }
    else //else, patrol
    {
        enemyPatrol(enemy.x, enemy.y);
    }
    */
}

std::string intToString(int num)
{
    if(num == 0)
    {
        return "0";
    }
    else
    {
        std::string temp = "";
        std::string ch = " ";
        while(num > 0)
        {
            ch[0] = (num % 10) + 48;
            temp.insert(0,ch);
            num = num / 10;
        }

        return temp;
    }
}
