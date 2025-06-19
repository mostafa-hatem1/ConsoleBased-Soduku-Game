#ifndef SUDOKU_GAME_CPP
#define SUDOKU_GAME_CPP
#include "SudokuGame.hpp"
#include "SudokuSolver.hpp"
#include "SudokuGenerator.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

SudokuGame::SudokuGame() {}

void SudokuGame::start() {
    int choice;
    do {
        board.printBoard();
        printMenu();

        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                enterMove();
                break;
            case 2:
                try{
                    solveAutomatically();
                }catch(const runtime_error& e){
                    cerr << "Error solving board: " << e.what() << '\n';
                }
                
                break;
            case 3: {
                string filename;
                cout << "Enter filename to load from: ";
                cin >> filename;
                handleLoadFromFile(filename);
                break;
            }
            case 4: {
                string filename;
                cout << "Enter filename to save to: ";
                cin >> filename;
                handleSaveToFile(filename);
                break;
            }
            case 5: {
                string difficulty;
                cout << "Choose difficulty: (easy, medium, hard): ";
                cin >> difficulty;
                generateRandomPuzzle(difficulty);
                break;
            }
            case 6:
                cout << "Exiting Sudoku Game...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);
}

void SudokuGame::handleLoadFromFile(const string& filename) {
    try {
        board.loadFromFile(filename);
        cout << "Board successfully loaded from '" << filename << "'.\n";
    } catch (const runtime_error& e) {
        cerr << "Error loading board: " << e.what() << '\n';
        return;
    }
}

void SudokuGame::handleSaveToFile(const string& filename) const {
    try {
        board.saveToFile(filename);
        cout << "Board successfully saved to '" << filename << "'.\n";
    } catch (const runtime_error& e) {
        cerr << "Error saving board: " << e.what() << '\n';
        return;
    }
}

void SudokuGame::printMenu() const {
    cout << "\n1) Enter a move   "
         << "2) Solve automatically   "
         << "3) Load puzzle from file\n"
         << "4) Save current puzzle to file   "
         << "5) Generate random puzzle   "
         << "6) Exit\n";
}

void SudokuGame::enterMove() {
    int row, col, val;

    cout << "Enter row (1-9): ";
    cin >> row;
    if (row < 1 || row > 9){
        cout << "Invalid row input, returning to main menu\n";
        return;
    }

    cout << "Enter column (1-9): ";
    cin >> col;
    if (col < 1 || col > 9){
        cout << "Invalid column input, returning to main menu\n";
        return;
    }

    cout << "Enter value (1-9): ";
    cin >> val;
    if (val < 1 || val > 9){
        cout << "Invalid input, returning to main menu\n";
        return;
    }

    row--; col--; // Convert to 0-based indexing

    if (board.getValue(row, col) != 0) {
        cout << "Cell is already filled. Move not accepted.\n";
        return;
    }

    if (board.isValidMove(row, col, val)) {
        board.setValue(row, col, val);
        cout << "Move accepted.\n";
    } else {
        cout << "Invalid move. Violates Sudoku rules.\n";
    }
}

void SudokuGame::solveAutomatically() {
    SudokuSolver solver(board);
    solver.solve();
}

void SudokuGame::generateRandomPuzzle(string level) {   
    if (level != "easy" && level != "medium" && level != "hard") {
        cout << "Invalid difficulty level. Please choose from easy, medium, or hard.\n";
        return;
    }
    int diff;
    if (level == "easy"){
        diff = 30;
    }else if(level == "medium"){
        diff = 40;
    } else if(level == "hard"){
        diff = 50;
    }
    board = SudokuGenerator::generatePuzzle(diff);
    cout << "Random puzzle generated with difficulty = " << level << "\n";
    return;
}
#endif // SUDOKU_GAME_CPP