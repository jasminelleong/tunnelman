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
    //    bool isProtesterThere(int x, int y);
    bool isBoulderOrEarth(int x, int y);
    virtual int init();
    bool isBoulderthere(int xPos, int yPos);
    //    void setLocation(int xPos, int yPos);
    void setDisplayText();
    void decrementBarrelCount();
    void populateEarth();
    void populateBoulders();
    void populateBarrels();
    void populatePoolsOrSonar();
    //    void populateSonar();
    void populateNuggets();
    void dropGold();
    bool protesterLocator(int x, int y);
    bool hasSomething(int xPos, int yPos, std::string& type);
    bool whatsAtThisLocation(int x, int y);
    virtual int move();
    void annoyance();
    bool stunned();
    void SetStun();
    void resetStun();
    int annoyCount();
    void resetAnnoy();
    bool isInRadius(int radius, int x1, int y1, int x2, int y2);
    void illuminate(int x, int y);

    virtual void cleanUp();

private:
    Tunnelman* player;
    Earth* earthPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    std::vector<Actor*> actorPtrs;
    bool BoulderPtrs[VIEW_WIDTH][VIEW_HEIGHT];
    int barrelCount = 0;
    int tick = 0;
    int timeSinceLastProtester = 0;
    int numProtesters = 0;
    bool m_restart = false;
    bool  m_shoot = false;
    int annoy = 5;
    bool stun = false;
};

#endif // STUDENTWORLD_H_
