#include "Enemy.h"

Enemy::Enemy()
{
	//initialize universal variables
		maxhp = 5;//maxhp equals 5
		currenthp = maxhp;//currenthp equals max hp
		power = 0;//power equals 0
		defense = 0;//defence equals 0
		hesDeadJim = false;//is the enemy dead?
		dropItemQuery = false; //drop the item?
		rarity = (rand() % 4) + 1;//int of random number from 1 to the max amount of enemy rarity types (4 at the moment)
}

Enemy::~Enemy()
{
}

bool Enemy::isSeenByPlayer(Player player)
{
	if(player.x - x >= -5 && player.x - x <= 5 && player.y - y >= -5 && player.y - y <= 5)
    {
        if(player.sightArray[5-(player.y-y)][5-(player.x-x)] == 1)
        {
            return true;
        }
    }
    return false;
}

void Enemy::hurtEnemy(int playerDamageDealt) //deal damage to the enemy, enemy dies if hp = 0
{
	currenthp -= playerDamageDealt;
	if(currenthp <= 0)
    {
        hesDeadJim = true;
    }
}

void Enemy::getNameAndChar()
{
	//declare variables to help in reading the file
    string currentLine; //string currentLine to hold the line currently being read
    int tempRar = 0; //int tempRar to hold a string converted to int variable, which is initialized to 0
    vector<string> data; //a string vector to hold name and displayChar in string form

	ifstream enemyFile ("enemyData.txt"); //open enemyData file

	//use getNextLine function to skip all initial comments and get the first line of input
	findNextLine(enemyFile, currentLine);

	//tempRar equals the firsfor(int i = 0;i<meleeCreatures.size();i++)
	tempRar = atoi(currentLine.substr(0,1).c_str());

	//while rarity is not equal to tempRar
	while (rarity != tempRar)
    {
        findNextLine(enemyFile, currentLine);//get the next line of valid input

		//tempRar equals the first part of the currentLine string converted to an int
		tempRar = atoi(currentLine.substr(0,1).c_str());
    }

	//once we have rarity, we can find the enemyType easily

	//while the second and third part is not equal to enemyType
	while (enemyType != currentLine.substr(1,2))
    {
		findNextLine(enemyFile, currentLine);//get the next line of valid input
    }

	//now we are on the line, identifying what we need to make our enemy

	//get the next line and push it into a 2 slot vector separating parts by a ','
	findNextLine(enemyFile, currentLine);

    istringstream enemyInputs(currentLine);
    string temp;

    //now the things from the comma and stick them in the vector for choice
    while (getline(enemyInputs, temp, ','))
    {
        data.push_back(temp);
    }

	//name equals the first part of the vector
	name = data[0];

	//convert second part into a char, and stick it into displayChar
	displayChar = (data[0])[0];

    //now close the file
	enemyFile.close();
}

string Enemy::getEnemyHealthStatus()
{
	//return the message currently contained in enemyHealthStatus if it is not empty
	return enemyHealthStatus;
}

string Enemy::getEnemyAttackTurn()
{
	//return the message currently contained in enemyAttackTurn if it is not empty
	return enemyAttackTurn;
}

void Enemy::findNextLine(ifstream& file, string& currentLine)
{
    getline (file, currentLine);

    while (currentLine.substr(0,1) == "*" || currentLine.substr(0,1) == "/" || currentLine.substr(0,1) == "")
    {
        getline (file,currentLine);
    }
}

char Enemy::getDisplayChar()
{
    return displayChar;
}

std::string Enemy::getName()
{
    return name;
}

std::string Enemy::getEnemyType()
{
    return enemyType;
}

bool Enemy::isDead()
{
    return hesDeadJim;
}

bool Enemy::getGoodLoot()
{
    return dropItemQuery;
}

Chest Enemy::getEnemyCorpse()
{
    Chest corpse(x, y, rarity, level, name + " corpse");
    corpse.generateItem();
    return corpse;
}

int Enemy::getPower()
{
    return power;
}
