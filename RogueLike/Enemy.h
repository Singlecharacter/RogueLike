#ifndef ENEMY_H
#define ENEMY_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cctype>#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "Chest.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void isSeenByPlayer(); //tells enemy if it should attack/chase
	void hurtEnemy(int playerDamageDealt); //deal damage to the enemy, enemy dies if hp = 0,
	void getNameAndChar(); //get the name and display char from a file

	//these two functions return two different strings for display log
	string getEnemyHealthStatus();
	string getEnemyAttackTurn();

	//some get functions for control
	char getDisplayChar();
	string getName();
	string getEnemeyType();
	bool getDeadOrNot();
	bool getGoodLoot();
	Chest getEnemyCorpse();

    //variables in public for easy reference and use
	int x,y; //x & y coordinates
    double moveSpeed, currentMoveSpeed; //currentMoveSpeed keeps track of when extra tile move will hit

protected:
	int maxhp, currenthp, power, defense, accuracy, rarity, level, mapLevel;
	char displayChar;
	bool seePlayer, hesDeadJim, dropItemQuery;
	string name, enemyType, enemyHealthStatus, enemyAttackTurn;

	//function to help read a file
	void findNextLine(ifstream& file, string& currentLine);
};

#endif
