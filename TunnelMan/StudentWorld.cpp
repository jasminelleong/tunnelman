#include "StudentWorld.h"
#include "Actor.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir)
{
}

StudentWorld::~StudentWorld() {


}

int StudentWorld::init()
{
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            if (y < 4 || x != 30 && x != 31 && x != 32 && x != 33 && y < 60) {
                earthPtrs[x][y] = new Earth(this, x, y);
            }
            else {
                earthPtrs[x][y] = nullptr;
            }
        }
    }
    player = new Tunnelman(this);

    // Create boulders where # of boulders  min(current_level_number/2+2, 9)
    // Boulders must be distributed between x=0,y=20 and x=60,y=56, inclusive (so
    // they have room to fall).
    //revist the loop that doesnt include the shaft
    int numBoulders = std::min((static_cast<int>(getLevel()) / 2) + 2, 9);
    string type = "";
    for (int i = 0; i < numBoulders; i++) {
        int x{};
        int y{};
        do {
            do {
                x = rand() % 61;
//                x = 17;
            }
            while (x >= 28 && x <= 35);
            y = rand() % (57 - 20 + 1) + 20;
        } while (hasSomething(x, y, type));
        
        actorPtrs.push_back(new Boulder(this, x, y));
        setLocation(x, y);
        digField(x, y);
    }
  
    int numBarrels = std::min((static_cast<int>(2+getLevel())), 21);
    for (int i = 0; i < numBarrels; i++) {
        int x{};
        int y{};
            // Keep generating x y coordinates if there's something there or it's not in correct bounds
        do {
            do {
                x = rand() % 61;
            }
            while (x >= 28 && x <= 35);
            y = rand() % (57 - 20 + 1) + 20;
        } while (hasSomething(x, y, type));
        actorPtrs.push_back(new Barrel(this, x, y, player));
        barrelCount++;
        setLocation(x, y);
        //digField(x, y);
    }
    return GWSTATUS_CONTINUE_GAME;
}

// This function checks if there is an actor (not tunnelman) something at the x, y coordinate
// It loops through actor pointers and checks if it has an overlapping coordinate
// Designed to take an x & y position from tunnelman, so it checks if anything in the 4x4 square of the actor matches the 4x4 square of the tunnelman
bool StudentWorld::hasSomething(int xPos, int yPos, string& type) {
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();
    
    while (it!=actorPtrs.end()) {
        for (int i = xPos; i <= xPos +3; i ++) {
            for (int k = yPos; k <= yPos +3; k++) {
                if ((*it)->isCoordinate(i, k)) {
                    return true;
                }
            }
        }
        
        it++;
    }
    

    return false;
}
void StudentWorld::setLocation(int xPos, int yPos) {
    for (int k = xPos; k <= xPos + 5 && (k >= 0 && k < VIEW_WIDTH); k++) {
        for (int j = yPos; j <= yPos + 5 && (j >= 0 && j < VIEW_HEIGHT); j++) {
            BoulderPtrs[xPos][yPos] = true;
        }
    }
 
}

bool StudentWorld::isBoulderthere(int xPos, int yPos) {
    
    // xPos & yPos is related to the tunnelman :(
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();
    for (int k = xPos; k <= xPos + 3 && (k >= 0 && k < VIEW_WIDTH); k++) {
        for (int j = yPos; j <= yPos + 3 && (j >= 0 && j < VIEW_HEIGHT); j++) {
            while (it != actorPtrs.end()) {
                if ((*it)->getX() == k && (*it)->getY() == j) {
                    return true;
                }
                it++;
            }
        }
    }
    return false;

}
void StudentWorld::setDisplayText() {
    int level = getLevel();
    int lives = getLives();
    int health = player->hp();
    int squirts = player->numWater();
    int gold = player->numGold();
    int barrelsLeft = barrelCount;
    int sonar = player->numSonar();
    int score = getScore();
    string s;
    s = "Time: " + std::to_string(tick) + " Lvl: " + std::to_string(level) + " Lives: " + std::to_string(lives) + " Hlth: " + std::to_string(health) + "% Wtr: " + std::to_string(squirts) + " Gld: " + std::to_string(gold) + " Oil Left: " + std::to_string(barrelsLeft) + " Sonar: " + std::to_string(sonar) + " Scr: " + std::to_string(score);
    setGameStatText(s);
}
int StudentWorld::move()
{
    /// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //
    if (barrelCount == 0) {
        vector<Actor*>::iterator it;
                it = actorPtrs.begin();
                    // delete boulders at end of the level
                while (it != actorPtrs.end()) {

                    if((*it)->getID() == TID_BOULDER){
                        delete (*it);
                        it = actorPtrs.erase(it);
                    }

                    /*if ((*it)->getID() == TID_BARREL) {
                        delete (*it);
                        it = actorPtrs.erase(it);
                    }*/
                }
                //advanceToNextLevel();
                return GWSTATUS_FINISHED_LEVEL;
    }
//    tick++;
    
    setDisplayText();
   //decLives();
    player->doSomething();
 
    // Allow all actors to do something
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();
    while (it != actorPtrs.end()) {
        (*it)->doSomething();
        it++;
    }
    
    
    // Loop through actors and remove dead ones
    it = actorPtrs.begin();
    while (it != actorPtrs.end()) {

        if (!(*it)->isAlive()) {
           delete (*it);
           it = actorPtrs.erase(it);
        }
        else {
            it++;
        }
    }

    

    return GWSTATUS_CONTINUE_GAME;
   // return barrelCount;
}


void StudentWorld::cleanUp()
{
    delete player;
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            delete earthPtrs[x][y];
        }
    }
    // TODO: check how to delete the rest of the pointers for cleanup lol
//    vector<Actor*>::iterator it;
//    it = actorPtrs.begin();
//    while (it != actorPtrs.end()) {
//        delete (*it);
//        it = actorPtrs.erase(it);
//        it ++;
//    }
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
/*Remove/destroy the Earth objects from the 4x4 area occupied by
the Tunnelman (from x, y to x+3,y+3 inclusive)*/
void StudentWorld::digField(int x, int y) {
    //    if (earthPtrs[x][y] != nullptr) {
    for (int k = x; k <= x + 3 && (k >= 0 && k < VIEW_WIDTH); k++) {
        for (int j = y; j <= y + 3 && (j >= 0 && j < VIEW_HEIGHT); j++) {
            delete earthPtrs[k][j];
            earthPtrs[k][j] = nullptr;
        }
    }
    //    }
}

bool StudentWorld::isthereEarth(int x, int y) {
    for (int k = x; k <= x + 3 && (k >= 0 && k < VIEW_WIDTH); k++) {
        for (int j = y; j <= y + 3 && (j >= 0 && j < VIEW_HEIGHT); j++) {
            if (earthPtrs[k][j] != nullptr)
                return true;
        }
    }
    return false;


}

void StudentWorld::decrementBarrelCount() {
    if (barrelCount != 0) {
        barrelCount--;
    }
}
