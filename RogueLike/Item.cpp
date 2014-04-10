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
    Speed = 0;

    rarity = ','; //this is initialize to , for item creation
}

Item::~Item()
{

}

//parameters are the player's level for stat adjustment,
//and rarity table from chests or enemies to generate another stat adjustment variable
//I'm assuming that the player, enemies, and chests will have a get function to grab these
void Item::createItem(int playerLevel, int rarityTable)
{
    int choice, itemNumber = 0; //this will hold the number for the type of item
    string Input, itemType;
    ifstream myfile ("enemyDropTable.txt");
    vector <string> listOfItems;
    vector <string> listOfStats;

    srand(time(NULL)); //seed the random

    int itemSlotChoice = rand() % 10 + 1; //adjust 10 for however many item slots

    //choose the rarity table
    //can represent enemy difficulty or chests on the map rarity
    choice = rarityTable;
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

    //now that we've built the name of the item and chosen the key features, we can now
    //apply it's stats

    /************************************************************************************
    * Stat Assignment Notes:                                                                       *
    *                                                                                   *
    * 'itemType' will hold the string of it's dominant stat, unless it's common         *
    * 'rarity' will hold it's modifier, if it's common, it is just base stats           *
    * 'level' will be determined with a rand +/- player's level, which is a parameter   *
    *                                                                                   *
    * Weapons:                                                                          *
    *   'Damage' will be the base damage for that item without multipliers              *
    *   'Accuracy' will be a value to roll to see if the weapon will hit                *
    * Armor:                                                                            *
    *   'Armor' will be the AC, which helps with defense in damage mitigation           *
    *                                                                                   *
    * if the 'slot' is == 1 - 2, it is a weapon or offhand                              *
    * if the 'slot' is == 3 - 7, it is a piece of armor                                 *
    * if the 'slot' is == 8 - 10, it is a piece of jewelry                              *
    *                                                                                   *
    * The current 2h weapons added in the file are:                                     *
    * Bow, Spear, Greatsword, Staff                                                     *
    *                                                                                   *
    * Also, for anything I edited on the player I left a note that I edited or added    *
    * I renamed those playerItems, so it doesn't conflict and you can just see changes  *
    ************************************************************************************/

}

string Item::getName()
{
    return name;
}

int Item::getSlot()
{
    return slot;
}

void Item::findNextLine(ifstream& file, string& currentLine)
{
    getline (file, currentLine);

    while (currentLine.substr(0,1) == "*" || currentLine.substr(0,1) == "/" || currentLine.substr(0,1) == "")
    {
        getline (file,currentLine);
    }
}
