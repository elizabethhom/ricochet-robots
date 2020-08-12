/*
 * Board.h
 * 
 * COMP15 - FALL2019
 * Elizabeth Hom (ehom01)
 * Last Modified: October 23, 2019
 * 
 * Purpose: Interface for Board class.
 */

#include <iostream>

using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

/*
 * Robot
 *
 * Describes the robot by its symbol and row/col indices.
 */
struct Robot {
    char symbol;
    int row, col, indexRow, indexCol;
};

class Board
{
    public:
    
        Board();
        ~Board();

        // Places robot symbol at row/col
        void placeRobot(char symbol, int row, int col);

        // Gets robot's current row/col
        int getRobotRowInd();
        int getRobotColInd();

        // Gets board character at row/col
        char getBoardChar(int rowInd, int colInd);

        // Reads and populates board
        void fillBoard(string filename);

        // Prints board 
        void printBoard();

        // Moves robot as far as possible in respective direction
        void moveEast();
        void moveWest();
        void moveSouth();
        void moveNorth();

        // Returns true if win conditions met
        bool getYouWin();

        // Returns true if robot can move in respective direction
        bool canMoveNorth(int rowIndex, int colIndex);
        bool canMoveEast(int rowIndex, int colIndex);
        bool canMoveSouth(int rowIndex, int colIndex);
        bool canMoveWest(int rowIndex, int colIndex);

        // Returns robot row/col if can move in respective direction
        int mvEGetPos(int rowIndex, int colIndex);
        int mvSGetPos(int rowIndex, int colIndex);
        int mvWGetPos(int rowIndex, int colIndex);
        int mvNGetPos(int rowIndex, int colIndex);

    private:
        Robot myRobot;
        char myBoard[15][15];
        bool youWin = false;
};

#endif
