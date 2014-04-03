#include "PlayerItems.h"
#include <math.h>

Player::Player(int x, int y, int HD , int MD,
               int STRMod, int DEXMod, int INTMod,
               int ACMod, int MRMod, int ACGain, int MRGain)
{
    visionRange = 5;
    poisonLevel = 0;

    srand(time(NULL));
    this -> x = x;
    this -> y = y;

    /*
    Max HP and MP are determined using base values HD and MD (Hit dice and magic dice).
    STR, DEX, and INT are all allocated semi-randomly using a semi-random stat cap.
    No attribute can be more than half of the stat cap or less than 5.
    Once attributes are allocated, modifiers are added, which are dependent upon class(and maybe race?)
    Players start with a base AC(Armor Class) and MR(Magic Resistance), and gain fixed amounts of each on level up.
    The amounts gained are detemined by ACGain and MRGain. Most likely, both ACGain and MRGain will be small values.
    */

    maxHP = HD + rand() % HD;
    currentHP = maxHP;
    this -> HD = HD;

    maxMP = rand() % MD + MD/2;
    currentMP = maxMP;
    this -> MD = MD;

    int statCap = rand() % 8 + 22;

    STR = rand() % statCap/2 + 5;
    if(STR > statCap/2)
    {
        STR = statCap/2;
    }
    statCap -= STR;

    DEX = rand() % statCap;
    if(DEX < 5)
    {
        DEX = 5;
    }
    statCap -= DEX;

    INT = statCap;

    STR += STRMod;
    DEX += DEXMod;
    INT += INTMod;

    AC = ACMod;
    MR = MRMod;
    this -> ACGain = ACGain;
    this -> MRGain = MRGain;

    //Equipment initialization (empty)
    Item noItem; //edited by Michael on 4/2/2014
    mainHand = noItem;
    offHand = noItem;
    bodySlot = noItem;
    headSlot = noItem;
    feetSlot = noItem;
    handSlot = noItem;
    backSlot = noItem;
    neckSlot = noItem;
    leftRing = noItem;
    rightRing = noItem;
}

Player::~Player()
{

}

int Player::hurt(int damage)
{
    /*
    Right now, damage is all treated the same, and is only affected by AC in a diminishingly increasing manner.

    Things to come:

    - Damage type differentiation
    - Crits
    - Poison
    -
    */
    int realDamage;

    if(AC > 0)
    {
        realDamage = damage - (rand() % (AC+1)) - 1.5*sqrt(AC);
    }
    else
    {
        realDamage = damage;
    }


    if(realDamage < 0)
    {
        realDamage = 0;
    }
    currentHP -= realDamage;

    return realDamage;
}

void Player::fullHeal()
{
    currentHP = maxHP;
}

void Player::setAC(int newAC)
{
    AC = newAC;
}

int Player::getAC()
{
    return AC;
}
