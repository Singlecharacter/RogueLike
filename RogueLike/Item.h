#ifndef ITEM_H
#define ITEM_H

//Placeholder item class

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
#include <fstream>

class Item
{
public:

    Item();
    ~Item();
    void createItem(int playerLevel = 0, int rarityTable = 0, int forcedSlot = 200); //create an item add everything to it's spot

    int getSlot();
    std::string getName();

    //potions
    void makePotion(); //create the item as a potion
    int useHealthPotion(); //use potion and return amount restored
    int useMagicPotion(); //use potion and return amount restored

    //weapons
    void makeWeapon(bool force); //create a weapon item

    //armor
    void makeArmor(bool force); //create an armor item

    //get functions
    bool getRangedWep();
    bool get2h();
    bool getItemOrPotion();
    int getAC();
    int getArmorType();
    int getDamage();
    int getAccuracy();
    int getPotionType();
    int getPotionEffect();


protected:
    void findNextLine (std::ifstream& file, std::string& currentLine); //will skip comments and whitespace in files

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

    bool ranged; //is the weapon ranged or melee? t = ranged, f = melee
    bool twoH; //is it 1 or two handed weapon? t = 2h, f = 1h
    bool itemOrPotion; //is it armor and weapons or potions? t = equipable, f = potion
    bool force;//make the item gen choose the correct thing

    int level;//this will be how we tell how much to add to stats

    int AC; //armor for items
    int armorType; //1 - cloth, 2 - leather, 3 - plate, 4 - jewelry

    int potionType; //0 = mana, 1 = hp
    int effectiveness; //how effective are the potions?

};

#endif // ITEM_H
