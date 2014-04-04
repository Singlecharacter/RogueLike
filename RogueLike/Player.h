#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <curses.h>
#include <iostream>

class Player
{
public:

    //See constructor documentation
    Player(int x = 0, int y = 0, int HD = 10, int MD = 5,
           int STRMod = 0, int DEXMod = 0, int INTMod = 0,
           int ACMod = 0, int MRMod = 0, int ACGain = 0, int MRGain = 0);

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
    void calculateSightRange(int levelArray[25][80]);

    void setAC(int newAC);
    int getAC();

    int x, y;

    //Sight range
    int sightArray[11][11];

private:

    //Stat information
    int maxHP, currentHP, HD, maxMP, currentMP, MD, sightRange, STR, DEX, INT, AC, MR, poisonLevel, ACGain, MRGain;

    //Equipment slots
    Item mainHand, offHand, bodySlot, headSlot, feetSlot, handSlot, backSlot, neckSlot, leftRing, rightRing;
};

#endif // PLAYER_H
