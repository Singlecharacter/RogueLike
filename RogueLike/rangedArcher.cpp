#include "rangedArcher.h"

rangedArcher::rangedArcher (int playerLevel = 0, int xCoord = 0, int yCoord = 0, int currentMapLevel = 1)
{
	//assign variables
    enemyType = "ra"; //enemyType equals "ra"
    level = playerLevel; //level equals playerLevel
    x = xCoord; //x equals xCoord
    y = yCoord; //y equals yCoord

    //first, if the rarity of the enemy is not appropriate for the mapLevel, adjust it
    while ((rarity == 4 && currentMapLevel >= 3) || (rarity == 3 && currentMapLevel >= 2))
    {
        rarity == (rand() % 4) + 1;
    }

    /****************
	* assign stats  *
	****************/

    /****************************
	* HEALTH                    *
    *                           *
	* examples of hp @ level 1  *
	* rarity 1 = 7              *
	* rarity 2 = 10             *
    * rarity 3 = 13             *
	* rarity 4 = 16             *
	****************************/

	int basehp = 9;

	maxhp = basehp; //set the basehp

	//adjust for the level
	for (int i = 1; i < level; i++) //i = 1 to account for starting at lvl 1
    {
		maxhp += rand() % basehp;
    }

    //now adjust for the rarity
    double rareMod = ((rarity / 3) + .5);
    maxhp = maxhp * rareMod;

    currenthp = maxhp;//now set the currenthp

    /*****************************
	* POWER                      *
    *                            *
	* examples of power @ level 1*
	* rarity 1 =                 *
	* rarity 2 =                 *
    * rarity 3 =                 *
	* rarity 4 =                 *
	*****************************/

	//using an equation using rarity, and level, and a rand, assign power
		//an archer is less strong than magic users so put in a balancer
		//generally, all ranged users are less powerful than melee

    //using an equation using rarity, and level, and a rand, assign power
    int basePower = 4; //melee has more attack than ranged

	power = basePower; //set the power

	//adjust for the level
	for (int i = 1; i < level; i++) //i = 1 to account for starting at lvl 1
    {
		power += rand() % basePower;
    }

    //now adjust for the rarity
    rareMod = ((rarity / 3) + .5);
    power = power * rareMod;


    /*****************************
	* DEFENSE                    *
    *                            *
	* examples of def @ level 1  *
	* rarity 1 =                 *
	* rarity 2 =                 *
    * rarity 3 =                 *
	* rarity 4 =                 *
	*****************************/

    //using an equation using rarity, and level, and a rand, assign defence
    int baseDefense = 7; //melee has more defense

	defense = baseDefense; //set the defense

	//adjust for the level
	for (int i = 1; i < level; i++) //i = 1 to account for starting at lvl 1
    {
		defense += rand() % baseDefense;
    }

    //now adjust for the rarity
    rareMod = ((rarity / 3) + .5);
    defense = defense * rareMod;

	//assign accuracy ( a rand between 80% and 95% ) for the magic user
	//accuracy is highest for archers due to low power and range
	int hiVal = 95, lowVal = 80;
	accuracy = (rand() % (hiVal - lowVal)) + lowVal;

	//run the getNameAndChar() function to get the name and displayChar
	getNameAndChar();
}

rangedArcher::~rangedArcher()
{

}

void rangedArcher::BossRoll()
{
    //make a roll from 0 - 10
	int roll = rand() % 11;

	//if the roll is good, adjust damage and add to the attackMessage
	if (roll == 10)
    {
        power = power * 2; //enemy's power doubles
        enemyAttackTurn += " and it found a kink in the armor!";
    }
    else
    {
        enemyAttackTurn += ".";
    }
}

int rangedArcher::attackPlayer()
{
    int damageDone = 0;
    int accuracyRoll = rand() % 101; //0-100

    //if the enemy's accuracy roll is good, do damage
    if(accuracyRoll >= accuracy)
    {
        enemyAttackTurn += name + " has attacked";
        //do damage

        //if enemy is a boss, do the boss roll
        if (rarity == 4)
        {
            BossRoll();
        }
        else
        {
            enemyAttackTurn += ".";
        }
    }
    else //miss!
    {
        enemyAttackTurn += name + " has missed it's attack.";
    }

    return damageDone;
}

