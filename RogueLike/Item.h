#ifndef ITEM_H
#define ITEM_H

//Placeholder item class

#include <string>

#include <iostream>
#include <string>

#define VITALITY 0
#define MANA 1
#define STRENGTH 2
#define DEXTERITY 3
#define INTELLECT 4
#define PURITY 5
#define ARMOR 6
#define WARD 7
#define SPEED 8

using namespace std;

class Item
{
public:

    Item();
    ~Item();
    void createItem(int playerLevel, int rarityTable); //create an item add everything to it's spot
    string getName();
    int getSlot();
    void findNextLine (ifstream& file, string& currentLine); //will skip comments and whitespace in files

private:

    std::string name;

    /********************************
    * Vitality = maxHP boost	    *
    * Mana = maxMP boost			*
    * Strength = STR boost			*
    * Dexterity = DEX boost			*
    * Intellect = INT boost			*
    * Purity = poisonLevel boost	*
    * Armor = AC boost				*
    * Ward = MR boost				*
    * Speed = movementSpeed			*
    ********************************/
    int Vitality, Mana, Strength, Dexterity, Intellect, Purity, Armor, Ward, Speed, Damage, Accuracy;

    /*****************
    * 1 = mainHand	 *
    * 2 = offHand	 *
    * 3 = bodySlot   *
    * 4 = headSlot	 *
    * 5 = feetSlot	 *
    * 6 = handSlot	 *
    * 7 = backSlot	 *
    * 8 = neckSlot	 *
    * 9 = rightRing	 *
    * 10 = leftRing  *
    *****************/
    int slot;

    /********************
    * c = Common Item	*
    * r = Rare Item 	*
    * e = Epic Item   	*
    * l = Legendary Item*
    ********************/
    char rarity;

    int level;//this will be how we tell how much to add to stats

};

#endif // ITEM_H
