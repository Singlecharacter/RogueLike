#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <curses.h>
#include <iostream>

#define MAINHAND 0
#define OFFHAND 1
#define BODYSLOT 2
#define HEADSLOT 3
#define FEETSLOT 4
#define HANDSLOT 5
#define BACKSLOT 6
#define NECKSLOT 7
#define RIGHTRING 8
#define LEFTRING 9
#define INVSIZE 25

class Player
{
public:

    //See constructor documentation
    Player(int x = 0, int y = 0, int HD = 10, int MD = 5,
           int STRMod = 0, int DEXMod = 0, int INTMod = 0,
           int ACMod = 0, int MRMod = 0, int ACGain = 0, int MRGain = 0, string name = "");

    ~Player();

    //Hurts the player for damage.
    void hurt(int damage);

    //Affected by AC. Returns the actual amount of damage to be dealt to the player.
    int calculatePhysicalDamage(int damage);

    //Affected by MR. Returns the actual amount of damage to be dealt to the player.
    int calculateMagicDamage(int damage);

    //Checks the player's poison level and returns the amount of poison damage to be dealt to the player.
    int calculatePoisonDamage();

    //Raises or lowers the player's poison level. Minimum level of 0 and maxium level of 300.
    void poisonChange(int poisonAmount);

    //Sets the player's HP to maxHP
    void fullHeal();

    //Determines which grid tiles the player can see from its current location.
    void calculateSightRange(int levelArray[200][200]);

    void equipItem(Item newItem);

    //Logs the player's stats to a file
    void logStats();

    void logItems();

    void setAC(int newAC);
    int getAC();

    int x,y;

    //Sight range
    int sightArray[11][11];

private:

    //Stat information
    int maxHP, currentHP, HD, maxMP, currentMP, MD, sightRange, STR, DEX, INT, AC, MR, poisonLevel, ACGain, MRGain;

    string name;

    //Equipment slots
    Item equipment[10];
    Item inventory[25];
};

#endif // PLAYER_H
