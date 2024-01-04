//board.cpp

#include "board.h"
#include "coin.h"
#include <iostream>
#include <string>
#include <cmath>

namespace coinWanderer
{
  Board::Board(int boardDimX = 7, int boardDimY = 5) {
    /*
    Creates a Board object of boardDimX by boardDimY, places a 'X' (player) in the middle.
    */
    if (boardDimX < 1 || boardDimY < 1) {
      std::cout << "Error: Invalid board dimension provided. Values must be integers greater than zero..." << std::endl;
      throw;
      }
    boardDimensionX = boardDimX;
    boardDimensionY = boardDimY;
    playerPositionX = floor(boardDimX / 2); //Sets the player to roughly the middle of the board (Favouring the right)
    playerPositionY = floor(boardDimY / 2); //Sets the player to roughly the middle of the board (Favouring the bottom)
    firstCoin = nullptr; //There are not yet any placed coins
  }

  void Board::printInstructions() {
    /*
    Prints the instructions for navigating the game
    */
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "------------ Welcome to Coin Wanderer ------------" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "This is a simple C++ linked list demo with no win condition" << std::endl;
    std::cout << std::endl;
    std::cout << "Movement controls:" << std::endl;
    std::cout << "  w = Move character UP" << std::endl;
    std::cout << "  a = Move character LEFT" << std::endl;
    std::cout << "  s = Move character DOWN" << std::endl;
    std::cout << "  d = Move character RIGHT" << std::endl;
    std::cout << std::endl;
    std::cout << "Other controls:" << std::endl;
    std::cout << "  e = COIN - New coin on player position" << std::endl;
    std::cout << "  r = COIN - Removes the oldest coin on the board" << std::endl;
    std::cout << "  h = HELP / Instructions" << std::endl;
    std::cout << "  q = QUIT / END GAME!" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

  }

  void Board::start() {
    /*
    Prints the board & instructions. Commences the game input cycle.
    */
    printInstructions();
    printBoard();
    while (makeMove()) {
      continue;
    }
    std::cout << "Thanks for playing the demo!" << std::endl; 
  }

  bool Board::makeMove() {
    /*
    Prints the available moves, then takes an input (repeatedly if invalid input is provided) and executes that command / move.
    */
    std::string availableMoves = getMoves();
    char move;
    printMoves(availableMoves);

    while (true) { //Take inputs until the input is valid according to getMoves()
      std::cout << std::endl << " -- Enter move: ";
      move = getchar(); //Take player input as a char
      if (availableMoves.find(move) < availableMoves.length()) { //If the character is valid: Break the input loop
        std::cout << std::endl;
        emptyInputBuffer();
        break;
      } else {
        emptyInputBuffer();
        std::cout << '\"' << move << "\" is an invalid move, please try again..." << std::endl;
        std::cout << "Need help? Try: h" << std::endl;
      }
    }
    switch (move) {
      case 'w':
      playerPositionY--;
      printBoard();
      return true;

      case 'a':
      playerPositionX--;
      printBoard();
      return true;

      case 's':
      playerPositionY++;
      printBoard();
      return true;
      
      case 'd':
      playerPositionX++;
      printBoard();
      return true;

      case 'e':
      createCoin();
      printBoard();
      return true;

      case 'r':
      removeCoin();
      printBoard();
      return true;

      case 'h':
      printInstructions();
      return true;
      
      case 'q':
      removeAllCoins();
      return false;
    }
    std::cout << "WARNING! Invalid command has bypassed available move check! Ending game..." << std::endl;
    removeAllCoins();
    return false;
  }

  void Board::emptyInputBuffer() {
    /*
    Will empty the input buffer. Used to ensure only one instruction is provided at a time
    */
    char c = 'X';
    while (c != '\n' && c != EOF) {  //Loop until there are no more characters, or next char is '\n'
      c = getchar();
    }
  }

