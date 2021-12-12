#include "Actor.h"
#include <string>
#include <iostream>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

const string earth = "earth";
const string tunnelman = "tunnelman";
const string boulder = "boulder";
const string barrel = "barrel";
const string protester = "protester";
const string squirt = "squirt";
const string sonarkit = "sonarkit";
const string waterpool = "waterpool";


///SONAR KIT CLASS///
SonarKit::SonarKit(StudentWorld* sw, int startX, int startY, Tunnelman* p) : Goodies(sw, TID_SONAR, startX, startY, right, 1, 2) {
    //    m_x = startX;
    //    m_y = startY;
    playerInGame = p;
    setVisible(true);
    m_state = stable; // stable aka waiting
    //found = false;
    waitingNum = std::max(100, 300 - 10 * (static_cast<int>(getWorld()->getLevel())));

}
void SonarKit::setState(std::string state) {
    m_state = state;
}
void SonarKit::doSomething() {
    int x = playerInGame->getX();
    int y = playerInGame->getY();
    if (!isAlive()) {
        return;
    }
    if (waitingNum == 0) {
        setVisible(false);
        setDead();
    }

    if (getX() - 3 <= x && x <= getX() + 3) {
        if (getY() - 3 <= y && y <= getY() + 3) {
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(75);
            playerInGame->increaseSonarCount();
            setDead();
        }
    }

    waitingNum--;

}
string SonarKit::classType() {
    return sonarkit;
}

SonarKit::~SonarKit() {
}











Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GraphObject(imageID, startX, startY, dir, size, depth) {
    m_world = sw;
    m_isAlive = true;
}

Actor::~Actor() {

}
bool Actor::isAlive() {
    return m_isAlive;
}
void Actor::setDead() {
    m_isAlive = false;
}


StudentWorld* Actor::getWorld() {
    return m_world;
}
//void Actor::setWorld(StudentWorld *world) {
//    m_world = world;
//}

Earth::Earth(StudentWorld* sw, int startX, int startY) : Actor(sw, TID_EARTH, startX, startY, right, .25, 3) {
    setVisible(true);
}
void Earth::doSomething() {
    return;
}
Earth::~Earth() {

}

string Earth::classType() {
    return earth;
}


Tunnelman::Tunnelman(StudentWorld* sw) : Actor(sw, TID_PLAYER, 30, 60, right, 1, 0) {
    setVisible(true);
    m_hp = 10;
    m_waterUnits = 5;
    m_numSonar = 1;
    m_numGold = 0;

}
Tunnelman::~Tunnelman() {

}

string Tunnelman::classType() {
    return tunnelman;
}

int Tunnelman::hp() const {
    return m_hp;
}
int Tunnelman::numWater() const {
    return m_waterUnits;
}
void Tunnelman::increaseSquirts(unsigned int howMuch)
{
    m_waterUnits += howMuch;
}
int Tunnelman::SquirtCount()
{
    return m_waterUnits;
}
void Tunnelman::decreaseSquirts()
{
    m_waterUnits--;
}

int Tunnelman::numSonar() const {
    return m_numSonar;
}

void Tunnelman::increaseSonarCount() {
    m_numSonar++;
}
int Tunnelman::numGold() const {
    return m_numGold;
}

Boulder::Boulder(StudentWorld* sw, int startX, int startY, Tunnelman* p) : Actor(sw, TID_BOULDER, startX, startY, down, 1, 1) {
    setVisible(true);
    m_state = stable;
    waitingNum = 30;
   playerInGame = p;

}

Boulder::~Boulder() {
}
string Boulder::classType() {
    return boulder;
}

bool Actor::isCoordinate(int otherX, int otherY, string& type) {
    int x = getX();
    int y = getY();
//    if (x <= otherX-3 && y <= otherY-3) {
//        return true;
////    }
//    if (otherX <= x + 3 && otherY <= y+3) {
//        return true;
//    }
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
    
}


bool Boulder::isCoordinate(int otherX, int otherY, string &type) {
    int x = getX();
    int y = getY();
    type = boulder;
    
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
}
bool Barrel::isCoordinate(int otherX, int otherY, string &type) {
    int x = getX();
    int y = getY();
    type = barrel;
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
}
bool Protester::isCoordinate(int otherX, int otherY, string &type) {
    int x = getX();
    int y = getY();
    type = protester;
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
}
bool WaterPool::isCoordinate(int otherX, int otherY, string &type) {
    int x = getX();
    int y = getY();
    type = waterpool;
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
}
bool SonarKit::isCoordinate(int otherX, int otherY, string &type) {
    int x = getX();
    int y = getY();
    type = sonarkit;
    for (int k = x; k <= x +3; k++) {
        for (int j = y; j <= y+3; j++) {
            if (k == otherX && j == otherY) {
                return true;
            }
        }
    }
    return false;
}
void Boulder::setState(string state) {
    m_state = state;
}

