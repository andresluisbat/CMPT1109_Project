#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
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
    
    cout << "Hello! Welcome to the game of life in CMPT 1109. What would you like to do?\n"
        << "To display the initial state for the game of life press 1\n"
        << "To load a new initial state from a CSV file into memory press 2\n"
        << "To play the game of life with the current initial state press 3\n"
        << "To seed more cells into the initial state, press 4\n"
        << "To report summary statistics on all games played press 5\n"
        << "To randomly play the game multiple times press 6\n"
        << "To output the best initial board press 7\n"
        << "To quit the program press 8\n";
}

void displayBoard(int arr[][COL]) {
    for (int i = 0; i < ROW; i++) {

        for (int j = 0; j < COL; j++) {

            cout << arr[i][j] << " ";

        }
        cout << endl;
    }
 
}
void loadBoard(int arr[][COL]) {

     ifstream inputFile;

 string fileName;

 cout << "Enter name of CSV file: ";
 cin >> fileName;

 inputFile.open(fileName);

 if (!inputFile) {
     cout << "Error opening file, Please Reenter the file\n";
     while (!inputFile) {
         cout << "Enter name of CSV file: ";
         cin >> fileName;

         inputFile.open(fileName);
     }
 }

 for (int i = 0; i < COL; i++) {

     for (int j = 0; j < ROW; j++) {

         inputFile >> arr[i][j];
         if (j < COL -1) {
             inputFile.ignore();
         }
         cout << arr[i][j];
         
     }
     cout << endl;
 }


    inputFile.close();

    cout << "Board successfully loaded!!\n";
}

void playOneYear(int arr[][COL], int newArr[][COL]) {

    for (int i = 0; i < COL; i++) {

        for (int j = 0; j < ROW; j++) {

            int neighbours;



        }
    }

}

void playGame(int arr[][COL], int newArr[][COL]) {

}

void addCells(int arr[][COL], int newArr[][COL]) {

}

void countCells(int arr[][COL]) {

}

void randomBoard(int arr[][COL]) {

}

void bestBoard(int arr[][COL], int newArr[][COL]) {

}

void displayResults(int arr[][COL]) {

}


int main() {

    int board[ROW][COL] = { 0 };
    int newBoard[ROW][COL] = { 0 };

    srand(time(0));

    int status;
    do {
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

        case 6: randomBoard(board);
            break;

        case 7:  bestBoard(board, newBoard);
            break;

        case 8:cout << "Thanks for playing\n";
            break;

        default: cout << "Invalid selection. Please enter a number between 1 and 8.\n";
            break;
        }

    } while (status != 8);

    return 0;
}
