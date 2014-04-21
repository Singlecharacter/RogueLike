#include "meleeCreature.h"

meleeCreature::meleeCreature (int playerLevel = 0, int xCoord = 0, int yCoord = 0, int currentMapLevel = 1)
{
	//assign variables
    enemyType = "mc"; //enemyType equals "mc"
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
		//a creature is less strong than humanoids so put in a balancer

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

	//assign accuracy ( a rand between 70% and 90% ) for the creature
	int hiVal = 90, lowVal = 70;
	accuracy = (rand() % (hiVal - lowVal)) + lowVal;

	//assign moveSpeed
	//every 2 turns it will get a free move (.5 + .5 = 1)
	speed = 1.5;
    moveSpeed = speed;
    currentMoveSpeed = 0;

	//run the getNameAndChar() function to get the name and displayChar
	getNameAndChar();
}

meleeCreature::~meleeCreature()
{

}


void meleeCreature::BossRoll(int& damageDealt)
{
    //make a roll from 0 - 10
	int roll = rand() % 11;

	//if the roll is good, adjust damage and add to the attackMessage
	if (roll == 10)
    {
		//enemyAttackTurn is: enemyAttackTurn + " and it breathed fire!"
		enemyAttackTurn += " and it breathed fire!";

		//150% damage is dealt
		damageDealt += damageDealt/2;
    }
	else //else enemyAttackTurn is: enemyAttackTurn + "."
    {
        enemyAttackTurn += ".";
    }
}

int meleeCreature::attackPlayer()
{

}