#ifndef ITEM_H
#define ITEM_H

//Placeholder item class

<<<<<<< HEAD
#include <string>

=======
#include <iostream>
#include <string>

using namespace std;

>>>>>>> origin/items
class Item
{
public:

<<<<<<< HEAD
    Item(std::string name = "");
    ~Item();
=======
    Item();
    ~Item();
    void createItem(int playerLevel, int rarityTable); //create an item add everything to it's spot
    int getSlot();
    void findNextLine (ifstream& file, string& currentLine); //will skip comments and whitespace in files
>>>>>>> origin/items

private:

    std::string name;
<<<<<<< HEAD
=======

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

>>>>>>> origin/items
};

#endif // ITEM_H
