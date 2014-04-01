#ifndef ITEM_H
#define ITEM_H

//Placeholder item class

#include <string>

class Item
{
public:

    Item(std::string name = "");
    ~Item();

private:

    std::string name;
};

#endif // ITEM_H
