//coin.cpp

#include "coin.h"

namespace coinWanderer
{
    Coin::Coin(int posX, int posY) {
        coinPositionX = posX;   //The X co-ordinate this coin was placed at
        coinPositionY = posY;   //The X co-ordinate this coin was placed at
        nextCoinPtr = nullptr;  //When a new coin is created, it is always added to the end of the linked list, therefore it will have no next coin yet
    }

    int Coin::getX() {
        return coinPositionX;
    }

    int Coin::getY() {
        return coinPositionY;
    }

    Coin* Coin::getNextPointer() {
        return nextCoinPtr;
    }

    void Coin::setNextPointer(Coin* coinPtr) {
        if (getNextPointer() != nullptr) { throw; } //Ensures that there are no calls to setNextPointer where a Coin is being lost
        nextCoinPtr = coinPtr;
    }
}