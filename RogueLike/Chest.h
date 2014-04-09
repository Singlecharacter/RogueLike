#ifndef CHEST_H
#define CHEST_H

#include <string>

using namespace std;

class Chest
{
public:
    Chest(int xCoord, int yCoord, int rarity, int playerLevel, string name);
    ~Chest();
    void generateItem();
    Item getItem();

    //coordinates
    int x, y;

private:
    string chestName;
    int rarity, level;
    Item contents;

};

#endif //chest.h
