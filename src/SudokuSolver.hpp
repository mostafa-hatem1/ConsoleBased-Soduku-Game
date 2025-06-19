#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include "SudokuBoard.hpp"
using namespace std;

class SudokuSolver {
public:
    SudokuSolver(SudokuBoard& board);
    void solve();

private:
    SudokuBoard& board;
    bool solveRecursive(int row, int col);
    bool isSafe(int row, int col, int value) const;
};



#endif // SUDOKU_SOLVER_HPP