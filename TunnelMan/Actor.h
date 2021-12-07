#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

const std::string stable = "stable";
const std::string waiting = "waiting";
const std::string falling = "falling";

/// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    ~Actor();
    StudentWorld* getWorld();
    virtual void doSomething() = 0;
    bool isAlive();
    void setDead();

private:
    StudentWorld* m_world;
    
    bool m_isAlive;
};

class Earth : public Actor {
public:
    Earth(StudentWorld* sw, int startX, int startY);
    ~Earth();
    void doSomething();
};


class Tunnelman : public Actor {
public:
    Tunnelman(StudentWorld* sw);
    void doSomething();
    ~Tunnelman();
    
    // Accessors - not sure if we need this actually
    int hp() const;
    int numWater() const;
    int numSonar() const;
    int numGold() const;
    
private:
    int m_hp;
    int m_waterUnits;
    int m_numSonar;
    int m_numGold;
    

};

class Boulder : public Actor {
public:
    Boulder(StudentWorld* sw, int startX, int startY);
    ~Boulder();
    void doSomething();
    std::string getState() {
        return m_state;
    }
    void setState(std::string state);
private:
    std::string m_state;
    int waitingNum;
    
};

// Base class for pick-uppable items: Sonar kits, Water, Gold nuggets
class Goodies : public Actor {
public:
    Goodies(StudentWorld*sw, int startX, int startY);
    ~Goodies();
private:
    
};

class Protestor : public Actor {
public:
    Protestor(StudentWorld* sw, int startX, int startY);
    ~Protestor();
    
};


#endif // ACTOR_H_
