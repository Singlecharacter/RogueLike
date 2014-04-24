#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>
#include <cstring>
#include <curses.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "Player.h"
#include "Chest.h"
#include "Wall.h"
#include "utility.cpp"

//enemies
#include "Enemy.h"
#include "meleeCreature.h"
#include "meleeHumanoid.h"
#include "rangedMagic.h"
#include "rangedArcher.h"

//screen state definitions
#define MAPSCREEN 0
#define INVENTORY 1
#define EQUIPSCREEN 2

#define SCREEN_HEIGHT 40

/*
Control is an organizational class that will handle most of the actual running of the game,
including things like window display, menus, enemy spawning, and enemy AI.
*/


class Control
{
public:

    Control();
    ~Control();

    void startCurses();
    void endCurses();
    void printMapScreen();
    void printInvScreen();
    void printEquipScreen();
    void clearWindows();
    void introMenu();

    void loadNewFloor();
    void loadOldFloor();
    void saveFloor();

    void spawnPlayer();

    void spawnEnemies();

    bool processInput();
    void openChest();

    //gameFrame runs a single frame of the game, accounting for things like menu choices.
    bool gameFrame();
    void activeFrame();
    void inventoryFrame();

    //The AI methods will move enemies and, if applicable, make them attack the player.
    void meleeAIFrame(meleeCreature);
    void rangedAIFrame();
    void enemyPatrol(int& enemyx, int& enemyy); //give new movement when not seen
    bool checkNextTiles(meleeCreature); //is the player on any of the tiles next to a melee enemy?
    void enemyPursuit(int& enemyx, int& enemyy); //make enemy chase the player

    void getEmptyTiles();


    void clearObjects();
    void clearEnemies();
    void getObjects();

    void debugLog();

    void logMessage(std::string);



private:

    int numberOfTurns; //For log/testing purposes

    //floorMap holds the tiles to be printed to the screeen
    int floorMap[200][200];

    //floorFlags stores whether a level has been previously loaded to avoid duplicates
    bool floorFlags[10];

    WINDOW *mapWin, *logWin, *statusWin, *invWin, *equipWin;
    int mapHeight,mapWidth,logHeight,logWidth,statusHeight,statusWidth,invHeight,invWidth,equipWidth,equipHeight;
    int mapStartX,mapStartY,logStartX,logStartY,statusStartX,statusStartY,invStartX,invStartY,equipStartX,equipStartY;

    int currentEnemies, enemyCap;

    int currentFloor,floorWidth,floorHeight;

    int screenState;

    bool equippingItem;
    bool droppingItem;

    vector<std::string> floorNames;

    Player player;

    vector<std::string> log;

    vector<Chest> chests;
    vector<Wall> walls;
    vector<meleeCreature> meleeCreatures;
    vector<int> emptyXList,emptyYList;

};
#endif // CONTROL_H
