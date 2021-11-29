#include "Actor.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GraphObject(imageID, startX, startY, dir, size, depth) {
    m_world = sw;
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


Tunnelman::Tunnelman(StudentWorld* sw) : Actor(sw, TID_PLAYER, 30, 60, right, 1, 0) {
    isAlive = true;
    setVisible(true);

}

void Tunnelman::doSomething() {

    int ch;
   
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        switch (ch)
        {
        case KEY_PRESS_LEFT:
            if (this->getDirection() != left) {
                this->setDirection(left);
                break;
            }
            if (getX() != 0) {
                moveTo(getX()-1, getY());
            }

            break;
        case KEY_PRESS_RIGHT:
            if (this->getDirection() != right) {
                this->setDirection(right);
                break;
            }
            if (getX() != 60) {
                moveTo(getX()+1, getY());
//                if (m_world->isthereEarth(getX()+1, getY())) {
//                    m_world->digField(getX()+1, getY());
//                    m_world->digField(getX()+2, getY());
//                    m_world->playSound(SOUND_DIG);
//                }
            }
            break;
        case KEY_PRESS_UP:
            if (this->getDirection() != up) {
                this->setDirection(up);
                break;
            }
                
            if (getY() != 60) {
                moveTo(getX(), getY()+1);
//                if (m_world->isthereEarth(getX(), getY())) {
//                    m_world->digField(getX(), getY());
//                    m_world->playSound(SOUND_DIG);
//                }
            }

            break;
        case KEY_PRESS_DOWN:
            if (this->getDirection() != down) {
                this->setDirection(down);
                break;
            }
            if (getY() != 0) {
                moveTo(getX(), getY()-1);
//                if (m_world->isthereEarth(getX(), getY())) {
//                    m_world->digField(getX(), getY());
//                    m_world->playSound(SOUND_DIG);
//                }
            }
            break;
        case KEY_PRESS_SPACE:

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