  void Board::printBoard() {
    /*
    Prints the board, with the number of coins representing each space on the board, and the player being represented by an 'X'
    */
    int boardSize = boardDimensionX * boardDimensionY;
    int* coinArray = new int[boardSize];
    std::fill_n(coinArray, boardSize, 0); //Note: While creating an array for each print isn't particularly logical or effective, it was an easy brute force solution with minimal impact at this scale

    Coin* currentCoin = firstCoin;
    while (currentCoin != nullptr) {
      coinArray[(boardDimensionX * currentCoin->getY()) + currentCoin->getX()] += 1;
      currentCoin = currentCoin->getNextPointer();
    }
    coinArray[(boardDimensionX * playerPositionY) + playerPositionX] = -1;

    std::string lnBreak;
    lnBreak.append((boardDimensionX * 2) + 1, '=');
    int valueToPrint;
    std::cout << lnBreak << std::endl;
    for (int row = 0; row < boardDimensionY; row++) {
      for (int column = 0; column < boardDimensionX; column++) {
        valueToPrint = coinArray[(boardDimensionX * row) + column];
        if (valueToPrint == -1) {
        std::cout << " X";
        } else {
        std::cout << " " << std::to_string(valueToPrint);
        }
      }
      std::cout << std::endl;
    }
    delete[] coinArray;
    std::cout << lnBreak << std::endl;
  }

  void Board::removeAllCoins() {
    /*
    Deletes all coin objects, called on program exit
    */
    while (firstCoin != nullptr) {
      removeCoin();
    }
  }

  void Board::createCoin() {
    /*
    Creates a new coin object and adds it into the linked list of coins. If no coin exists: set this as the 'firstCoin'
    */
    Coin* newCoin = new Coin(playerPositionX, playerPositionY); //Create a new coin
    if (firstCoin == nullptr) { //If no coins exist: This new coin is now the first coin
      firstCoin = newCoin;
    } else {                    //Else iterate through the existing coins until we reach the latest coin
      Coin* currentCoin = firstCoin;
      while (currentCoin->getNextPointer() != nullptr) { //While there is a next coin, make the next coin the current coin
        currentCoin = currentCoin->getNextPointer();
      }
      currentCoin->setNextPointer(newCoin); //Now that the final coin has been found: add the new coin to the end of the linked list
    } //Note: This could have been reduced computationally by storing both ends of the linked list, but this way demonstrates iteration and reduces the risk of improperly updating firstCoin and lastCoin
  }

  void Board::removeCoin() {
    /*
    Removes the oldest created coin (firstCoin), then updates the firstCoin pointer to the next coin (If one exists, else it will be set to nullptr as that is the default nextCoinPtr value)
    */
    if (firstCoin != nullptr) {
      Coin* newFirstCoin = firstCoin->getNextPointer();
      delete firstCoin;
      firstCoin = newFirstCoin;
    }
  }

  void Board::printMoves(std::string moves) {
    /*
    Prints a list of available moves to the user
    */
    std::cout << "Available moves: " << std::endl;
    for (char move : moves) {
      std::cout << "|" << move; 
    }
    std::cout << "|" << std::endl;
  }

  std::string Board::getMoves() {
    /*
    Assesses the game-state and returns the available commands as a string (E.g. "wasehq")
    */
    std::string availableMoves = "";
    if (playerPositionY > 0) { //If there is at least 1 space from the top side W is available
      availableMoves = availableMoves.append("w");
    }
    if (playerPositionX > 0) { //If there is at least 1 space from the left side A is available
      availableMoves = availableMoves.append("a");
    }
    if (playerPositionY < boardDimensionY - 1) { //If there is at least 1 space from the bottom side S is available
      availableMoves = availableMoves.append("s");
    }
    if (playerPositionX < boardDimensionX - 1) { //If there is at least 1 space from the right side D is available
      availableMoves = availableMoves.append("d");
    }
    availableMoves = availableMoves.append("e"); //Creating a coin is always available (Assuming that sufficient memory is available)
    if (firstCoin != nullptr) { //If a coin exists then removing a coin is available
      availableMoves = availableMoves.append("r");
    }
    availableMoves = availableMoves.append("h"); //Printing the help menu is always available
    availableMoves = availableMoves.append("q"); //Exiting the program is always available
    return availableMoves;
  }
}