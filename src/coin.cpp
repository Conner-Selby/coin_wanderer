//coin.cpp

#include "coin.h"

namespace coinWanderer
{
    Coin::Coin(int posX, int posY) {
        /*
        Creates a new coin object at location posX, posY. Assumes no nextCoin.
        */
        coinPositionX = posX;   //The X co-ordinate this coin was placed at
        coinPositionY = posY;   //The X co-ordinate this coin was placed at
        nextCoinPtr = nullptr;  //When a new coin is created, it is always added to the end of the linked list, therefore it will have no next coin yet
    }

    int Coin::getX() {
        /*
        X location getter function, protecting position by practicing encapsulation
        */
        return coinPositionX;
    }

    int Coin::getY() {
        /*
        Y location getter function, protecting position by practicing encapsulation
        */
        return coinPositionY;
    }

    Coin* Coin::getNextPointer() {
        /*
        Next coin getter function, protects the pointers by practicing encapsulation
        */
        return nextCoinPtr;
    }

    void Coin::setNextPointer(Coin* coinPtr) {
        /*
        Used to set the nextCoinPtr variable for adding coins, tests to ensure no existing coin address is being overwritten.
        */
        if (getNextPointer() != nullptr) { throw; } //Ensures that there are no calls to setNextPointer where a Coin is being lost
        nextCoinPtr = coinPtr;
    }
}