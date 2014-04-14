#include "Enemy.h"

Enemy::Enemy()
{
	//initialize universal variables
		maxhp = 5;//maxhp equals 5
		currenthp = maxhp;//currenthp equals max hp
		power = 0;//power equals 0
		defense = 0;//defence equals 0
		moveSpeed = 0;//moveSpeed equals 0
		currentMoveSpeed = 0;//currentMoveSpeed equals 0
		seePlayer = false;//seePlayer equals false
		hesDeadJim = false;//is the enemy dead?
		rarity = (rand() % 4) + 1;//int of random number from 1 to the max amount of enemy rarity types (4 at the moment)
}

Enemy::~Enemy()
{
}

void Enemy::isSeenByPlayer()
{
	//by default, if this function is ever called, set seePlayer boolean to true,
    //the bool will be set false every turn so this will set it to true if the enemy is seen
    seePlayer = true;
}

void Enemy::hurtEnemy(int playerDamageDealt) //deal damage to the enemy, enemy dies if hp = 0
{
	//declare variables
    int realDamage = playerDamageDealt;//int of what the real damage dealt will be equals playerDamageDealt
    bool dropItemQuery = false;//bool dropItem equals false

	//realDamage modified through equation using defence
	if (defense > 0)
    {
        //this was pulled from player's damage mitigation
        realDamage = realDamage - (rand() % (defense + 1)) - 1.5 * sqrt(defense);
    }

	//deal the damage
    currenthp -= realDamage;//currenthp equals (currenthp - realDamage)

	//if currenthp is less than or equal to 0, the enemy has died
	if (currenthp <= 0)
    {
        hesDeadJim = true;//set dead bool

		//create rand roll of 0 through 100 to decide if enemy drops loot
		int dropChance = rand() % 101;

		//if enemy is boss, there is 80% drop chance, if it is hit, set dropItem to true
		if (rarity == 4 && dropChance <= 80)
		{
		    dropItemQuery = true;
		}
		else if (rarity == 3 && dropChance <= 55)//else if enemy is epic, 55% drop chance
        {
            dropItemQuery = true;
        }
		else if (rarity == 2 && dropChance <= 35)//else if enemy is rare, 35% drop chance
        {
            dropItemQuery = true;
        }
		else if (rarity == 1 && dropChance <= 25)//else enemy is common, 25% drop chance
        {
            dropItemQuery = true;
        }
        else
        {
            cout << "ERROR IN ENEMY DROP CHANCE" << endl;
        }

		//if the dropItem bool is true, run the onDeathCreateLoot() function which makes a "chest"
        if (dropItemQuery)
        {
            enemyLoot = onDeathCreateLoot();
        }
		else //else, set the current x & y to '.' & set message
        {
            displayChar = '.';
            enemyHealthStatus = name + " is now dead as a doornail.";
        }
    }

	else //else make the enemyHealthStatus what it is appropriate to the current health percentage
	{
	    int hpPerc = ((currenthp/maxhp) * 100);

		if (hpPerc > 90)//if percentage is > 90%
        {
			enemyHealthStatus = name + " is healthy.";
        }
		else if (hpPerc > 50 && hpPerc <= 90)//else if percentage is > 50% and <= 90%
        {
			enemyHealthStatus = name + " is slightly wounded.";
        }
		else if (hpPerc > 30 && hpPerc <= 50)//else if percentage is > 30% and <= 50%
        {
			enemyHealthStatus = name + " is greatly wounded.";
        }
		else if (hpPerc > 1 && hpPerc <= 30)//else if percentage is > 1% and <= 30%
        {
			enemyHealthStatus = name + " is seriously wounded.";
        }
		else //else the percentage is 1%
        {
            string newName = "";

            for (int i = 0; i < name.length(); i++)
            {
                newName += toupper(name[i]);
            }

			enemyHealthStatus = "FINISH " + newName + "!";
        }
	}
}

Chest Enemy::onDeathCreateLoot()
{
	//create the chest obj for enemy drop
	string chestName = name + " corpse.";
	Chest enemyDrop(x, y, rarity, level, chestName);

	//now generate an item for that chest
	enemyDrop.generateItem();

	return enemyDrop;
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

	//tempRar equals the first part of the currentLine string converted to an int
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
