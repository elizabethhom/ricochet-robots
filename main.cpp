  
/*
 * main.cpp
 * 
 * COMP15 - FALL2019
 * Elizabeth Hom (ehom01)
 * Last Modified: October 23, 2019
 * 
 * Purpose: Main driver of the game's two modes.
 */

#include <iostream>
#include <fstream>

#include "Board.h"
#include "Tree.h"

using namespace std;

string getInput(Board *myBoard);
void   getCommands(Board *myBoard);

int main(int argc, char *argv[])
{
    string mode;
    Board *myBoard = new Board();

    if (argc == 2) {
        string boardFile = argv[1];
        myBoard->fillBoard(boardFile);

        mode = getInput(myBoard);
        
        // Automatic mode
        if (mode == "AUTO") {
            Tree myTree(*myBoard);
        } else if (mode == "INTER") {
          // Interactive mode
            myBoard->printBoard();
            getCommands(myBoard);
        }
    } else
        cout << "Usage: ./gorobots [boardFile]" << endl;

    delete myBoard;
    return 0;
}

/*
 *  getInput()
 *
 *  Parameters: Game board
 *  Does:       Prompts user input for robot symbol, starting row/col, and
 *              preferred game mode (AUTO or INTER). Places robot accordingly to
 *              user's input.
 *  Returns:    User's preferred game mode 
 */
string getInput(Board *myBoard)
{
    int row, col;
    char symbol;
    string mode;

    cout << "Welcome to Ricocheting Robots!\n";
    cout << "Enter Robot symbol (1 Char): ";
        cin >> symbol;
    cout << "Enter starting row: ";
        cin >> row;
    cout << "Enter starting col: ";
        cin >> col;
    cout << "Please enter AUTO for automatic solver and INTER for an "
         << "interactive game mode!" << endl;
        cin >> mode;

    myBoard->placeRobot(symbol, row, col);

    return mode;
}

/*
 *  getCommands()
 *
 *  Parameters: Game board
 *  Does:       If user selects interactive mode, continuously prompts user for
 *              directional commands to control robot until user wins or quits
 *  Returns:    NA
 */
void getCommands(Board *myBoard)
{
    char command;

    // Prompts for commands until winning conditions are met or user quits
    do {
        cin >> command;
        if (command == 'q') {
            cout << "move: " << command << "Quitting..." << endl;
            return;
        } else if (command == 'a') {
            cout << "move: " << command << " -> moving west" << endl;
            myBoard->moveWest();
        } else if (command == 's') {
            cout << "move: " << command << " -> moving south" << endl;
            myBoard->moveSouth();
        } else if (command == 'd') {
            cout << "move: " << command << " -> moving east" << endl;
            myBoard->moveEast();
        } else if (command == 'w') {
            cout << "move: " << command << " -> moving north" << endl;
            myBoard->moveNorth();
        } else {
            cout << "move: " << command << "INVALID MOVE" << endl;
        }
    } while (myBoard->getYouWin() == false);
}