void Boulder::doSomething() {
    if (!isAlive()) {
        return;
    }
    int x = getX();
    int y = getY();
    //if it's stable, set to waiting.
    if (getState() == stable) {
        if (!getWorld()->isthereEarth(x, y - 1)) {
            setState(waiting);
        }
    }
    if (waitingNum == 0) {
        setState(falling);
        getWorld()->playSound(SOUND_FALLING_ROCK);
        waitingNum = -1;
    }

    if (getState() == falling) {
        // As long as there isn't earth below and y is valid we can move down
        // TODO: check for a bolder
        string type = "";
        int xP = playerInGame->getX();
        int yP = playerInGame->getY();
        if (y-1 == -1 || getWorld()->isthereEarth(x, y - 1) || getWorld()->isBoulderthere(x, y-5)) {
            setDead();
            
        }
        
        if (!getWorld()->isthereEarth(x, y - 1)) {
            moveTo(x, y - 1);
        }
        int XL = xP - 3;
        int XR = xP + 3;
        int YL = yP - 3;
        int YR = yP + 3;
        if (XL <= x && x <= XR){
            if (YL <= y && y <= YR) {
                setDead();
                getWorld()->decLives();
                playerInGame->setDead();
                //getWorld()->returnDeadplayer(); // here
            }
        }
        
        // Need to figure out how to not run into other boulders. I think something like we had in Zion like nRobotsAt?? like a function to check if a boulder/object is at that location. Maybe it could take in a class type so we can template it for other classess???
        
    }
    // TODO: check if it's near a Protestor or Tunnelman & annoy them.
    // Decrement each tick if waiting to fall
    if (getState() == waiting) {
        waitingNum--;
    }
}
Goodies::Goodies(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Actor(sw, imageID, startX, startY, dir, size, depth) {

}
Goodies::~Goodies() {
    
}

Barrel::Barrel(StudentWorld* sw, int startX, int startY, Tunnelman* p) : Goodies(sw, TID_BARREL, startX, startY, right, 1, 2) {
//    m_x = startX;
//    m_y = startY;
    playerInGame = p;
    found = false;
    //count++;
}
string Barrel::classType() {
    return barrel;
}

void Barrel::doSomething() {
    if (!isAlive()) {
        return;
    }
    int x = playerInGame->getX();
    int y = playerInGame->getY();
   
    
    // If not foudn yet, if it's within 4 of tunnelman, found it
    if (found != true) {
        if (getX() - 4 <= x && x <= getX() + 4) {
            if (getY() - 4 <= y && y <= getY() + 4) {
                setVisible(true);
                found = true;
                return;
            }

        }
    }
    
    
    // If found, set Dead, play sound, increase score, decrement barrels
    else {
//        if (m_x - 3 <= x && x <= m_x + 3) {
//            if (m_y - 3 <= y && y <= m_y + 3) {
                setDead();
                getWorld()->playSound(SOUND_FOUND_OIL);
                getWorld()->increaseScore(1000);
                getWorld()->decrementBarrelCount();
                
            }
            
//        }
//    }
   

   
}
void Barrel::makeVisible() {
    found = true;

}
Barrel::~Barrel() {
}
void Barrel::setState(string state) {
    m_state = state;
}

void Tunnelman::doSomething() {

    int ch;
    int x = getX();
    int y = getY();

    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        string type = "";
        switch (ch)
        {
        case KEY_PRESS_LEFT:
            if (this->getDirection() != left) {
                this->setDirection(left);
                break;
            }
            if (x != 0) {
                if (!getWorld()->whatsAtThisLocation(x-1, y)) {
//                    if (type != boulder) {
                        moveTo(x - 1, y);
//                    }
                }
            }
                
                break;
            case KEY_PRESS_RIGHT:
                if (this->getDirection() != right) {
                    this->setDirection(right);
                    break;
                }
                if (x != 60) {
                    if (!getWorld()->whatsAtThisLocation(x+1, y)) {
//                        if (type != boulder) {
                            moveTo(x + 1, y);
//                        }
                    }
                }
                break;
            case KEY_PRESS_UP:
                if (this->getDirection() != up) {
                    this->setDirection(up);
                    break;
                }
                
                if (y != 60) {
                    if (!getWorld()->whatsAtThisLocation(x, y+1)) {
//                        if (type != boulder) {
                            moveTo(x, y + 1);
//                        }
                    }
                }
                
                break;
            case KEY_PRESS_DOWN:
                if (this->getDirection() != down) {
                    this->setDirection(down);
                    break;
                }
                if (y != 0) {
                    if (!getWorld()->whatsAtThisLocation(x, y-1)) {
//                        if (type != boulder) {
                            moveTo(x, y - 1);
//                        }
                    }
                }
                break;
            case KEY_PRESS_SPACE:
                getWorld()->shoot(x,y);
                break;
            case KEY_PRESS_ESCAPE:
                getWorld()->decLives();
                getWorld()->returnDeadplayer();
                setDead();
                break;
            case none:
                return;
                // etcÖ
        }
        //        Direction d = getDirection();
        //        int x = getX();
        //        int y = getY();
        
        if (getWorld()->isthereEarth(getX(), getY())) {
            getWorld()->digField(getX(), getY());
            getWorld()->playSound(SOUND_DIG);
            
        }
        
    }
}

