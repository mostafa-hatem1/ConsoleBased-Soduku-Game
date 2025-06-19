#ifndef SUDOKU_GAME_HPP
#define SUDOKU_GAME_HPP

#include "SudokuBoard.hpp"

class SudokuGame {
    private:
        SudokuBoard board;
        
        
        void printMenu() const;
        void enterMove();
        void solveAutomatically();
        void generateRandomPuzzle(string level);

    public:
        SudokuGame();

        void start(); 
        void handleSaveToFile(const string& filename) const;
        void handleLoadFromFile(const string& filename);
};

#endif // SUDOKU_GAME_HPP