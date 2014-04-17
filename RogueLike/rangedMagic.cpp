#include "rangedMagic.h"

rangedMagic::rangedMagic (int playerLevel = 0, int xCoord = 0, int yCoord = 0, int currentMapLevel = 1)
{
	//assign variables
    enemyType = "rm"; //enemyType equals "rm"
    level = playerLevel; //level equals playerLevel
    x = xCoord; //x equals xCoord
    y = yCoord; //y equals yCoord

    //first, if the rarity of the enemy is not appropriate for the mapLevel, adjust it
    while ((rarity == 4 && currentMapLevel >= 3) || (rarity == 3 && currentMapLevel >= 2))
    {
        rarity = (rand() % 4) + 1;
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
		//a magic user is stronger than archers so put in a balancer
		//generally, all ranged users are less powerful than melee (about 75% ?)

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

	//assign accuracy ( a rand between 55% and 70% ) for the magic user
	//accuracy is lowest for magic due to large power and range
	int hiVal = 70, lowVal = 55;
	accuracy = (rand() % (hiVal - lowVal)) + lowVal;

	//assign moveSpeed
	//ranged enemies are at base speed since they can attack player as soon as he enters LOS
	speed = 0;
    moveSpeed = speed;
    currentMoveSpeed = 0;

	//run the getNameAndChar() function to get the name and displayChar
	getNameAndChar();
}

rangedMagic::~rangedMagic()
{

}

void rangedMagic::BossRoll()
{
    //make a roll from 0 - 10
	int roll = rand() % 11;

	//if the roll is good, heal and add to the attackMessage
	if (roll == 10)
    {
		//enemyAttackTurn is: enemyAttackTurn + " and it healed itself!"
		enemyAttackTurn += " and it healed itself!";

		//heal 10% of hp
		int healhp = ceil(maxhp/10); //get 10% of the max hp, and round up
		currenthp += healhp; //heal with that 10%
		//Example:
		//maxhp = 25, currenthp = 17, 10% of 25 is 2.5, round up to 3, 17 + 3 = 20
    }
    else
    {
        enemyAttackTurn += ".";
    }
}
