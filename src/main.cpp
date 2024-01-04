//main.cpp

#include "board.h"
#include <iostream>

int inputInt() {
/*
Used to take user inputs for the dynamic board size
*/
    int x;
    std::cin >> x;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Error: Invalid Int" << std::endl;
        std::cout << "Please try again..." << std::endl;
        std::cin >> x;
    }
    std::cin.ignore(); //Empties the buffer of other characters
    return x;
}

int main() { 
    /*
    Main - Runs the game from a external (public) class (Also requests dimension inputs to demonstrate the dynamic sizing capability of the class)
    */
    std::cout << "Enter board Column dimension... (Default = 7)" << std::endl;
    int dimX = inputInt();
    std::cout << "Enter board Row dimension...    (Default = 5)" << std::endl;
    int dimY = inputInt();
    coinWanderer::Board game(dimX, dimY);
    game.start();
    return 0;
}