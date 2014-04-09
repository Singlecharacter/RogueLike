#ifndef WALL_H
#define WALL_H

//It's a wall. It does wall things, which include, and are limited to:
// 1. Nothing

class Wall
{
public:

    Wall(int y, int x);
    ~Wall();

    int x,y;
};

#endif // WALL_H
