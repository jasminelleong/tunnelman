#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
class GraphObject;
class Earth;
class Tunnelman;
class Actor;
class Boulder;
/// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();

    void shoot(int x, int y);
    void returnDeadplayer();
    void digField(int x, int y);
    bool isthereEarth(int x, int y);
    virtual int init();
    bool isBoulderthere(int xPos, int yPos);
    void setLocation(int xPos, int yPos);
    void setDisplayText();
    void decrementBarrelCount();
    void populateEarth();
    void populateBoulders();
    void populateBarrels();
    void populatePoolsOrSonar();
//    void populateSonar();
    void populateNuggets();
    void dropGold();
    bool protestorLocator(int x, int y);
    bool hasSomething(int xPos, int yPos, std::string& type);
    bool whatsAtThisLocation(int x, int y);
    virtual int move();

    virtual void cleanUp();

private:
    Tunnelman* player;
    Earth* earthPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    std::vector<Actor*> actorPtrs;
    bool BoulderPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    int barrelCount = 0;
    int tick = 0;
   bool m_restart = false;
   bool  m_shoot = false;
};

#endif // STUDENTWORLD_H_
