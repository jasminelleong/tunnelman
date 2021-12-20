#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

const std::string stable = "stable";
const std::string waiting = "waiting";
const std::string falling = "falling";
const std::string temp = "temp";

/// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
//template <typename Object>
//Object isCoordinate(int otherX, int otherY) {
//
//}
class Actor : public GraphObject {
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    //Actor(StudentWorld* sw, int imageID, int startX, int startY, double size, unsigned int depth);
    ~Actor();
    StudentWorld* getWorld();
    virtual void doSomething() = 0;
    bool isAlive();
    void setDead();
    bool isCoordinate(int otherX, int otherY);
    virtual std::string classType() = 0;

private:
    StudentWorld* m_world;
    bool m_isAlive;
};

class Earth : public Actor {
public:
    Earth(StudentWorld* sw, int startX, int startY);
    ~Earth();
    void doSomething();
    std::string classType();
};


class Tunnelman : public Actor {
public:
    Tunnelman(StudentWorld* sw);
    void doSomething();
    ~Tunnelman();
    std::string classType();
    void increaseSonarCount();
    int hp() const;
    int numWater() const;
    int numSonar() const;
    int numGold() const;
    void increaseSquirts(unsigned int howMuch);
    void decreaseSquirts();
    void increaseGold();
    void decreaseGold();
    void decrementHealth(int howMuch);

private:
    int m_hp;
    int m_waterUnits;
    int m_numSonar;
    int m_numGold;
    int x;
    int y;
    bool m_isAlive = true;


};

class Boulder : public Actor {
public:
    Boulder(StudentWorld* sw, int startX, int startY, Tunnelman* p);
    ~Boulder();
    virtual void doSomething();
    std::string getState() {
        return m_state;
    }
    void setState(std::string state);
    std::string classType();

private:
    std::string m_state;
    int waitingNum;
    int x;
    int y;
    Tunnelman* playerInGame;

};

class Squirt : public Actor {
public:
    Squirt(StudentWorld* sw, int startX, int startY, Tunnelman* p, Direction d);
    ~Squirt();
    void doSomething();
    std::string getState() {
        return m_state;
    }
    void setState(std::string state);
    std::string classType();

private:
    std::string m_state;
    int waitingNum;
    int x;
    int y;
    Tunnelman* playerInGame;
    Direction dir;

};

class Protester : public Actor {
public:
    Protester(StudentWorld* sw, int startX, int startY, Tunnelman* p, int imageID);
    ~Protester();
    void doSomething();
    std::string classType();
    void move();
    bool getShot();
    //    bool isCoordinate(int otherX, int otherY, std::string& type);
    bool isNearTunnelman();
    bool isFacingTunnelman();
    void setNewDirection();
    bool takePerpendicularTurn();
    void decrementHealth(int howMuch);
    bool stunProtest();
    void setHp(int hp);
private:
    bool stun;
    int restP;
    int yellWaitingNum;
    int annoy;
    int perpendicularRestingNum = 200;
    int waitingNum;
    int numSquaresToMoveInCurrentDirection;
    int m_hp;
    bool isLeaveFieldState;
    Tunnelman* playerInGame;

};

class HardcoreProtester : public Protester {
public:
    HardcoreProtester(StudentWorld* sw, int startX, int startY, Tunnelman* p);
    ~HardcoreProtester();
private:

};




// Base class for pick-uppable items: Sonar kits, Water, Gold nuggets
class Goodies : public Actor {
public:
    Goodies(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, Tunnelman* p);
    ~Goodies();
    bool isNearTunnelman();
private:
    Tunnelman* playerInGame;
};

class Nuggets : public Goodies {
public:
    Nuggets(StudentWorld* sw, int startX, int startY, Tunnelman* p, std::string state);
    ~Nuggets();
    void doSomething();

    std::string classType();
    

private:
    std::string m_state;
    int m_x;
    int m_y;
    bool found;
    int count;
    int waitingNum;
    Tunnelman* playerInGame;
};

class Barrel : public Goodies {
public:
    Barrel(StudentWorld* sw, int startX, int startY, Tunnelman* p);
    ~Barrel();
    void doSomething();
    
    std::string classType();

private:
   
    int m_x;
    int m_y;
    bool found;
    int count;
    Tunnelman* playerInGame;
};

class WaterPool : public Goodies {
public:
    WaterPool(StudentWorld* sw, int startX, int startY, Tunnelman* p);
    ~WaterPool();
    void doSomething();
    std::string classType();
    std::string getID();
private:
    std::string m_state;
    int m_x;
    int m_y;
    //bool found;
    int waitingNum;
    Tunnelman* playerInGame;
};

class SonarKit : public Goodies {
public:
    SonarKit(StudentWorld* sw, int startX, int startY, Tunnelman* p);
    ~SonarKit();
    //    void setState(std::string state);
    void doSomething();
    std::string classType();
    std::string getID();
    bool isWithinRadius(int);
private:
    std::string m_state;
    int m_x;
    int m_y;
    int waitingNum;
    Tunnelman* playerInGame;
};




#endif // ACTOR_H_
