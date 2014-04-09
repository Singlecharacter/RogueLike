#include "Player.h"
#include <math.h>

Player::Player(int x, int y, int HD , int MD,
               int STRMod, int DEXMod, int INTMod,
               int ACMod, int MRMod, int ACGain, int MRGain)
{
    sightRange = 5;
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
    The amounts gained are detemined by ACGain and MRGain. ACGain and MRGain should be small values.
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
    Item noItem("");
    for(int i = 0;i<RIGHTRING;i++)
    {
        equipment[i] = noItem;
    }

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            sightArray[j][i] = 0;
        }
    }
}

Player::~Player()
{

}

void Player::hurt(int damage)
{
    currentHP -= damage;
}

int Player::calculatePhysicalDamage(int damage)
{
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

    return realDamage;
}

int Player::calculateMagicDamage(int damage)
{
    int realDamage;

    if(MR > 0)
    {
        realDamage = damage - (rand() % (MR+1)) - 1.5*sqrt(MR);
    }
    else
    {
        realDamage = damage;
    }


    if(realDamage < 0)
    {
        realDamage = 0;
    }

    return realDamage;
}

void Player::poisonChange(int poisonAmount)
{
    poisonLevel += poisonAmount;
    if(poisonLevel > 300)
    {
        poisonLevel = 300;
    }
    else if(poisonLevel < 0)
    {
        poisonLevel = 0;
    }
}

int Player::calculatePoisonDamage()
{
    int hits = 0;
    int adjustedLevel;
    if(poisonLevel >= 200)
    {
        hits += 2;
        adjustedLevel = poisonLevel - 200;
    }
    else if(poisonLevel >= 100)
    {
        hits += 1;
        adjustedLevel = poisonLevel - 200;
    }
    else
    {
        adjustedLevel = poisonLevel;
    }

    if((rand() % 100) + 1 < adjustedLevel)
    {
        hits += 1;
    }

    return hits;
}

