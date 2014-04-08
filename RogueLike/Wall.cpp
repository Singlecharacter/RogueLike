#include "Wall.h"

Wall::Wall(int y = 0, int x = 0)
{
    this -> y = y;
    this -> x = x;
}

Wall::~Wall()
{

}


int Wall::getX()
{
    return x;
}

int Wall::getY()
{
    return y;
}

void Wall::setX(int newX)
{
    x = newX;
}

void Wall::setY(int newY)
{
    y = newY;
}
