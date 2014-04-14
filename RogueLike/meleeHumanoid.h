#ifndef MELEEHUMANOID_H
#define MELEEHUMANOID_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Enemy.h"

class meleeHumanoid: public Enemy
{
public:
	meleeHumanoid(int playerLevel, int xCoord, int yCoord, int currentMapLevel); //faster, less damage
	~meleeHumanoid();

	//special rolls for the "boss" level enemies
	void BossRoll(int damageDealt); //Minotaur "enrages" (some stats go up)

	//attack the player when player is on next tile and return the base damage
	int attackPlayer();
};

#endif

