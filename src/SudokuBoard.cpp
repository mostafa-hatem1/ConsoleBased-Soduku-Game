#ifndef SUDOKU_BOARD_CPP
#define SUDOKU_BOARD_CPP

#include "SudokuBoard.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

SudokuBoard::SudokuBoard() {
    board.resize(9, vector<int>(9, 0));
    loadDefaultPuzzle();
}

void SudokuBoard::loadDefaultPuzzle() {
    board = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
}

void SudokuBoard::printBoard() const {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << "-------------------------------\n";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0) cout << "| ";
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "-------------------------------\n";
}

bool SudokuBoard::isValidMove(int row, int col, int value) const{
    if(value > 9 || value < 1) return false;
        
    for(int i = 0; i < 9; i++){
        if(board[i][col] == value) return false;
    }

    for(int j = 0; j < 9; j++){
        if(board[row][j] == value) return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j)
        {
            if (board[startRow + i][startCol + j] == value) return false;
        }
        
    }
    return true;    
}

void SudokuBoard::setValue(int row, int col, int value){
    board[row][col] = value;

}

int SudokuBoard::getValue(int row, int col) const {
    return board[row][col];
}


void SudokuBoard::saveToFile(const string& filename) const {
    ofstream out(filename);
    if (!out.is_open()) {
        throw runtime_error("Could not open file for writing: " + filename);
    }
    for (const auto& row : board) {
        for (int val : row) {
            out << val << ' ';
        }
        out << '\n';
    }
}

void SudokuBoard::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        throw runtime_error("Could not open file for reading: " + filename);
    }

    vector<vector<int>> newBoard(9, vector<int>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!(in >> newBoard[i][j])) {
                throw runtime_error("Invalid file format at row " +
                                    to_string(i + 1) + ", col " + to_string(j + 1));
            }

            if (newBoard[i][j] < 0 || newBoard[i][j] > 9) {
                throw runtime_error("Value out of range at row " +
                                    to_string(i + 1) + ", col " + to_string(j + 1));
            }
        }
    }
    board = newBoard;
}
#endif // SUDOKU_BOARD_HPP  


