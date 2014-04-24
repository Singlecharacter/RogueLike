#include "meleeHumanoid.h"

meleeHumanoid::meleeHumanoid (int playerLevel = 0, int xCoord = 0, int yCoord = 0, int currentMapLevel = 1)
{
	//assign variables
    enemyType = "mh"; //enemyType equals "mh"
    level = playerLevel; //level equals playerLevel
    x = xCoord; //x equals xCoord
    y = yCoord; //y equals yCoord

/** commented out for testing
    //first, if the rarity of the enemy is not appropriate for the mapLevel, adjust it
    //rare enemies won't spawn until level 2, epic to level 3, and bosses to level 4
    while ((rarity > currentMapLevel))
    {
        rarity = (rand() % 4) + 1;
    }
*/

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
		//a humanoid is stronger than creatures so put in a balancer

    //using an equation using rarity, and level, and a rand, assign power
    int basePower = 9; //melee has more attack than ranged

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
    int baseDefense = 10; //melee has more defense

	defense = baseDefense; //set the defense

	//adjust for the level
	for (int i = 1; i < level; i++) //i = 1 to account for starting at lvl 1
    {
		defense += rand() % baseDefense;
    }

    //now adjust for the rarity
    rareMod = ((rarity / 3) + .5);
    defense = defense * rareMod;

	//assign accuracy ( a rand between 70% and 80% ) for the humanoid
	int hiVal = 80, lowVal = 70;
	accuracy = (rand() % (hiVal - lowVal)) + lowVal;

	//run the getNameAndChar() function to get the name and displayChar
	getNameAndChar();
}

meleeHumanoid::~meleeHumanoid()
{

}


void meleeHumanoid::BossRoll()
{
    //make a roll from 0 - 10
	int roll = rand() % 11;

	//if the roll is good, adjust stats and add to the attackMessage
	if (roll == 10)
    {
		//enemyAttackTurn is: enemyAttackTurn + " and it enraged!"
		enemyAttackTurn += " and it enraged!";

		//up the stats for enrage
		int hiVal = 30, lowVal = 10;//top and bottom percentages
		int percInc = (rand() % (hiVal - lowVal)); //get a random value between hiVal and lowVal
		double decInc = percInc * .01; //this is the decimal for math, like 16% is .16

        power += power * decInc; //power increases by a rand of 10% to 30%
		defense += defense * decInc; //defense increases by a rand of 10% to 30%
		accuracy -= accuracy * decInc; //accuracy falls by a rand of 10% to 30%
    }
    else
    {
        enemyAttackTurn += ".";
    }
}

int meleeHumanoid::attackPlayer()
{
    int damageDone = 0;
    int accuracyRoll = rand() % 101; //0-100

    //if the enemy's accuracy roll is good, do damage
    if(accuracyRoll <= accuracy)
    {
        enemyAttackTurn += name + " has attacked";
        //do damage
        damageDone = rand() % power + 1; //1-powerMax

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
