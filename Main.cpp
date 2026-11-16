#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void optionOne(int arr[][]);
void optionTwo(int arr[][]);
void optionThree();
void optionFour();
void optionFive();

int main() {
    const int COL = 30, ROW = 30;

    int status;
    int currentArray[COL][COL];
    cout << "Hello! Welcome to the game of life in CMPT 1109. What would you like to do?"
        << "To display the initial state for the game of life press 1"
        << "To load a new initial state from a CSV file into memory press 2"
        << " To play the game of life with the current initial state press 3"
        << "To seed more cells into the initial state, press 4"
        << "To report summary statistics on all games played press 5"
        << "To randomly play the game multiple times press 6"
        << "To output the best initial board press 7"
        << "To quit the program press 8";
    cin >> status;

    switch (status) {
    case 1: optionOne(currentArray[COL][COL]);
        break;

    case 2: optionTwo(currentArray[COL][COL]);
        break;
    case 3: optionThree(currentArray[COL][COL]);
        break;
    case 4: optionFour(currentArray[COL][COL]);
        break;
    case 5: optionFive(currentArray[COL][COL]);
        break;
    }

    return 0;
}
