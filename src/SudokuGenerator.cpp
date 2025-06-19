#ifndef SUDOKU_GENERATOR_CPP
#define SUDOKU_GENERATOR_CPP

#include "SudokuGenerator.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;


static random_device rd;
static mt19937 rng(rd());


static bool fillBoardRandomly(SudokuBoard& board, int row = 0, int col = 0) {
    if (row == 9) return true;               
    if (col == 9) return fillBoardRandomly(board, row + 1, 0);  

    if (board.getValue(row, col) != 0)       
        return fillBoardRandomly(board, row, col + 1);

    vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    shuffle(numbers.begin(), numbers.end(), rng); 

    for (int num : numbers) {
        if (board.isValidMove(row, col, num)) {
            board.setValue(row, col, num);
            if (fillBoardRandomly(board, row, col + 1))
                return true;
            board.setValue(row, col, 0);  
        }
    }
    return false;  
}

SudokuBoard SudokuGenerator::generatePuzzle(int level) {
    SudokuBoard board;
    
    fillBoardRandomly(board);

    vector<pair<int, int>> cells;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            cells.emplace_back(i, j);

    shuffle(cells.begin(), cells.end(), rng);

    int removed = 0;
    for (const auto& [row, col] : cells) {
        int backup = board.getValue(row, col);
        board.setValue(row, col, 0);

        ++removed;
        if (removed >= level)
            break;
    }

    return board;
}



#endif // SUDOKU_GENERATOR_CPP