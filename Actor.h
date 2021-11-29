#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

/// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    StudentWorld* getWorld();

private:
    StudentWorld* m_world;
};

class Earth : public Actor {
public:
    Earth(StudentWorld* sw, int startX, int startY);
};


class Tunnelman : public Actor {
public:
    Tunnelman(StudentWorld* sw);
    void doSomething();
private:
    bool isAlive;


};
#endif // ACTOR_H_
