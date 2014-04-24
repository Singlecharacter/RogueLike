#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <math.h>
#include <curses.h>

#include "Item.h"

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
           int ACMod = 0, int MRMod = 0, int ACGain = 0, int MRGain = 0, std::string name = "");

    ~Player();

    //Hurts the player for damage.
    void hurt(int damage);
    void hurtMana(int amount);

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

    void fullManaHeal();

    //Determines which grid tiles the player can see from its current location.
    void calculateSightRange(int levelArray[200][200]);

    bool equipItem(int invSlot);

    void dropItem(int invSlot);

    //attempts to unequip the item at slot, returns false if there is no item or no room to unequip it.
    bool unequipItem(int slot);

    void calcStats();

    bool levelUp();
    void addXP(int xp);

    int getLevel();

    //Logs the player's stats to a file
    void logStats();

    void logItems();

    int getAC();
    int getMaxHP();
    int getCurrentHP();

    int getMaxMP();
    int getCurrentMP();

    int getAccuracy();
    int getMaxMeleeDamage();

    int getSTR();
    int getDEX();
    int getINT();
    int getMR();

    std::string getName();

    int x,y;

    //Sight range
    int sightArray[11][11];
    int sightRange;

    //Equipment slots
    Item equipment[10];
    Item *inventory;

    int invSize;

    int regenTimer;

private:

    //Stat information
    int maxHP, baseMaxHP, currentHP, HD, maxMP, baseMaxMP, currentMP, MD, STR, DEX, INT, AC, baseAC, MR, baseMR, poisonLevel, ACGain, MRGain;

    //Stats adjusted by items/potion effects
    int adjSTR,adjDEX,adjINT,purityLevel;

    int maxMeleeDamage,maxRangedDamage,maxMagicDamage, accuracy;

    int currentXP, neededXP, level;

    std::string name;
};

#endif // PLAYER_H
