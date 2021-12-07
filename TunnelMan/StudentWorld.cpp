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
            if (y <4 || x != 30 && x != 31 && x != 32 && x != 33 && y < 60) {
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
    int numBoulders = std::min((static_cast<int>(getLevel())/2)+2, 9);
    for (int i = 0; i < numBoulders; i ++) {
        int x = rand() % 61;
        int y = rand() %(57-20 +1) + 20;
        actorPtrs.push_back(new Boulder(this, x, y));
        digField(x, y);
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    /// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //
    setDisplayText();
    
    if (player->isAlive()) {
        player->doSomething();
    }
    else {
        return GWSTATUS_PLAYER_DIED;
    }
    // Iterate through actor vector and allow everyone a chance to do something
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();
    while (it != actorPtrs.end()) {
        if ((*it)->isAlive()) {
            (*it)->doSomething();
        }
        it++;
    }
    it = actorPtrs.begin();
    
    
    while (it != actorPtrs.end()) {
        if (!(*it)->isAlive()) {
            delete (*it);
            actorPtrs.erase(it);
        }
        else {
            it++;
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete player;
    for (int x = 0; x < VIEW_WIDTH; x++) {
        for (int y = 0; y < VIEW_HEIGHT; y++) {
            delete earthPtrs[x][y];
        }
    }
}

void StudentWorld::setDisplayText(){
    int level = getLevel();
    int lives = getLives();
    int health = player->hp();
    int squirts = player->numWater();
    int gold = player->numGold();
    int barrelsLeft = 111;
    int sonar = player->numSonar();
    int score = getScore();
    string s;
    s = "Lvl: " + std::to_string(level) + " Lives: " + std::to_string(lives) + " Hlth: " + std::to_string(health) + "% Wtr: " + std::to_string(squirts) + " Gld: " + std::to_string(gold) + " Oil Left: " + std::to_string(barrelsLeft) + " Sonar: " + std::to_string(sonar) + " Scr: " + std::to_string(score);
    setGameStatText(s);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
/*Remove/destroy the Earth objects from the 4x4 area occupied by
the Tunnelman (from x, y to x+3,y+3 inclusive)*/
void StudentWorld::digField(int x, int y) {
//    if (earthPtrs[x][y] != nullptr) {
        for (int k = x; k <= x + 3 && (k >=0 && k < VIEW_WIDTH); k++) {
            for (int j = y; j<= y + 3 && (j >= 0 && j < VIEW_HEIGHT); j++) {
                delete earthPtrs[k][j];
                earthPtrs[k][j] = nullptr;
            }
        }
//    }
}

bool StudentWorld::isthereEarth(int x, int y){
    for (int k = x; k <= x + 3 && (k >=0 && k <VIEW_WIDTH); k++) {
        for (int j = y; j<= y + 3 && (j >= 0 && j <VIEW_HEIGHT); j++) {
            if (earthPtrs[k][j] != nullptr)
                return true;
        }
    }
        return false;
    

}

