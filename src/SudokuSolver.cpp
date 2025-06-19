#ifndef SUDOKU_SOLVER_CPP
#define SUDOKU_SOLVER_CPP

#include "SudokuSolver.hpp"

SudokuSolver::SudokuSolver(SudokuBoard& b) : board(b) {}

void SudokuSolver::solve() {
    if(!(solveRecursive(0,0))){
        throw runtime_error("No solution found");
    }else{
        return;    // Start from the top-left cell
    }   
}

bool SudokuSolver::solveRecursive(int row, int col) {
    if (row == 9) return true;  // Reached end of board = puzzle solved

    // Move to next row if at the end of this one
    if (col == 9) return solveRecursive(row + 1, 0);

    // If the cell is already filled, skip it
    if (board.getValue(row, col) != 0)
        return solveRecursive(row, col + 1);

    // Try placing values 1 through 9
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(row, col, num)) {
            board.setValue(row, col, num);  // Place number

            if (solveRecursive(row, col + 1))  // Recurse to next cell
                return true;

            board.setValue(row, col, 0);  // Backtrack (reset to 0)
        }
    }

    return false;  // No valid number found for this cell
}

bool SudokuSolver::isSafe(int row, int col, int value) const {
    return board.isValidMove(row, col, value);
}
#endif // SUDOKU_SOLVER_CPP