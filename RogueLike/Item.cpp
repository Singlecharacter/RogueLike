#include <string>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <sstream>
#include "Item.h"

using namespace std;

Item::Item()
{
    //initialize everything for easy addition
    name = "";
    Vitality = 0;
    Mana = 0;
    Strength = 0;
    Dexterity = 0;
    Intellect = 0;
    Purity = 0;
    Armor = 0;
    Ward = 0;

    rarity = ','; //this is initialize to , for item creation

    ranged = false; //is the weapon ranged or melee? t = ranged, f = melee
    twoH = false; //is it 1 or two handed weapon? t = 2h, f = 1h
    itemOrPotion = false; //is it armor and weapons or potions? t = equipable, f = potion

    level = 0;//this will be how we tell how much to add to stats

    AC = 0; //armor for items
    armorType = 0; //1 - cloth, 2 - leather, 3 - plate, 4 - jewelry

    Damage = 0; //damage for weapons
    Accuracy = 50; //how accurate the weapons

    potionType = 0; //0 = mana, 1 = hp
    effectiveness = 0; //how effective are the potions?
}

Item::~Item()
{

}

//parameters are the player's level for stat adjustment,
//and rarity table from chests or enemies to generate another stat adjustment variable
//I'm assuming that the player, enemies, and chests will have a get function to grab these
void Item::createItem(int playerLevel, int rarityTable, int forcedSlot)
{
    rarity = rarityTable; //get the rarity
    level = playerLevel;
    int whatToMake;
    bool force;

    if (forcedSlot != 200) //user defined
    {
        slot = forcedSlot; //slot is forced

        if (forcedSlot == 0 || forcedSlot == 1) //make a weapon
        {
            whatToMake = 0;
        }
        else //make armor
        {
            whatToMake = 1;
        }
        force = true; //it is a forced assignment
    }
    else //it is random selection
    {
        whatToMake = rand() % 3;

        force = false;
    }

    switch(whatToMake)
    {
    case 0:
        makeArmor(force);
        break;
    case 1:
        makeWeapon(force);
        break;
    case 2:
        makePotion();
        break;
    default:
        cout << "wtf..." << endl;
    }
}

string Item::getName()
{
    return name;
}

int Item::getSlot()
{
    return slot;
}

void Item::makeArmor(bool force)
{
    int choice = rarity, ArmorIndex, itemSlotChoice, itemNumber = 0; //this will hold the number for the type of item
    string Input, itemType;
    ifstream myfile ("dropArmor.txt");
    vector <string> listOfItems;
    vector <string> listOfStats;

    srand(time(NULL)); //seed the random

    if (force == true) //force it
    {
        itemSlotChoice = slot;
    }
    else //random
    {
    itemSlotChoice = (rand() % 8) + 2; //item slots 2 - 9
    }

    findNextLine (myfile, Input);

    //find the rarity of the table to use
    while (atoi(Input.substr(0,1).c_str()) != choice)
    {
        findNextLine (myfile, Input);
    }

    //now choose the rarity from that subTable
    //if it is a ',' it will choose again
    while (rarity == ',')
    {
        //will choose from 1 - last element of the subTable
        choice = rand() % (Input.length() - 1) + 1;
        rarity = Input[choice];
    }

    //add the rarity to the string name for the item
    switch(rarity)
    {
    case 'c':
        name = name + "Common ";
        break;
    case 'r':
        name = name + "Rare ";
        break;
    case 'e':
        name = name + "Epic ";
        break;
    case 'l':
        name = name + "Legendary ";
        break;
    default:
        name = name + "Common "; //if there is an error, just make it common
    }

    //now that we have the rarity, get the type of item
    findNextLine (myfile, Input); //go down once more to get off of 1 if that was the rarity table

    //now keep going intil it is in the section for item types
    while (atoi(Input.substr(0,1).c_str()) != 2)
    {
        findNextLine (myfile, Input);
    }

    //now that we are at the correct file position, get the item slot
    choice = itemSlotChoice; //will the cooresponding item slot from a random int

    //now assign the slot variable for the item
    slot = choice;

    //find the item slot to use
    while (itemNumber != choice)
    {
        stringstream StrToNum(Input);
        StrToNum >> itemNumber;
        findNextLine (myfile, Input);
    }

    //now choose the item name from that subTable
    //first, put all of the subTable onto a vector to choose from
    istringstream itemStream(Input);
    string temp;

    //now the things from the comma and stick them in the vector for choice
    while (getline(itemStream, temp, ','))
    {
        listOfItems.push_back(temp);
    }
    //now pick a random item base from the vector of items
    choice = rand() %  listOfItems.size(); //will choose from 0 - last element

    name = name + listOfItems[choice]; //now add the type of item

    ArmorIndex = choice; //use to determine armor type

    //if the rarity is common it will exclude
    if (rarity != 'c')
    {
        //now get the file to the correct place for the stat addage
        while (Input.substr(0,1) != "V")
        {
            findNextLine (myfile, Input);
        }

        //now put all possible stats into a vector
        istringstream statStream(Input);
        while (getline(statStream, temp, ','))
        {
            listOfStats.push_back(temp);
        }

        //now add the stat to the item and put it into the itemType string for stat addage
        //pick a random item stat from the vector of stats
        choice = rand() %  listOfStats.size(); //will choose from 0 - last element

        //now put it into the item string
        itemType = listOfStats[choice];
        name = name + " of " + itemType;
    }
    else //if it's common, set itemType to Nothing, to exclude big bonuses
    {
        itemType = "Nothing";
    }

    //now for some item setting
    if (slot == 2 || slot == 3 || slot == 4 || slot == 5 && ArmorIndex == 0) //it is cloth
    {
        armorType = 1;
    }
    else if (slot == 2 || slot == 3 || slot == 4 || slot == 5 && ArmorIndex == 1) //it is leather
    {
        armorType = 2;
    }
    else if (slot == 2 || slot == 3 || slot == 4 || slot == 5 && ArmorIndex == 2) //it is plate
    {
        armorType = 3;
    }
    else //it is jewelry
    {
        armorType = 4;
    }

    itemOrPotion = true; //it is an item
}

