#include "StudentWorld.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    //thisgame->setWorld(this);
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 64; y++) {
            if (y <4 || x != 30 && x != 31 && x != 32 && x != 33 && y < 60) {
                earthPtrs[x][y] = new Earth(this, x, y);
            }
            else {
                earthPtrs[x][y] = nullptr;
            }
        }
    }
    player = new Tunnelman(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    /// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //
    decLives();
    player->doSomething();
    return GWSTATUS_CONTINUE_GAME;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
/*Remove/destroy the Earth objects from the 4x4 area occupied by
the Tunnelman (from x, y to x+3,y+3 inclusive)*/
void StudentWorld::digField(int x, int y) {
//    if (earthPtrs[x][y] != nullptr) {
        for (int k = x; k <= x + 3 && (k >=0 && k <64); k++) {
            for (int j = y; j<= y + 3 && (j >= 0 && j <64); j++) {
                delete earthPtrs[k][j];
                earthPtrs[k][j] = nullptr;
            }
        }
//    }
}

bool StudentWorld::isthereEarth(int x, int y){
    for (int k = x; k <= x + 3 && (k >=0 && k <64); k++) {
        for (int j = y; j<= y + 3 && (j >= 0 && j <64); j++) {
            if (earthPtrs[k][j] != nullptr)
                return true;
        }
    }
        return false;
    

}

