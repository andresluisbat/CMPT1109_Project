#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;
const int COL = 30, ROW = 30;

void displayMenu();
void displayBoard(int arr[][COL]);
void loadBoard(int arr[][COL]);
void playOneYear(int arr[][COL], int newArr[][COL]);
void playGame(int arr[][COL], int newArr[][COL], int& gamesPlayed, int yearCount[], int bestStartBoard[][COL], int& bestAlive);
void addCells(int arr[][COL], int newArr[][COL]);
void randomBoard(int arr[][COL]);
void bestBoard(int bestStartBoard[][COL], int bestAlive);
void displayResults(int arr[][COL], int gamesPlayed, int yearCount[]);
int countLivingCells(int arr[][COL]);
int countDeadCells(int arr[][COL]);

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
            inputFile.clear();
            cout << "Enter name of CSV file: ";
            cin >> fileName;

            inputFile.open(fileName);
        }
    }

    for (int i = 0; i < COL; i++) {

        for (int j = 0; j < ROW; j++) {
         inputFile >> arr[i][j];
            if (arr[i][j] != 0 && arr[i][j] != 1) {
    cout << "Invalid board. Only 0 and 1 are allowed.\n";
    return;
}
            if (j < COL - 1) {
                inputFile.ignore();
            }
            cout << arr[i][j] << ' ';

        }
        cout << endl;
    }


    inputFile.close();

    cout << "Board successfully loaded!!\n";
}

void playOneYear(int arr[][COL], int newArr[][COL]) {
    const int ALIVE_MIN = 2, ALIVE_AND_REPRODUCE = 3;
    for (int i = 0; i < COL; i++) {

        for (int j = 0; j < ROW; j++) {
            int aliveCounter = 0;
            int deadCounter = 0;

            for (int l = -1;l <= 1;l++) {
                for (int m = -1;m <= 1;m++) {
                    if (i + l < 0 || i + l >= COL)
                        continue;
                    if (j + m < 0 || j + m >= COL)
                        continue;
                    if (l == 0 && m == 0)
                        continue;


                    if (arr[i + l][j + m] == 1) {

                        aliveCounter++;

                    }
                }
            }
            if (arr[i][j] == 1) {
                if (aliveCounter == ALIVE_MIN || aliveCounter == ALIVE_AND_REPRODUCE) {
                    newArr[i][j] = 1;
                }
                else newArr[i][j] = 0;

            }
            else {
                if (aliveCounter == ALIVE_AND_REPRODUCE) {
                    newArr[i][j] = 1;
                }

                else {
                    newArr[i][j] = 0;
                }
            }
        }
    }
}

void playGame(int arr[][COL], int newArr[][COL], int& gamesPlayed,
    int yearResults[], int bestStartBoard[][COL], int& bestAlive) {

    // 100-game array limit
    if (gamesPlayed >= 100) {
        cout << "Maximum number of games reached.\n";
        return;
    }
    
    // Save a copy of the starting board
int initialBoard[ROW][COL];
int currentBoard[ROW][COL];

for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
        initialBoard[i][j] = arr[i][j];
        currentBoard[i][j] = arr[i][j];
    }
}

    const int GAME_MAX = 30;
    int yearCount = 0;

    for (int year = 1; year <= GAME_MAX; year++) {

        playOneYear(currentBoard, newArr);

        // Check if the board has stopped changing
        bool unchanged = true;

        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                if (currentBoard[i][j] != newArr[i][j]) {
                    unchanged = false;
                }
            }
        }

        // Copy the new generation into the current board
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
               currentBoard[i][j] = newArr[i][j];
            }
        }

        yearCount++;

        displayBoard(currentBoard);
        cout << endl << endl;

        // Stop if all cells have died
        if (countLivingCells(arr) == 0) {
            cout << "All cells have died. Simulation stopped.\n";
            break;
        }

        // Stop if the board has stopped changing
        if (unchanged) {
            cout << "The board has stopped changing. Simulation stopped.\n";
            break;
        }
    }

    // Save the number of years played
    yearResults[gamesPlayed] = yearCount;

    // Check the final number of living cells
    int aliveAtEnd = countLivingCells(currentBoard);
    
    // Save the best starting board
    if (aliveAtEnd > bestAlive) {
        bestAlive = aliveAtEnd;

        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                bestStartBoard[i][j] = initialBoard[i][j];
            }
        }
    }

    gamesPlayed++;
}


