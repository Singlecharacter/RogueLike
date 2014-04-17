#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "Wall.h"
#include "Player.h"
#include "utility.h"
#include "Item.h"
#include "Chest.h"
#include "Control.h"

//Enemies
#include "Enemy.h"
#include "meleeCreature.h"
#include "meleeHumanoid.h"
#include "rangedMagic.h"
#include "rangedArcher.h"


using namespace std;

int main()
{
    srand(time(NULL));

    Control control;

    control.startCurses();
    control.loadNewFloor();
    control.getObjects();
    control.spawnPlayer();
    while(control.processInput());
    control.endCurses();
    control.debugLog();

    return 0;
}
