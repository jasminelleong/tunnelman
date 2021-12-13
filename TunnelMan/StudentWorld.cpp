#include "StudentWorld.h"
#include "Actor.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

const string earth = "earth";
const string tunnelman = "tunnelman";
const string boulder = "boulder";
const string barrel = "barrel";
const string waterpool = "waterpool";
const string perm = "perm";

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir)
{
}

StudentWorld::~StudentWorld() {


}
void StudentWorld::shoot(int x, int y) {
    m_shoot = true;
}

void StudentWorld::returnDeadplayer() {
    m_restart = true;
}
void StudentWorld::populateEarth() {
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
}
// Create boulders where # of boulders  min(current_level_number/2+2, 9)
// Boulders must be distributed between x=0,y=20 and x=60,y=56, inclusive (so
// they have room to fall).
//revist the loop that doesnt include the shaft
void StudentWorld::populateBoulders() {
    int numBoulders = std::min((static_cast<int>(getLevel()) / 2) + 2, 9);

    string type = "";
    for (int i = 0; i < numBoulders; i++) {
        int x{};
        int y{};
        do {
            do {
                x = rand() % 61;
                //                x = 17;
            } while (x >= 28 && x <= 35);
            y = rand() % (57 - 20 + 1) + 20;
        } while (hasSomething(x, y, type));

        actorPtrs.push_back(new Boulder(this, x, y, player));
//        setLocation(x, y);
        digField(x, y);
    }
}
void StudentWorld::populateBarrels() {
    string type = "";
    int numBarrels = std::min((static_cast<int>(2 + getLevel())), 21);
    for (int i = 0; i < numBarrels; i++) {
        int x{};
        int y{};
        // Keep generating x y coordinates if there's something there or it's not in correct bounds
        do {
            do {
                x = rand() % 61;
            } while (x >= 28 && x <= 35);
            y = rand() % (57 - 20 + 1) + 20;
        } while (hasSomething(x, y, type));
        actorPtrs.push_back(new Barrel(this, x, y, player));
        barrelCount++;
//        setLocation(x, y);
        digField(x, y);
    }
}
void StudentWorld::populatePoolsOrSonar() {
    string type = "";
    int G = (int)getLevel() * 25 + 300;
    int chanceForwater = rand() % G + 1;
    int chance = rand() % 6 + 1;
    int x{};
    int y{};
    if (chanceForwater == 1) {
        if (chance <= 4) {

            do {
                x = rand() % 61;
                y = rand() % 61;
            } while (isthereEarth(x, y) == true);
            if (hasSomething(x, y, type) != true) {
                actorPtrs.push_back(new WaterPool(this, x, y, player));
            }

        }
        else {
            actorPtrs.push_back(new SonarKit(this, 0, 60, player));
        }
    }
}
//void StudentWorld::populateSonar() {
//    //sonars are generated here
//    int G = (int)getLevel() * 25 + 300;
//    int sonarChance = rand() % G + 1;
//    if (sonarChance == 1) {
//        if (rand() % 6 + 1 == 1) {
//
//            actorPtrs.push_back(new SonarKit(this, 0, 60, player));
//
//        }
//    }
//}
void StudentWorld::populateNuggets() {
    std::string type = "";
    int tempGold = 0;
    int permGold = 0;
    int N = (static_cast<int>(getLevel())) / 2;
    int G = std::max(5 - N, 2);
    //if (G % 2 == 0) {
    //    tempGold = G / 2;
    //    permGold = G / 2;
    //}
    //if (G % 2 != 0) { // 5/2 = 3
    //     tempGold = G / 2;
    //     permGold = tempGold-1;
    //}
    for (int i = 0; i < G; i++) {
        int x{};
        int y{};
        do {
            do {
                x = rand() % 61;
            } while (x >= 28 && x <= 35);
            y = rand() % (57 - 20 + 1) + 20;
        } while (hasSomething(x, y, type));
        actorPtrs.push_back(new Nuggets(this, x, y, player,perm));
        setLocation(x, y);
//        digField(x, y);
    }
}
void StudentWorld::dropGold() {
    actorPtrs.push_back(new Nuggets(this, player->getX(), player->getY(), player,temp));
}
int StudentWorld::init()
{
    populateEarth();
    player = new Tunnelman(this);
    populateBoulders();
    populateBarrels();
    populateNuggets();
    tick = 0;
  
    return GWSTATUS_CONTINUE_GAME;
}
//could this be specific to tunnelmans walking , like he can walk and collect barrels and pools and sonar
bool StudentWorld::whatsAtThisLocation(int xPos, int yPos) {
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();

    while (it != actorPtrs.end()) {
        for (int i = xPos; i <= xPos + 3; i++) {
            for (int k = yPos; k <= yPos + 3; k++) {
                if ((*it)->getID() == TID_WATER_POOL) {
                    return false;
                }
                if ((*it)->getID() == TID_BARREL) {
                    return false;
                }
                
                if ((*it)->isCoordinate(i, k)) {
                    return true;
                }
            }
        }

        it++;
    }
    return false;
}
// This function checks if there is an actor (not tunnelman) something at the x, y coordinate
// It loops through actor pointers and checks if it has an overlapping coordinate
// Designed to take an x & y position from tunnelman, so it checks if anything in the 4x4 square of the actor matches the 4x4 square of the tunnelman
bool StudentWorld::hasSomething(int xPos, int yPos, string& type) {
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();

    while (it != actorPtrs.end()) {
        for (int i = xPos; i <= xPos + 3; i++) {
            for (int k = yPos; k <= yPos + 3; k++) {
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
bool StudentWorld::protestorLocator(int x, int y) {
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();

    while (it != actorPtrs.end()) {

        if ((*it)->getID() == TID_PROTESTER) {

            int X = (*it)->getX();
            int Y = (*it)->getY();
            for (int k = X; k <= X + 3; k++) {
                for (int j = Y; j <= Y + 3; j++) {
                    if (k == x && j == y) {

                        return true;
                    }
                }
            }
            return false;

        }

        it++;
    }
    return true;
    
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
    s = "Time: " + std::to_string(tick) + " Lvl: " + std::to_string(level) + " Lives: " + std::to_string(lives) + " Hlth: " + std::to_string(10*health) + "% Wtr: " + std::to_string(squirts) + " Gld: " + std::to_string(gold) + " Oil Left: " + std::to_string(barrelsLeft) + " Sonar: " + std::to_string(sonar) + " Scr: " + std::to_string(score);
    setGameStatText(s);
}
int StudentWorld::move()
{
    tick++;
    string type = "";
   
    if (tick == 1) {
        //TODO: where is he actually supposed to appear not sure
        actorPtrs.push_back(new Protester(this, 25, 60, player));
    }
    /// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //
    if (barrelCount == 0) {
        vector<Actor*>::iterator it;
        it = actorPtrs.begin();
        // delete boulders at end of the level
        while (it != actorPtrs.end()) {

            /*if ((*it)->getID() == TID_BOULDER) {
                delete (*it);
                it = actorPtrs.erase(it);
            }*/
            
                delete (*it);
                it = actorPtrs.erase(it);


        }
        tick = 0;
        return GWSTATUS_FINISHED_LEVEL;
    }
    //if player presses escape delete actors return player died
    if (m_restart == true) {
        m_restart = false;
        // Moved this code to cleanup() function
//        vector<Actor*>::iterator it;
//        it = actorPtrs.begin();
//        while (it != actorPtrs.end()) {
//            delete (*it);
//            it = actorPtrs.erase(it);
//        }
//        tick = 0;
        return GWSTATUS_PLAYER_DIED;
    }
    // if player is not alive, delete stuff and restart level
    if (player->isAlive() != true) {
        vector<Actor*>::iterator it;
        it = actorPtrs.begin();
        while (it != actorPtrs.end()) {
                delete (*it);
                it = actorPtrs.erase(it);
        }
        barrelCount = 0; // needed to reset level barrel count
        tick = 0;
        return GWSTATUS_PLAYER_DIED;
    }
    
    if (m_shoot == true && player->numWater()!=0) {
        actorPtrs.push_back(new Squirt(this, player->getX(), player->getY(), player,player->getDirection()));
        player->decreaseSquirts();
        m_shoot = false;
        
    }

    setDisplayText();
    player->doSomething();
    populatePoolsOrSonar();
//    populateSonar();

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
    
    vector<Actor*>::iterator it;
    it = actorPtrs.begin();
    while (it != actorPtrs.end()) {
        delete (*it);
        it = actorPtrs.erase(it);
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
   
    for (int k = x; k <= x + 3 && (k >= 0 && k < VIEW_WIDTH); k++) {
        for (int j = y; j <= y + 3 && (j >= 0 && j < VIEW_HEIGHT); j++) {
            delete earthPtrs[k][j];
            earthPtrs[k][j] = nullptr;
        }
    }
  
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
void StudentWorld::decrementBarrelCount() {
    if (barrelCount != 0) {
        barrelCount--;
    }
}
