#include <curses.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#define SCREEN_HEIGHT 50


using namespace std;

void clearScreen();
void wait(int sec);
void runMenu();


int main()
{
    runMenu();
    return 0;
}




//__________________________FUNCTION DEFINITIONS____________________________

void runMenu()
{
    int playerChoice = 0;


    cout << setw(64) << "*******************SEIZURE TIME********************" << endl;
    cout << endl;
    cout << endl;
    cout << "Select your race/character type" << endl;
    cout << "_______________________________" << endl;
    cout << "1. Character type 1" << endl;
    cout << setw(35) << "-Attributes about character, etc." << endl;
    cout << endl;
    cout << "2. Character type 2" << endl;
    cout << "... N. Character type N" << endl;
    cout << endl;
    cin >> playerChoice;

    switch (playerChoice)
    {
        case 1     :cout << "You have chosen [character type 1]" << endl;
                    break;

        case 2     :cout << "You have chosen [character type 2]" << endl;
                    break;

        default    :cout << "You have chosen [character type 1]" << endl;
                    playerChoice = 1;
                    break;
    }

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