void Player::calculateSightRange(int levelArray[200][200])
{
    /*std::ofstream sightLog;
    sightLog.open("sightlog.txt",std::ofstream::app);
    sightLog << std::endl;

    sightLog << "Map: " << std::endl;

    char ch;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            if(levelArray[y-5+j][x-5+i] == ACS_BLOCK)
            {
                ch = '#';
            }
            else
            {
                ch = levelArray[y-5+j][x-5+i];
            }
            sightLog << ch;
        }
        sightLog << std::endl;
    }*/

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<11;j++)
        {
            sightArray[j][i] = 0;
        }
    }

    //Player spot
    sightArray[5][5] = 1;

    //Straight left
    for(int i = 0;i<sightRange;i++)
    {
        sightArray[5][5-(i+1)] = 1;
        if(levelArray[y][x-(i+1)] == ACS_BLOCK)
        {
            break;
        }
    }

    //Straight right
    for(int i = 0;i<sightRange;i++)
    {
        sightArray[5][5+(i+1)] = 1;
        if(levelArray[y][x+(i+1)] == ACS_BLOCK)
        {
            break;
        }
    }

    //Straight up
    for(int i = 0;i<sightRange;i++)
    {
        sightArray[5-(i+1)][5] = 1;
        if(levelArray[y-(i+1)][x] == ACS_BLOCK)
        {
            break;
        }
    }

    //Straight down
    for(int i = 0;i<sightRange;i++)
    {
        sightArray[5+(i+1)][5] = 1;
        if(levelArray[y+(i+1)][x] == ACS_BLOCK)
        {
            break;
        }
    }

    //Upper left diagonal
    sightArray[4][4] = 1;
    if(levelArray[y-1][x-1] != ACS_BLOCK)
    {
        sightArray[3][3] = 1;
    }

    //Upper right diagonal
    sightArray[4][6] = 1;
    if(levelArray[y-1][x+1] != ACS_BLOCK)
    {
        sightArray[3][7] = 1;
    }

    //Lower left diagonal
    sightArray[6][4] = 1;
    if(levelArray[y+1][x-1] != ACS_BLOCK)
    {
        sightArray[7][3] = 1;
    }

    //Lower right diagonal
    sightArray[6][6] = 1;
    if(levelArray[y+1][x+1] != ACS_BLOCK)
    {
        sightArray[7][7] = 1;
    }

    //Cone checks
    int upTurn = 0,downTurn = 0,leftTurn = 0,rightTurn = 0;

    //Left cone
    for(int i = 0;i<sightRange;i++)
    {
        if(levelArray[y][x-1-i] == ACS_BLOCK)
        {//We can't see this way!
            break;
        }
        else
        {
            //Up
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[4-j][4-i] = 1;
                if(levelArray[y-1-j][x-1-i] == ACS_BLOCK)
                {
                    upTurn = 1;
                    break;
                }
                else
                {
                    if(upTurn == 1)
                    {
                        break;
                    }
                }
            }

            //Down
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[6+j][4-i] = 1;
                if(levelArray[y+1+j][x-1-i] == ACS_BLOCK)
                {
                    downTurn = 1;
                    break;
                }
                else
                {
                    if(downTurn == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    //Right cone
    upTurn = 0;
    downTurn = 0;
    for(int i = 0;i<sightRange;i++)
    {
        if(levelArray[y][x+1+i] == ACS_BLOCK)
        {//We can't see this way!
            break;
        }
        else
        {
            //Up
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[4-j][6+i] = 1;
                if(levelArray[y-1-j][x+1+i] == ACS_BLOCK)
                {
                    upTurn = 1;
                    break;
                }
                else
                {
                    if(upTurn == 1)
                    {
                        break;
                    }
                }
            }

            //Down
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[6+j][6+i] = 1;
                if(levelArray[y+1+j][x+1+i] == ACS_BLOCK)
                {
                    downTurn = 1;
                    break;
                }
                else
                {
                    if(downTurn == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    //Up cone
    for(int i = 0;i<sightRange;i++)
    {
        if(levelArray[y-1-i][x] == ACS_BLOCK)
        {//We can't see this way!
            break;
        }
        else
        {
            //Left
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[4-i][4-j] = 1;
                if(levelArray[y-1-i][x-1-j] == ACS_BLOCK)
                {
                    leftTurn = 1;
                    break;
                }
                else
                {
                    if(leftTurn == 1)
                    {
                        break;
                    }
                }
            }

            //Right
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[4-i][6+j] = 1;
                if(levelArray[y-1-i][x+1+j] == ACS_BLOCK)
                {
                    rightTurn = 1;
                    break;
                }
                else
                {
                    if(rightTurn == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    //Down cone
    leftTurn = 0;
    rightTurn = 0;
    for(int i = 0;i<sightRange;i++)
    {
        if(levelArray[y+1+i][x] == ACS_BLOCK)
        {//We can't see this way!
            break;
        }
        else
        {
            //Left
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[6+i][4-j] = 1;
                if(levelArray[y+1+i][x-1-j] == ACS_BLOCK)
                {
                    leftTurn = 1;
                    break;
                }
                else
                {
                    if(leftTurn == 1)
                    {
                        break;
                    }
                }
            }

            //Right
            for(int j = 0;j<sightRange-1-i;j++)
            {
                sightArray[6+i][6+j] = 1;
                if(levelArray[y+1+i][x+1+j] == ACS_BLOCK)
                {
                    rightTurn = 1;
                    break;
                }
                else
                {
                    if(rightTurn == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    //Log the sight range
    /*sightLog << std::endl << "Sight:" << std::endl;
    for(int i = 0;i<11;i++)
    {
        for(int j = 0;j<11;j++)
        {
            sightLog << sightArray[i][j];
        }
        sightLog << std::endl;
    }*/


    //sightLog.close();

}

void Player::logStats()
{
    std::ofstream statsFile;
    statsFile.open("stats.txt",std::ofstream::app);

    statsFile << "Max HP: " << maxHP << std::endl;
    statsFile << "Max MP: " << maxMP << std::endl;
    statsFile << "STR: " << STR << std::endl;
    statsFile << "DEX: " << DEX << std::endl;
    statsFile << "INT: " << INT << std::endl;
    statsFile << std::endl;

    statsFile.close();
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
