/********************************************
* Comp 15 - Fall 2019
* Project 1
* ELIZABETH HOM
* 23 OCT 2019
* 
* Board.cpp
*
* Board implementation
*********************************************/

#include <iostream>
#include <fstream>

#include "Board.h"

using namespace std;

// constructor
// parameters: none
// does: none
Board::Board()
{

}

// destructor
// parameters: none
// does: none
Board::~Board()
{

}

// function placeRobot
// parameters: robot's symbol and user-inputted starting row, col
// does: sets robot's symbol, row, and col based on  user-input in main. then
//       places robot symbol in the specified row, col in the board array
void Board::placeRobot(char symbol, int row, int col)
{
    myRobot.symbol = symbol;
    myRobot.row = row;
    myRobot.col = col;
    myRobot.indexRow = row * 2 - 2;
    myRobot.indexCol = col * 2 - 2;

    myBoard[myRobot.indexRow][myRobot.indexCol] = symbol;
}

// function fillBoard
// parameters: board filename
// does: reads in the board from the filename provided on the command line
//       and saves the file's board characters into the 2d board array
void Board::fillBoard(string filename)
{
    char cell;

    ifstream input;
    input.open(filename);

    for(int tempRow = 0; tempRow < 15; tempRow++) {
        for(int tempCol = 0; tempCol < 15; tempCol++) {
            input >> cell;
            myBoard[tempRow][tempCol] = cell;
        }
    }

    input.close();
}

// function printBoard
// parameters: none
// does: prints the current state of the game board
void Board::printBoard()
{
    cout << endl;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if (myBoard[i][j] == 'O')
                cout << " ";
            else
                cout << myBoard[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// function moveEast
// parameters: none
// does: moves the robot as far East as possible (until it hits a wall or
//       the edge). then, prints resulting board to the terminal as well as a
//       winning message if the user has won (lands on the target).
void Board::moveEast()
{   
    // gets new col of robot moving as far east as possible
    int newCol = mvEGetPos(myRobot.indexRow, myRobot.indexCol);
    if (myBoard[myRobot.indexRow][newCol] == '*')
        youWin = true;   // if find *, winning condition met

    myBoard[myRobot.indexRow][myRobot.indexCol] = 'X';   // swap board
    myBoard[myRobot.indexRow][newCol] = myRobot.symbol;  // characters

    myRobot.indexCol = newCol;          // update robot col index and col #
    myRobot.col = (newCol + 2) / 2;

    if (youWin == false)
        printBoard();
    else if (youWin == true) {
        printBoard();
        cout << "Congratulations!! You Win!!!!" << endl;
    }
}

// function moveWest
// parameters: none
// does: moves the robot as far West as possible (until it hits a wall or
//       the edge). then, prints resulting board to the terminal as well as a
//       winning message if the user has won (lands on the target).
void Board::moveWest()
{
    int newCol = mvWGetPos(myRobot.indexRow, myRobot.indexCol);
    if (myBoard[myRobot.indexRow][newCol] == '*')
        youWin = true;
    myBoard[myRobot.indexRow][myRobot.indexCol] = 'X';
    myBoard[myRobot.indexRow][newCol] = myRobot.symbol;

    myRobot.indexCol = newCol;
    myRobot.col = (newCol + 2) / 2;

    if (youWin == false)
        printBoard();
    else if (youWin == true) {
        printBoard();
        cout << "Congratulations!! You Win!!!!" << endl;
    }
}

// function moveSouth
// parameters: none
// does: moves the robot as far South as possible (until it hits a wall or
//       the edge). then, prints resulting board to the terminal as well as a
//       winning message if the user has won (lands on the target).
void Board::moveSouth()
{
    int newRow = mvSGetPos(myRobot.indexRow, myRobot.indexCol);
    if (myBoard[newRow][myRobot.indexCol] == '*')
        youWin = true;
    myBoard[myRobot.indexRow][myRobot.indexCol] = 'X';
    myBoard[newRow][myRobot.indexCol] = myRobot.symbol;

    myRobot.indexRow = newRow;
    myRobot.row = (newRow + 2) / 2;

    if (youWin == false)
        printBoard();
    else if (youWin == true) {
        printBoard();
        cout << "Congratulations!! You Win!!!!" << endl;
    }
}

// function moveNorth
// parameters: none
// does: moves the robot as far North as possible (until it hits a wall or
//       the edge). then, prints resulting board to the terminal as well as a
//       winning message if the user has won (lands on the target).
void Board::moveNorth()
{
    int newRow = mvNGetPos(myRobot.indexRow, myRobot.indexCol);
    if (myBoard[newRow][myRobot.indexCol] == '*')
        youWin = true;
    myBoard[myRobot.indexRow][myRobot.indexCol] = 'X';
    myBoard[newRow][myRobot.indexCol] = myRobot.symbol;

    myRobot.indexRow = newRow;
    myRobot.row = (newRow + 2) / 2;

    if (youWin == false)
        printBoard();
    else if (youWin == true) {
        printBoard();
        cout << "Congratulations!! You Win!!!!" << endl;
    }
}

// function youWin
// parameters: none
// returns: returns true if the user has won, false if the user still has yet
//          to win
// does: checks if the user has won (robot lands on the target), returns true
//       or false accordingly.
bool Board::getYouWin()
{
    if (youWin == true)
        return true;
    else
        return false;
}

// function canMoveNorth
// parameters: row and col index of robot
// returns: true if the robot, at its current position, can move north at all.
//          returns false if robot cannot move north (against a '- wall or
//          board north edge)
// does: checks if the robot can move north
bool Board::canMoveNorth(int rowIndex, int colIndex) // parameters are robot index
{
    if (myBoard[rowIndex - 1][colIndex] == '-' or rowIndex == 0)
        return false;
    else
        return true;
}

// function canMoveEast
// parameters: row and col index of robot
// returns: true if the robot, at its current position, can move east at all.
//          returns false if robot cannot move east (against a '|' wall or
//          board east edge)
// does: checks if the robot can move east
bool Board::canMoveEast(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex][colIndex + 1] == '|' or colIndex == 14)
        return false;
    else
        return true;
}


