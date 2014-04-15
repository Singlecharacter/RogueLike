#ifndef MELEECREATURE_H
#define MELEECREATURE_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Enemy.h"

class meleeCreature: public Enemy
{
public:
	meleeCreature(int playerLevel, int xCoord, int yCoord, int currentMapLevel); //faster, less damage
	~meleeCreature();

	//special rolls for the "boss" level enemies
	void BossRoll(int damageDealt); //Dragon breathes fire on chance (150% damage)

	//attack the player when player is on next tile and return the base damage
	int attackPlayer();
};

#endif
