/********************************************
* Comp 15 - Fall 2019
* Project 1
* ELIZABETH HOM
* 23 OCT 2019
* 
* Tree.cpp
*
* Tree implementation
*********************************************/

#include <iostream>

#include "Tree.h"
#include "Board.h"

using namespace std;

// constructor
// parameters: game board
// does: passes in the game board from Board class, makes the tree of possible
//       moves the robot can take from starting position, solves game
Tree::Tree(Board inputBoard)
{
    myBoard = inputBoard;
    root = makeTree(0,"", myBoard.getRobotRowInd(), myBoard.getRobotColInd());

    if (not autoSolve('*'))
        cout << "No solution" << endl;
}

// destructor
// parameters: none
// does: calls destroy(), deletes the tree
Tree::~Tree()
{
    destroy(root);
}

// function destroy
// parameters: a Node
// does: deletes the tree
void Tree::destroy(Node *curr)
{
    if (curr->north != nullptr)     // deletes the children
        destroy(curr->north);
    if (curr->east != nullptr)
        destroy(curr->east);
    if (curr->south != nullptr)
        destroy(curr->south);
    if (curr->west != nullptr)
        destroy(curr->west);

    delete curr;                    // deletes the root
}

// function makeTree
// parameters: current height, current path, row, col index of robot
// does: recursively creates the tree of possible paths the robot could take
//       from its starting position. with each recursive call, if the robot can
//       move in a direction (N, S, W, E), adds a node that contains the height
//       of tree and current path at that point, and row, col index of robot
Tree::Node* Tree::makeTree(int height, string currPath, int rowInd, int colInd)
{
    if (height == maxLength + 1)    // if seven moves have passed, return
        return nullptr;

    Node *curr = new Node;
    curr->row = rowInd;
    curr->col = colInd;
    curr->boardChar = myBoard.getBoardChar(rowInd, colInd);

    if (myBoard.canMoveNorth(rowInd, colInd)) {              // recursive call
        curr->north = makeTree(height + 1, currPath + "N -> ",
                      myBoard.mvNGetPos(rowInd, colInd), colInd);
    } else
        curr->north = nullptr;
    if (myBoard.canMoveEast(rowInd, colInd)) {
        curr->east  = makeTree(height + 1, currPath + "E -> ", rowInd,
                      myBoard.mvEGetPos(rowInd, colInd));
    } else
        curr->east = nullptr;
    if (myBoard.canMoveSouth(rowInd, colInd)) {
        curr->south = makeTree(height + 1, currPath + "S -> ",
                      myBoard.mvSGetPos(rowInd, colInd), colInd);
    } else
        curr->south = nullptr;
    if (myBoard.canMoveWest(rowInd, colInd)) {
        curr->west  = makeTree(height + 1, currPath + "W -> ", rowInd,
                      myBoard.mvWGetPos(rowInd, colInd));
    } else
        curr->west = nullptr;

    curr->path  = currPath;     // set path to currPath
    return curr;
}

// function autoSolve
// parameters: the target
// does: calls private function autoSolve (attempts to find solution to game)
bool Tree::autoSolve(char target)
{
    return autoSolve(target, root);
}

// function autoSolve
// parameters: target, starting Node (the root of tree)
// does: searches for a solution to the game by searching the tree to find
//       the target
bool Tree::autoSolve(char target, Node *curr)
{
    bool isNorth = false, isEast = false, isSouth = false, isWest = false;

    if (curr == nullptr)    // if find nullptr, return
        return false;

    if (curr->boardChar == target) {    // if find target, you win!
        cout << curr->path << "Found the target!" << endl;
        return true;
    }

    // searches tree depending on if robot can move in each direction
    if (myBoard.canMoveNorth(curr->row, curr->col))
        isNorth = autoSolve(target, curr->north);
        if (isNorth)
            return isNorth;
    if (myBoard.canMoveEast(curr->row, curr->col))
        isEast = autoSolve(target, curr->east);
        if (isEast)
            return isEast;
    if (myBoard.canMoveSouth(curr->row, curr->col))
        isSouth = autoSolve(target, curr->south);
        if (isSouth)
            return isSouth;
    if (myBoard.canMoveWest(curr->row, curr->col))
        isWest = autoSolve(target, curr->west);
        if (isWest)
            return isWest;

    return false;
}


// function copy
// parameters: a Node
// does: copies the tree
Tree::Node *Tree::copy(Node *toCopy) {
        if (toCopy == nullptr)
            return nullptr;

        Node *curr = new Node;

        curr->path   = toCopy->path;    // copy data from original node

        curr->north   = copy(toCopy->north);    // deep copies children
        curr->east = copy(toCopy->east);
        curr->south = copy(toCopy->south);
        curr->west = copy(toCopy->west);
        return curr;
}

// copy constructor
Tree::Tree(const Tree &oldTree)
{
    root = copy(oldTree.root);
}

// assignment operator
Tree &Tree::operator=(const Tree &toCopy){
        if (this == &toCopy)    // check for self assignment
                return *this;

        destroy(root);  // deletes dynamic memory in current obj
        
        root = copy(toCopy.root);   // deep copies

        return *this;
}