void Item::makeWeapon(bool force)
{
    int choice = rarity, itemSlotChoice, itemNumber = 0; //this will hold the number for the type of item
    string Input, itemType;
    ifstream myfile ("dropWeapon.txt");
    vector <string> listOfItems;
    vector <string> listOfStats;

    srand(time(NULL)); //seed the random

    if (force == true)
    {
        itemSlotChoice = slot;
    }
    else
    {
        itemSlotChoice = rand() % 4; //item slots 0 - 3
    }

    findNextLine (myfile, Input);

    //find the rarity of the table to use
    while (atoi(Input.substr(0,1).c_str()) != choice)
    {
        findNextLine (myfile, Input);
    }

    //now choose the rarity from that subTable
    //if it is a ',' it will choose again
    while (rarity == ',')
    {
        //will choose from 1 - last element of the subTable
        choice = rand() % (Input.length() - 1) + 1;
        rarity = Input[choice];
    }

    //add the rarity to the string name for the item
    switch(rarity)
    {
    case 'c':
        name = name + "Common ";
        break;
    case 'r':
        name = name + "Rare ";
        break;
    case 'e':
        name = name + "Epic ";
        break;
    case 'l':
        name = name + "Legendary ";
        break;
    default:
        name = name + "Common "; //if there is an error, just make it common
    }

    //now that we have the rarity, get the type of item
    findNextLine (myfile, Input); //go down once more to get off of 1 if that was the rarity table

    //now keep going intil it is in the section for item types
    while (atoi(Input.substr(0,1).c_str()) != 0)
    {
        findNextLine (myfile, Input);
    }

    //now that we are at the correct file position, get the item slot
    choice = itemSlotChoice; //will the cooresponding item slot from a random int

    //now assign the slot variable for the item
    slot = choice;

    //find the item slot to use
    while (itemNumber != choice)
    {
        stringstream StrToNum(Input);
        StrToNum >> itemNumber;
        findNextLine (myfile, Input);
    }

    //now choose the item name from that subTable
    //first, put all of the subTable onto a vector to choose from
    istringstream itemStream(Input);
    string temp;

    //now the things from the comma and stick them in the vector for choice
    while (getline(itemStream, temp, ','))
    {
        listOfItems.push_back(temp);
    }
    //now pick a random item base from the vector of items
    choice = rand() %  listOfItems.size(); //will choose from 0 - last element

    name = name + listOfItems[choice]; //now add the type of item

    //if the rarity is common it will exclude
    if (rarity != 'c')
    {
        //now get the file to the correct place for the stat addage
        while (Input.substr(0,1) != "V")
        {
            findNextLine (myfile, Input);
        }

        //now put all possible stats into a vector
        istringstream statStream(Input);
        while (getline(statStream, temp, ','))
        {
            listOfStats.push_back(temp);
        }

        //now add the stat to the item and put it into the itemType string for stat addage
        //pick a random item stat from the vector of stats
        choice = rand() %  listOfStats.size(); //will choose from 0 - last element

        //now put it into the item string
        itemType = listOfStats[choice];
        name = name + " of " + itemType;
    }
    else //if it's common, set itemType to Nothing, to exclude big bonuses
    {
        itemType = "Nothing";
    }

    //now for some item setting
    //choose melee or ranged boolean
    if (slot == 0 || slot == 1 || slot == 3)
    {
        ranged = false;
    }
    else
    {
        ranged = true;
    }

    //is it 1h or 2h
    if (slot == 2 || slot == 3)
    {
        twoH = true;
        slot = 0;
    }
    else
    {
        twoH = false;
    }

    itemOrPotion = true; //it is an item
}

void Item::makePotion()
{
    int choice = rand() % 2; //0 for mana, 1 for hp
    effectiveness = (rand() % 15) + 25; //restore 25 - 40% of the resource
    itemOrPotion = false; //it is a potion
}

bool Item::getRangedWep()
{
    return ranged;
}

bool Item::get2h()
{
    return twoH;
}

bool Item::getItemOrPotion()
{
    return itemOrPotion;
}

int Item::getAC()
{
    return AC;
}

int Item::getArmorType()
{
    return armorType;
}

int Item::getDamage()
{
    return Damage;
}

int Item::getAccuracy()
{
    return Accuracy;
}

int Item::getPotionType()
{
    return potionType;
}

int Item::getPotionEffect()
{
    return effectiveness;
}

void Item::findNextLine(ifstream& file, string& currentLine)
{
    getline (file, currentLine);

    while (currentLine.substr(0,1) == "*" || currentLine.substr(0,1) == "/" || currentLine.substr(0,1) == "")
    {
        getline (file,currentLine);
    }
}
