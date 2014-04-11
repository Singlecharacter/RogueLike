#include <curses.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "Wall.h"
#include "utility.h"

using namespace std;

void levelLoad(int levelArray[200][200], bool levelFlagArray[10]);  //opens filestream and loads text level onto array
void levelCreate(int levelArray[200][200]);                                                 //initializes and displays screen with current level


/*
COMMENTED OUT
USED FOR TESTING

DO NOT DELETE UNTIL WE'RE IN THE FINAL
STAGES OF WORK

int main()
{
    int levelArray[200][200];                         //Changed this to 200x200 levels
    srand(time(NULL));
    bool levelFlagArray[10];                         //Used to flag whether or not a level has already been loaded


    for (int i = 0; i < 10; i++)                    //Initialized all flag values to false
    {
        levelFlagArray[i] = false;
    }

    levelLoad(levelArray, levelFlagArray);          //Load and display a random level

    return 0;
}
*/



//___________________ FUNCTION DEFINITIONS____________________

void levelLoad(int levelArray[200][200], bool levelFlagArray[10])
{
    int levelChoice = 1 + (rand()% 10);                                               //Random level selection
    ifstream level;

    if (levelChoice == 1 && levelFlagArray[0] == false)                               //open level 1
    {
        level.open("level1.txt");                                                  //displays level
        levelFlagArray[0] = true;                                                   //flags level as already loaded
    }

    else if (levelChoice == 2 && levelFlagArray[1] == false)                               //open level 2
    {
        level.open("level2.txt");
        levelFlagArray[1] = true;
    }

    else if (levelChoice == 3 && levelFlagArray[2] == false)                               //open level 3
    {
        level.open("level3.txt");
        levelFlagArray[2] = true;
    }

    else if (levelChoice == 4 && levelFlagArray[3] == false)                               //open level 4
    {
        level.open("level4.txt");
        levelFlagArray[3] = true;
    }

    else if (levelChoice == 5 && levelFlagArray[4] == false)                               //open level 5
    {
        level.open("level5.txt");
        levelFlagArray[4] = true;
    }

    else if (levelChoice == 6 && levelFlagArray[5] == false)                               //open level 6
    {
        level.open("level6.txt");
        levelFlagArray[5] = true;
    }

    else if (levelChoice == 7 && levelFlagArray[6] == false)                               //open level 7
    {
        level.open("level7.txt");
        levelFlagArray[6] = true;
    }

    else if (levelChoice == 8 && levelFlagArray[7] == false)                               //open level 8
    {
        level.open("level8.txt");
        levelFlagArray[7] = true;
    }

    else if (levelChoice == 9 && levelFlagArray[8] == false)                               //open level 9
    {
        level.open("level9.txt");
        levelFlagArray[8] = true;
    }

    else if (levelChoice == 10 && levelFlagArray[9] == false)                               //open level 10
    {
        level.open("level10.txt");
        levelFlagArray[9] = true;
    }

    char inChar;

    for(int i = 0; i < 200; i++)
    {
        for(int j = 0; j < 200; j++)
        {
            inChar = level.get();
            if(inChar == '#')
            {
                levelArray[i][j] = ACS_BLOCK;
            }
            else
            {
                levelArray[i][j] = inChar;
            }
        }
        level.ignore();
    }

    level.close();
}

