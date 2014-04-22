#include "utility.h"
/*
place_meeting takes a vector of game objects and checks if any of those objects are at a given point.
If one is, it returns true. Otherwise, it returns false.
*/

#include <vector>
#include <string>

template<typename T>
int place_meeting(int checkY, int checkX, std::vector<T> objs)
{
    for(int i = 0;i<objs.size();i++)
    {
        if(objs.at(i).x == checkX && objs.at(i).y == checkY)
        {
            return i;
        }
    }
    return -1;
}
