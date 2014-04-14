#ifndef CONTROL_H
#define CONTROL_H

#include <vector>
#include <string>

/*
Control is an organizational class that will handle most of the actual running of the game,
including things like window display, menus, enemy spawning, and enemy AI.
*/


class Control
{
public:

    Control();
    ~Control();


    void printScreen();
    void playerMenu();

    void spawnEnemies();

    //gameFrame runs a single frame of the game, simulating enemy AI and updating positions, the map, and the log accordingly
    void gameFrame();
    //The AI functions will move enemies and, if applicable, make them attack the player.
    void meleeAIFrame();
    void rangedAIFrame();


    void getObjects();

    void logMessage(string);



private:

    int numberOfTurns; //For log/testing purposes
    int levelArray[200][200];
    int currentEnemies, enemyCap;

    Player myPlayer;

    vector<string> log;

    vector<Chest> chests;
    vector<Wall> walls;
    //vector<Enemy> enemies;

};
#endif // CONTROL_H