Protester::Protester(StudentWorld* sw, int startX, int startY) : Actor(sw, TID_PROTESTER, startX, startY, left, 1, 0) {
    setVisible(true);
    m_hp = 5;
    numSquaresToMoveInCurrentDirection = rand() % (60-8 +1) +8;
    isLeaveFieldState = false;
    waitingNum = 3;
}

Protester::~Protester() {
    
}
string Protester::classType() {
    return protester;
}
void Protester::move() {
    int x = getX();
    int y = getY();
    string type = "";
    Direction direction = getDirection();
    if (direction == left) {
        if (x != 0) {
            if (!getWorld()->isthereEarth(x-1, y)) {
                if (!getWorld()->whatsAtThisLocation(x-1, y)) {
//                    if (type != boulder) {
                        moveTo(x - 1, y);
//                    }
                }
                else if (type == protester) {
                    moveTo(x - 1, y);
                }
            }
        }
    }
    if (direction == right) {
        if (x != 60) {
            if (!getWorld()->isthereEarth(x+1, y)) {
                if (!getWorld()->whatsAtThisLocation(x+1, y)) {
//                    if (type != boulder) {
                        moveTo(x + 1, y);
//                    }
                }
                else if (type == protester) {
                    moveTo(x + 1, y);
                }
            }
        }
    }
    if (direction == up) {
        if (y != 60) {
            if (!getWorld()->isthereEarth(x, y+1)) {
                if (!getWorld()->whatsAtThisLocation(x, y+1)) {
//                    if (type != boulder) {
                        moveTo(x, y + 1);
//                    }
                }
                else if (type == protester) {
                    moveTo(x, y+1);
                }
            }
        }
    }
    if (direction == down) {
        if (y != 0) {
            if (!getWorld()->isthereEarth(x, y-1)) {
                if (!getWorld()->whatsAtThisLocation(x, y-1)) {
//                    if (type != boulder) {
                        moveTo(x, y - 1);
//                    }
                }
                else if (type == protester) {
                    moveTo(x, y-1);
                }
            }
        }
    }
    
}

void Protester::doSomething() {
    if (!isAlive()) {
        return;
    }
    // resting state
    if (waitingNum !=0) {
        waitingNum--;
        return;
    }
    if (numSquaresToMoveInCurrentDirection==0) {
        int dir = rand() % 4;
        if (dir == 0) {
            setDirection(left);
        }
        if (dir == 1) {
            setDirection(right);
        }
        if (dir==2) {
            setDirection(up);
        }
        if (dir ==3) {
            setDirection(down);
        }
        numSquaresToMoveInCurrentDirection = rand() % (60-8 +1) +8;
    }
    else if (waitingNum == 0) {
        
//        if (isLeaveFieldState) {
//            // find a way to quickly exit
//        }
//        else {
            move();
            numSquaresToMoveInCurrentDirection--;
            // if (closetoTunnelman & facingTunnelman) {
                // play yell sound dont yell for another 15 non-resting ticks
                // Deduct 2 hp from TM
            // if (close but !facingTunnelman) {
            // Is in a straight horizontal or vertical line of sight to the Tunnelman  AND Is more than 4 units away from the Tunnelman – that is, the radius from the Regular Protester and the Tunnelman is greater than 4.0 units away, AND Could actually move the entire way to the Tunnelman with no Earth or Boulders blocking its path4 (assuming it kept walking straight over th next N turns),
            // (if in View of tunnelman && is > 4 units away && has clear path to TM) {
                // Change its direction to face in the direction of the Tunnelman, AND then take one step toward him.
                // b. The Regular Protester will set its numSquaresToMoveInCurrentDirection value to zero, forcing it to pick a new direction/distance to move during its next non-resting tick (unless of course, the Regular Protester still sees theTunnelman in its line of sight, in which case it will continue to move toward the Tunnelman).
                // Immediately return
            // ELSE (can't see tunnelman) {
                // decrement numSquares to move
            // if numSquares to move == 0 {
            
        }
//    }
}


