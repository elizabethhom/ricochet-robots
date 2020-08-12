/*
 * Board.cpp
 * 
 * COMP15 - FALL2019
 * Elizabeth Hom (ehom01)
 * Last Modified: October 23, 2019
 * 
 * Purpose: Implementation of the Board class. Oversees game board, its
 *          elements, and relevant functions, including moving robot,
 *          printing board, checking win conditions
 */

#include <iostream>
#include <fstream>

#include "Board.h"

using namespace std;

/*
 * Constructor
 */
Board::Board()
{
    
}

/*
 * Destructor
 */
Board::~Board()
{

}

/*
 * placeRobot
 *
 * Parameters: Robot's user-inputted symbol, starting row, starting col
 * Returns:    NA
 * Does:       Sets robot's symbol, row, col. Places robot symbol in specified
 *             coordinates in board
 */
void Board::placeRobot(char symbol, int row, int col)
{
    myRobot.symbol = symbol;
    myRobot.row = row;
    myRobot.col = col;
    myRobot.indexRow = row * 2 - 2;
    myRobot.indexCol = col * 2 - 2;

    myBoard[myRobot.indexRow][myRobot.indexCol] = symbol;
}

/*
 * fillBoard
 *
 * Parameters: Board file name
 * Returns:    NA
 * Does:       Reads and populates board from file
 */
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

/*
 * printBoard
 *
 * Parameters: NA
 * Returns:    NA
 * Does:       Prints current state of game board
 */
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

/*
 * moveEast
 *
 * Parameters: NA
 * Returns:    NA
 * Does:       Moves robot as far East as possible (until hits wall or edge).
 *             Prints resulting game board to terminal and winning message, if
 *             applicable.
 */
void Board::moveEast()
{   
    // Gets new col of robot moving as far East as possible
    int newCol = mvEGetPos(myRobot.indexRow, myRobot.indexCol);
    if (myBoard[myRobot.indexRow][newCol] == '*')
        youWin = true;

    // Swap board characters
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

/*
 * moveWest
 *
 * Parameters: NA
 * Returns:    NA
 * Does:       Moves robot as far West as possible (until hits wall or edge).
 *             Prints resulting game board to terminal and winning message, if
 *             applicable.
 */
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

/*
 * moveSouth
 *
 * Parameters: NA
 * Returns:    NA
 * Does:       Moves robot as far South as possible (until hits wall or edge).
 *             Prints resulting game board to terminal and winning message, if
 *             applicable.
 */
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

/*
 * moveNorth
 *
 * Parameters: NA
 * Returns:    NA
 * Does:       Moves robot as far North as possible (until hits wall or edge).
 *             Prints resulting game board to terminal and winning message, if
 *             applicable.
 */
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

/*
 * youWin
 *
 * Parameters: NA
 * Returns:    True if user has met winning conditions, otherwise false
 * Does:       Checks and returns true if user has won (robot lands on target)
 */
bool Board::getYouWin()
{
    if (youWin == true)
        return true;
    else
        return false;
}

/*
 * canMoveNorth
 *
 * Parameters: Robot's row and col indices
 * Returns:    True if robot, at its current position, can move North. Otherwise,
 *             false
 * Does:       Checks whether robot can move North
 */
bool Board::canMoveNorth(int rowIndex, int colIndex) // parameters are robot index
{
    if (myBoard[rowIndex - 1][colIndex] == '-' or rowIndex == 0)
        return false;
    else
        return true;
}

/*
 * canMoveEast
 *
 * Parameters: Robot's row and col indices
 * Returns:    True if robot, at its current position, can move East. Otherwise,
 *             false
 * Does:       Checks whether robot can move East
 */
bool Board::canMoveEast(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex][colIndex + 1] == '|' or colIndex == 14)
        return false;
    else
        return true;
}


/*
 * canMoveSouth
 *
 * Parameters: Robot's row and col indices
 * Returns:    True if robot, at its current position, can move South. Otherwise,
 *             false
 * Does:       Checks whether robot can move South
 */
bool Board::canMoveSouth(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex + 1][colIndex] == '-' or rowIndex == 14)
        return false;
    else
        return true;
}

/*
 * canMoveWest
 *
 * Parameters: Robot's row and col indices
 * Returns:    True if robot, at its current position, can move West. Otherwise,
 *             false
 * Does:       Checks whether robot can move West
 */
bool Board::canMoveWest(int rowIndex, int colIndex)
{
    if (myBoard[rowIndex][colIndex - 1] == '|' or colIndex == 0)
        return false;
    else
        return true;
}

/*
 * mvEGetPos
 *
 * Parameters: Robot's row and col indices
 * Returns:    New col of robot
 * Does:       Returns the new column value had the robot moved as far East as
 *             possible from the passed in row and column indices
 */
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

/*
 * mvSGetPos
 *
 * Parameters: Robot's row and col indices
 * Returns:    New col of robot
 * Does:       Returns the new column value had the robot moved as far South as
 *             possible from the passed in row and column indices
 */
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

/*
 * mvWGetPos
 *
 * Parameters: Robot's row and col indices
 * Returns:    New col of robot
 * Does:       Returns the new column value had the robot moved as far West as
 *             possible from the passed in row and column indices
 */
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

/*
 * mvNGetPos
 *
 * Parameters: Robot's row and col indices
 * Returns:    New col of robot
 * Does:       Returns the new column value had the robot moved as far North as
 *             possible from the passed in row and column indices
 */
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

/*
 * getRobotRowInd
 *
 * Parameters: NA
 * Does:       Returns current row of robot
 */
int Board::getRobotRowInd()
{
    return myRobot.indexRow;
}

/*
 * getRobotColInd
 *
 * Parameters: NA
 * Does:       Returns current col of robot
 */
int Board::getRobotColInd()
{
    return myRobot.indexCol;
}

// function getBoardChar
// parameters: row and col index
// returns: the board character at the specified row and col index
// does: returns the character in the board at the passed in row and col index

/*
 * getBoardChar
 *
 * Parameters: Row and col indices
 * Does:       Returns board character at specified row and col indices
 */
char Board::getBoardChar(int rowInd, int colInd)
{
    return myBoard[rowInd][colInd];
}
