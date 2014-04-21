#include <ctime>
#include "Control.h"

int main()
{
    srand(time(NULL));

    Control control;

    control.introMenu();
    control.startCurses();
    control.loadNewFloor();
    control.getObjects();
    control.spawnPlayer();
    while(control.processInput());
    control.endCurses();
    control.debugLog();

    return 0;
}
