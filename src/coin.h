// coin.h

#pragma once
namespace coinWanderer
{
    class Coin
    {
    public:
        Coin(int, int);
        int getX();
        int getY();
        Coin* getNextPointer();
        void setNextPointer(Coin*);
        
    private:
        int coinPositionX; //Holds the coin's X co-ordinate
        int coinPositionY; //Holds the coin's Y co-ordinate
        Coin* nextCoinPtr; //Holds the pointer for a next coin (Updated with setNextPointer(Coin*))
    };
}