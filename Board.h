/********************************************
* Comp 15 - Fall 2019
* Project 1
* ELIZABETH HOM
* 23 OCT 2019
* 
* Board interface
* Class interface for the Board class
*********************************************/

#include <iostream>

using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

struct Robot {
    char symbol;
    int row, col, indexRow, indexCol;
};

class Board
{
    public:
        // default constructor
        Board();

        // destructor
        ~Board();

        // places robot symbol in the specified row and col
        void placeRobot(char symbol, int row, int col);

        // gets robot's current row, col index
        int getRobotRowInd();
        int getRobotColInd();

        // gets board character at specified row, col index
        char getBoardChar(int rowInd, int colInd);

        // reads in board and saves into board array
        void fillBoard(string filename);

        // prints current state of board
        void printBoard();

        // moves robot as far as possible in specified direction
        void moveEast();
        void moveWest();
        void moveSouth();
        void moveNorth();

        // returns true if conditions to win are met
        bool getYouWin();

        // returns true if robot can move in specified direction
        bool canMoveNorth(int rowIndex, int colIndex);
        bool canMoveEast(int rowIndex, int colIndex);
        bool canMoveSouth(int rowIndex, int colIndex);
        bool canMoveWest(int rowIndex, int colIndex);

        // returns row or col of robot if it moved in specified direction
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
