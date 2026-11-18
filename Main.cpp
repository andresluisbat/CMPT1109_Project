#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int COL = 30, ROW = 30;

void displayMenu();
void displayBoard(int arr[][COL]);
void loadBoard(int arr[][COL]);
void playOneYear(int arr[][COL], int newArr[][COL]);
void playGame(int arr[][COL], int newArr[][COL]);
void addCells(int arr[][COL], int newArr[][COL]);
void countCells(int arr[][COL]);
void randomBoard(int arr[][COL]);
void bestBoard(int arr[][COL], int newArr[][COL]);
void displayResults(int arr[][COL]);

void displayMenu() {

    cout << "Hello! Welcome to the game of life in CMPT 1109. What would you like to do?"
        << "To display the initial state for the game of life press 1"
        << "To load a new initial state from a CSV file into memory press 2"
        << " To play the game of life with the current initial state press 3"
        << "To seed more cells into the initial state, press 4"
        << "To report summary statistics on all games played press 5"
        << "To randomly play the game multiple times press 6"
        << "To output the best initial board press 7"
        << "To quit the program press 8";
}
int main() {

    int board[COL][ROW];
    int newBoard[COL][ROW];


    int status;

    displayMenu();

    cin >> status;

    switch (status) {
    case 1: displayBoard(board);
        break;

    case 2: loadBoard(board);
        break;
    case 3: playGame(board, newBoard);
        break;
    case 4: addCells(board, newBoard);
        break;
    case 5: displayResults(board);
        break;
    case 6: countCells(board);
        break;
    case 7: cout << "Thanks for playing";
        return 0;
    }

    return 0;
}
