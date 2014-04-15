#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Chest.h"

using namespace std;

Chest::Chest(int xCoord = 0, int yCoord = 0, int rarity = 1, int level = 0, string name = "")
{
    //assign the parameters
    x = xCoord;
    y = yCoord;
    chestName = name;
    this -> rarity = rarity;
    this -> level = level;
}

Chest::~Chest()
{
}

void Chest::generateItem()
{
    //make a temp Item to create the random item
    Item tempItem;

    //create the item
    tempItem.createItem(level, rarity);

    //now make that item what we currently have
    contents = tempItem;
}

Item Chest::getItem()
{
    return contents;
}
