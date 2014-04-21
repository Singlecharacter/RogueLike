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
#include "utility.h"

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
    void introMenu();

    void loadNewFloor();
    void loadOldFloor();
    void saveFloor();

    void spawnPlayer();

    void spawnEnemies();

    bool processInput();

    //gameFrame runs a single frame of the game, accounting for things like menu choices.
    void gameFrame();
    void activeFrame();
    void inventoryFrame();

    //The AI methods will move enemies and, if applicable, make them attack the player.
    void meleeAIFrame();
    void rangedAIFrame();


    void clearObjects();
    void getObjects();

    void debugLog();

    void logMessage(std::string);



private:

    int numberOfTurns; //For log/testing purposes

    //floorMap holds the tiles to be printed to the screeen
    int floorMap[200][200];

    //floorFlags stores whether a level has been previously loaded to avoid duplicates
    bool floorFlags[10];

    WINDOW *mapWin, *logWin, *statusWin, *invWin;
    int mapHeight,mapWidth,logHeight,logWidth,statusHeight,statusWidth,invHeight,invWidth;
    int mapStartX,mapStartY,logStartX,logStartY,statusStartX,statusStartY,invStartX,invStartY;

    int currentEnemies, enemyCap;

    int currentFloor,floorWidth,floorHeight;

    int screenState;

    vector<std::string> floorNames;

    Player player;

    vector<std::string> log;

    vector<Chest> chests;
    vector<Wall> walls;
    //vector<Enemy> enemies;

};
#endif // CONTROL_H