// function canMoveSouth
// parameters: row and col index of robot
// returns: true if the robot, at its current position, can move south at all.
//          returns false if robot cannot move south (against a '-' wall or
//          board south edge)
// does: checks if the robot can move south
bool Board::canMoveSouth(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex + 1][colIndex] == '-' or rowIndex == 14)
        return false;
    else
        return true;
}

// function canMoveWest
// parameters: row and col index of robot
// returns: true if the robot, at its current position, can move west at all.
//          returns false if robot cannot move west (against a '|' wall or
//          board west edge)
// does: checks if the robot can move west
bool Board::canMoveWest(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex][colIndex - 1] == '|' or colIndex == 0)
        return false;
    else
        return true;
}

// function mvEGetpos
// parameters: row and col index of robot
// returns: the new col of the robot had it moved as far east as possible
//          from the row and col position of the robot passed in
// does: if the robot moves east, the row stays the same, but the robot will
//       get a new column. returns the value of the new column had the robot
//       moved as far east as possible
int Board::mvEGetPos(int rowIndex, int colIndex)
{
   int tempCol = colIndex;

   while(tempCol < 14 and myBoard[rowIndex][colIndex + 1] != '|') {
        if(myBoard[rowIndex][colIndex + 1] == 'O') {
            colIndex = colIndex + 2;
            tempCol = tempCol + 2;
        }
   }

   return colIndex;
}

// function mvSGetpos
// parameters: row and col index of robot
// returns: the new row of the robot had it moved as far south as possible
//          from the row and col position of the robot passed in
// does: if the robot moves south, the col stays the same, but the robot will
//       get a new row. returns the value of the new row had the robot
//       moved as far south as possible
int Board::mvSGetPos(int rowIndex, int colIndex)
{
    int tempRow = rowIndex;

    while(tempRow < 14 and myBoard[rowIndex + 1][colIndex] != '-') {
        if (myBoard[rowIndex + 1][colIndex] == 'O') {
            rowIndex = rowIndex + 2;
            tempRow = tempRow + 2;
        }
    }

    return rowIndex;
}

// function mvWGetpos
// parameters: row and col index of robot
// returns: the new col of the robot had it moved as far west as possible
//          from the row and col position of the robot passed in
// does: if the robot moves west, the row stays the same, but the robot will
//       get a new column. returns the value of the new column had the robot
//       moved as far west as possible
int Board::mvWGetPos(int rowIndex, int colIndex)
{
    int tempCol = colIndex;

    while(tempCol > 0 and myBoard[rowIndex][colIndex - 1] != '|') {
        if(myBoard[rowIndex][colIndex - 1] == 'O') {
            colIndex = colIndex - 2;
            tempCol = tempCol - 2;
        }
    }

    return colIndex;
}

// function mvSGetpos
// parameters: row and col index of robot
// returns: the new row of the robot had it moved as far north as possible
//          from the row and col position of the robot passed in
// does: if the robot moves north, the col stays the same, but the robot will
//       get a new row. returns the value of the new row had the robot
//       moved as far north as possible
int Board::mvNGetPos(int rowIndex, int colIndex)
{
    int tempRow = rowIndex;

    while(tempRow > 0 and myBoard[rowIndex - 1][colIndex] != '-') {
        if(myBoard[rowIndex - 1][colIndex] == 'O') {
            rowIndex = rowIndex - 2;
            tempRow = tempRow - 2;
        }
    }

    return rowIndex;
}

// function getRobotRowInd
// parameters: none
// returns: the current row position of the robot
// does: returns the current row of the robot
int Board::getRobotRowInd()
{
    return myRobot.indexRow;
}

// function getRobotColInd
// parameters: none
// returns: the current col position of the robot
// does: returns the current col of the robot
int Board::getRobotColInd()
{
    return myRobot.indexCol;
}

// function getBoardChar
// parameters: row and col index
// returns: the board character at the specified row and col index
// does: returns the character in the board at the passed in row and col index
char Board::getBoardChar(int rowInd, int colInd)
{
    return myBoard[rowInd][colInd];
}