void addCells(int arr[][COL], int newArr[][COL]) {
    string input;
    bool isNumber = false;

    while (!isNumber) {
        cout << "How many cells would you like to add? \n";
        cin >> input;

        isNumber = !input.empty();

        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) {
                isNumber = false;
                break;
            }
        }

        if (isNumber && stoi(input) <= 0) {
            isNumber = false;
            cout << "\nPlease enter a positive number! ";
        }

        if (isNumber && stoi(input) > countDeadCells(arr)) {
            isNumber = false;
            cout << "\nThere are not enough empty cells, enter a smaller number";
        }
        if (!isNumber) {
            cout << "Invalid answer!\n";
        }
    }
    int numberOfCells = stoi(input);
    int cellsAdded = 0;

    cout << "Adding " << numberOfCells << " cells.\n";
    while (cellsAdded < numberOfCells) {
        int randomRow = rand() % ROW;
        int randomCol = rand() % COL;

        if (arr[randomRow][randomCol] == 0) {
            arr[randomRow][randomCol] = 1;
            cellsAdded++;
        }
    }

    displayBoard(arr);
}


void randomBoard(int arr[][COL]) {

}

void bestBoard(int bestStartBoard[][COL], int bestAlive) {
    if (bestAlive == -1) {
        cout << "No games have been played yet.\n";
        return;
    }

    cout << "The best initial board ended with " << bestAlive << " living cells:\n";
    displayBoard(bestStartBoard);
}

void displayResults(int arr[][COL], int gamesPlayed, int yearCount[]) {
    int deadResults = countDeadCells(arr);
    int aliveResults = countLivingCells(arr);

    for (int i = 0; i < gamesPlayed; i++) {
        cout << "\nGame " << i + 1 << endl;
        cout << "Living cells: " << aliveResults << endl;
        cout << "Dead cells: " << deadResults << endl;
        cout << "Years played: " << yearCount[i] << endl;
    }
}

// Counts the number of living cells
int countLivingCells(int arr[][COL])
{
    int total = 0;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (arr[i][j] == 1)
            {
                total++;
            }
        }
    }

    return total;
}

// Counts the number of dead cells
int countDeadCells(int arr[][COL])
{
    int total = 0;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (arr[i][j] == 0)
            {
                total++;
            }
        }
    }

    return total;
}
int getMenuChoice()
{
    int choice;

    cout << "\nEnter your choice: ";
    cin >> choice;

    // Repeat if the user enters invalid input
    while (cin.fail() || choice < 1 || choice > 8)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid choice. Enter a number between 1 and 8: ";
        cin >> choice;
    }

    return choice;
}

int main() {
    const int MAX_SIZE = 100;
    int board[ROW][COL] = { 0 };
    int newBoard[ROW][COL] = { 0 };
    int initialBoard[ROW][COL] = { 0 };
    int gamesPlayed = 0;
    int yearCount[MAX_SIZE];
    int bestStartBoard[ROW][COL] = { 0 };
    int bestAlive = -1;

    srand(static_cast<unsigned int>(time(0)));

    int status;
    do {
        displayMenu();

        status = getMenuChoice();

        switch (status) {
        case 1: displayBoard(board);
            break;

        case 2: loadBoard(board);
            break;

        case 3: playGame(board, newBoard, gamesPlayed, yearCount, bestStartBoard, bestAlive);
            break;

        case 4: addCells(board, newBoard);
            break;

        case 5: displayResults(board, gamesPlayed, yearCount);
            break;

        case 6: randomBoard(board);
            break;

        case 7: bestBoard(bestStartBoard, bestAlive);
            break;

        case 8:cout << "Thanks for playing\n";
            break;

        default: cout << "Invalid selection. Please enter a number between 1 and 8.\n";
            break;
        }

    } while (status != 8);

    return 0;
}
