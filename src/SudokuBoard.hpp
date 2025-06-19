#ifndef SUDOKU_BOARD_HPP
#define SUDOKU_BOARD_HPP
#include <vector>
#include <iostream>
using namespace std;

class SudokuBoard {
    private:
        vector<vector<int>> board;
    public:
        SudokuBoard();
        void loadDefaultPuzzle();
        void printBoard() const;
        bool isValidMove(int row, int col, int value) const;
        void setValue(int row, int col, int value);
        int getValue(int row, int col) const;
        void saveToFile(const string& filename) const;
        void loadFromFile(const string& filename);
};
#endif // SUDOKU_BOARD_HPP