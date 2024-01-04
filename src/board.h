// board.h

#pragma once
#include "coin.h"
#include <string>

namespace coinWanderer
{
    class Board
    {
    public:
        Board(int, int);
        void start();
        
    private: 
    int boardDimensionX; //Board dimension X, where the number of Columns are stored
    int boardDimensionY; //Board dimension Y, where the number of Rows are stored
    Coin* firstCoin; //Holds the first coin pointer for iterating through the coin linked list
    int playerPositionX; //Holds the current player position X co-ordinate
    int playerPositionY; //Holds the current player position Y co-ordinate

        bool makeMove();
        void emptyInputBuffer();
        void printInstructions();
        void printBoard();
        void removeAllCoins();
        void createCoin();
        void removeCoin();
        void printMoves(std::string);
        std::string getMoves();
    };
}