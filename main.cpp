/********************************************
* Comp 15 - Fall 2019
* Project 1
* ELIZABETH HOM
* 23 OCT 2019
* 
* main.cpp
*
* Interactive main for running gorobots
*********************************************/

#include <iostream>
#include <fstream>

#include "Board.h"
#include "Tree.h"

using namespace std;

string getInput(Board *myBoard);
void getCommands(Board *myBoard);

int main(int argc, char *argv[])
{
    string mode;
    Board *myBoard = new Board();

    if (argc == 2) {
        string boardFile = argv[1];
        myBoard->fillBoard(boardFile);

        mode = getInput(myBoard);
        if (mode == "AUTO") {           // automatic mode
            Tree myTree(*myBoard);
        } else if (mode == "INTER") {   // interactive mode
            myBoard->printBoard();
            getCommands(myBoard);
        }
    } else
        cout << "Usage: ./gorobots [board input file]" << endl;

    delete myBoard;
    return 0;
}

// function getInput
// parameters: the game board
// returns: the game mode the user would like to play (string)
// does: prints messages to terminal and gets user input for robot symbol, row,
//       col, and their preferred game mode (AUTO or INTER). then places robot
//       onto board using user's specified location and symbol
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

// function getCommands
// parameters: the game board
// returns: none
// does: if the user selects interactive mode, getCommands contiuously gets
//       commands to control the robot from the user until the user wins or the
//       user quits
void getCommands(Board *myBoard)
{
    char command;

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
    } while (myBoard->getYouWin() == false);    // gets commands until winning
}                                               // conditions are met
