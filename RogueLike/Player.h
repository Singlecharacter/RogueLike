#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

class Player
{
public:

    Player(int x = 0, int y = 0, int HD = 10, int MD = 5,
           int STRMod = 0, int DEXMod = 0, int INTMod = 0,
           int ACMod = 0, int MRMod = 0, int ACGain = 0, int MRGain = 0);

    ~Player();

    //Hurts the player for damage. Affected by AC.
    int hurt(int damage);

    //Sets the player's HP to maxHP
    void fullHeal();

    void setAC(int newAC);
    int getAC();

    int x, y;

private:

    //Stat information
    int maxHP, currentHP, HD, maxMP, currentMP, MD, visionRange, STR, DEX, INT, AC, MR, poisonLevel, ACGain, MRGain;

    //Equipment slots
    Item mainHand, offHand, bodySlot, headSlot, feetSlot, handSlot, backSlot, neckSlot, leftRing, rightRing;
};

#endif // PLAYER_H
