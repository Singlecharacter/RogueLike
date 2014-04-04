#include <curses.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Item.h"

#define SCREEN_HEIGHT 25

/*

Here's the menu. If there are any improvements you'd like me to make, let me know.
You're also free to make them yourself.
I would've used Curses for all of this, but printing all of that stuff to the screen would've
taken an exponentially larger amount of code.
Let me know what you think or if I missed anything.

*/





using namespace std;

void clearScreen();                                   //Clears screen
void wait(int sec);                                   //Waits 'sec' number of seconds
Player runMenu();                                    //Menu functionality wrapped up

/*
COMMENTED MAIN() OUT BECAUSE I WAS ONLY USING IT FOR TESTS
int main()
{
    runMenu();
    return 0;
}
*/



//__________________________FUNCTION DEFINITIONS____________________________

Player runMenu()
{
    int raceChoice = 1;
    int typeChoice = 1;
    string racePrint = "";
    string typePrint = "";
    Player characterPlayer;

    cout << setw(64) << "*******************SEIZURE TIME********************" << endl;
    cout << endl;
    cout << endl;
    cout << "Select Your Race" << endl;
    cout << "_______________________________" << endl;
    cout << "1. Race type 1" << endl;
    cout << setw(35) << "-Attributes about race, etc." << endl;
    cout << endl;
    cout << "2. Race type 2" << endl;
    cout << endl;
    cout << "N. Race type N" << endl;                                //'N' is just a placeholder, this will continue until...
    cout << endl;                                                         //...the last race we decide on
    cin >> raceChoice;

    switch (raceChoice)                                         //Race Switch Statement
    {
        case 1     :cout << "You have chosen [race 1]" << endl;
                    //Set Race 1 attributes...
                    racePrint = " Race 1 ";
                    break;

        case 2     :cout << "You have chosen [race 2]" << endl;
                    //Set Race 2 attributes
                    racePrint = " Race 2 ";
                    break;

        default    :cout << "You have chosen [race 1]" << endl;
                    raceChoice = 1;
                    //Set Race 1 attributes...
                    racePrint = " Race 1 ";
                    break;
    }

    clearScreen();


    cout << "Select Your Type" << endl;
    cout << "_______________________________" << endl;
    cout << "1. Melee" << endl;
    cout << setw(35) << "-Melee attributes..." << endl;
    cout << endl;
    cout << "2. Mage" << endl;
    cout << setw(35) << "-Mage attributes..." << endl;
    cout << endl;
    cout << "3. Thief" << endl;                                   //Can't remember what we wanted to call the melee type
    cout << setw(35) << "-Thief attributes..." << endl;
    cout << endl;
    cin >> typeChoice;



    switch (typeChoice)                                         //Basic switch statement with default going back to 1st type
    {
        case 1     :cout << "You are a melee." << endl;          //"You are a melee.....?" lol
                    //Set melee attributes...
                    typePrint = "Melee.";
                    break;

        case 2     :cout << "You are a mage." << endl;
                    //Set mage attributes...
                    typePrint = "Mage.";
                    break;

        case 3     :cout << "You are a thief." << endl;
                    //Set thief attributes...
                    typePrint = "Thief.";
                    break;

        default    :cout << "You are a melee by default." << endl;
                    raceChoice = 1;
                    //Set melee attributes...
                    typePrint = "Melee.";
                    break;
    }


    clearScreen();

    cout << "You are a" << racePrint << typePrint << endl;


    clearScreen();

    cout << setw(40) << "Controls" << endl;
    cout << setw(40) << "________" << endl;
    cout << "A list of commands..." << endl;
    cout << "--" << endl;
    cout << "--" << endl;
    cout << "--" << endl;
    cout << "--" << endl;
    cout << "--" << endl;

    cout << endl;


    cout << "Press enter to begin the game..." << endl;
    cin.sync();
    cin.get();

    return characterPlayer;
}

void clearScreen()
{
    wait(2);
    cout << string(SCREEN_HEIGHT, '\n');
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
