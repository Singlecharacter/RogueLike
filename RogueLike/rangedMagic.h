#ifndef RANGEDMAGIC_H
#define RANGEDMAGIC_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Enemy.h"

class rangedMagic: public Enemy
{
public:
	rangedMagic(int playerLevel, int xCoord, int yCoord, int currentMapLevel); //faster, less damage
	~rangedMagic();

	//special rolls for the "boss" level enemies
	void BossRoll(int damageDealt); //Minotaur "enrages" (some stats go up)

	//attack the player when player is on next tile and return the base damage
	int attackPlayer();
};

#endif