Squirt::Squirt(StudentWorld* sw, int startX, int startY, Tunnelman* p,Direction d) : Actor(sw, TID_WATER_SPURT, startX, startY,dir, 1, 1) {
    setVisible(true);
    m_state = stable;
    waitingNum = 4; //travel distance
    playerInGame = p;
    dir = d;
}

Squirt::~Squirt() {
}
string Squirt::classType() {
    return squirt;
}

void Squirt::setState(string state) {
    m_state = state;
}

void Squirt::doSomething() {
    if (!isAlive()) {
        return;
    }
    int x = getX();
    int y = getY();
    int xP = playerInGame->getX();
    int yP = playerInGame->getY();
    if (waitingNum == 0) {
        setDead();
    }
    if (waitingNum <= 4) {
        if (playerInGame->getDirection() == right) {
            setDirection(right);
           // while (waitingNum != 0) {
                if (getWorld()->isthereEarth(x + 1, y) == true) {
                    setDead();
                    waitingNum = 0;
                }
                else {
                    moveTo(x + 1, y);
                    x++;
                    waitingNum--;
                }
            //}
            
        }
        if (playerInGame->getDirection() == left) {
            setDirection(left);
            //while (waitingNum != 0) {
                if (getWorld()->isthereEarth(x - 1, y) == true) {
                    setDead();
                    waitingNum = 0;
                }
                else {
                    moveTo(x - 1, y);
                    x--;
                    waitingNum--;
                }
           // }
        }
        if (playerInGame->getDirection() == up) {
            setDirection(up);
           // while (waitingNum != 0) {
                if (getWorld()->isthereEarth(x, y + 1) == true) {
                    setDead();
                    waitingNum = 0;
                }
                else {
                    moveTo(x, y + 1);
                    y++;
                    waitingNum--;
                }
           // }
        }
        if (playerInGame->getDirection() == down) {
            setDirection(down);
           // while (waitingNum != 0) {
                if (getWorld()->isthereEarth(x, y - 1) == true) {
                    setDead();
                    waitingNum = 0;
                }
                else {
                    moveTo(x, y - 1);
                    y--;
                    waitingNum--;
                }
           // }
        }
    }
    
}
///WATERPOOL CLASS///

WaterPool::WaterPool(StudentWorld* sw, int startX, int startY, Tunnelman* p) : Goodies(sw, TID_WATER_POOL, startX, startY, right, 1, 2) {
    //    m_x = startX;
    //    m_y = startY;
    playerInGame = p;
    setVisible(true);
    m_state = stable; // stable aka waiting
    //found = false;
     waitingNum = std::max(100, 300 - 10 * (static_cast<int>(getWorld()->getLevel())));
 
}
void WaterPool::setState(std::string state) {
    m_state = state;
}
void WaterPool::doSomething() {
    int x = playerInGame->getX();
    int y = playerInGame->getY();
    if (!isAlive()) {
        return;
    }
    if (waitingNum == 0) {
        setVisible(false);
        setDead();
    }
    // If found
    //if (getX() == x && getY()== y) {
    if (getX() - 3 <= x && x <= getX() + 3) {
        if (getY() - 3 <= y && y <= getY() + 3) {
            getWorld()->playSound(SOUND_GOT_GOODIE);
            playerInGame->increaseSquirts(5);
            getWorld()->increaseScore(100);
            setDead(); // ?
        }
    }
    
    waitingNum--;

}
string WaterPool::classType() {
    return waterpool;
}

WaterPool::~WaterPool() {
}

