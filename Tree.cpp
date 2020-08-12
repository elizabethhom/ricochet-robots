  
/*
 * Tree.cpp
 * 
 * COMP15 - FALL2019
 * Elizabeth Hom (ehom01)
 * Last Modified: October 23, 2019
 * 
 * Purpose: Implementation of the Tree class. Oversees building of tree that
 *          models all possible paths of robot from its starting position,
 *          and automated searching tree for solution.
 */

#include <iostream>

#include "Tree.h"
#include "Board.h"

using namespace std;

/*
 * Constructor
 *
 * Parameters: Game board
 * Does:       Makes tree of possible moves robot can take from starting position
 *             and attempts to auto-solve game
 */
Tree::Tree(Board inputBoard)
{
    myBoard = inputBoard;
    root = makeTree(0,"", myBoard.getRobotRowInd(), myBoard.getRobotColInd());

    if (not autoSolve('*'))
        cout << "No solution" << endl;
}

/*
 * Destructor
 *
 * Does:       Destroys associated memory of tree
 */
Tree::~Tree()
{
    destroy(root);
}

/*
 * destroy
 *
 * Parameters: A tree Node
 * Returns:    NA
 * Does:       Recursively deletes tree in all directions
 */
void Tree::destroy(Node *curr)
{
    // Deletes children
    if (curr->north != nullptr)
        destroy(curr->north);
    if (curr->east != nullptr)
        destroy(curr->east);
    if (curr->south != nullptr)
        destroy(curr->south);
    if (curr->west != nullptr)
        destroy(curr->west);

    // Deletes root
    delete curr;
}

/*
 * makeTree
 *
 * Parameters: Current tree height, path, robot row/col indices
 * Returns:    Current pointer to tree node
 * Does:       Recursively creates tree of possible paths robot can take from
 *             starting position. With each recursive call, if robot can move in
 *             a direction (N, S, W, E), adds Node that contains height of tree,
 *             current path, and robot's row/col indices
 */
Tree::Node* Tree::makeTree(int height, string currPath, int rowInd, int colInd)
{
    // If seven moves have passed, return
    if (height == maxLength + 1)
        return nullptr;

    Node *curr = new Node;
    curr->row = rowInd;
    curr->col = colInd;
    curr->boardChar = myBoard.getBoardChar(rowInd, colInd);

    // Recursive call in all directions
    if (myBoard.canMoveNorth(rowInd, colInd)) {
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

    // Set path to current path
    curr->path  = currPath;
    return curr;
}

/*
 * autoSolve (public)
 *
 * Parameters: Target
 * Returns:    True if game is solveable in < 7 moves, otherwise false
 * Does:       Calls private helper autoSolve, which attempts to find solution
 *             to game
 */
bool Tree::autoSolve(char target)
{
    return autoSolve(target, root);
}

/*
 * autoSolve (private)
 *
 * Parameters: Target, poitner to starting Node (tree root)
 * Returns:    True if game is solveable, otherwise false
 * Does:       Searches for solution by searching tree to find target
 */
bool Tree::autoSolve(char target, Node *curr)
{
    bool isNorth = false,
         isEast  = false,
         isSouth = false,
         isWest  = false;

    // If reached nullptr, return
    if (curr == nullptr)
        return false;

    // If target found, you win!
    if (curr->boardChar == target) {
        cout << curr->path << "Found the target!" << endl;
        return true;
    }

    // Searches tree if robot can move in respective direction
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

/*
 * copy
 *
 * Parameters: a Node
 * Returns:    Pointer to root of copied tree
 * Does:       Copies tree
 */
Tree::Node *Tree::copy(Node *toCopy) {
    if (toCopy == nullptr)
            return nullptr;

    Node *curr = new Node;

    // Copies data from original node
    curr->path   = toCopy->path;

    // Deep copies children
    curr->north   = copy(toCopy->north);
    curr->east = copy(toCopy->east);
    curr->south = copy(toCopy->south);
    curr->west = copy(toCopy->west);

    return curr;
}

/*
 * Copy Constructor
 */
Tree::Tree(const Tree &oldTree)
{
    root = copy(oldTree.root);
}

/*
 * Assignment Operator
 */
Tree &Tree::operator=(const Tree &toCopy){
    // Checks for self-assignment    
    if (this == &toCopy)    // check for self assignment
        return *this;

    // Deletes dynamic memory in current object
    destroy(root);
        
    // Performs deep copy
    root = copy(toCopy.root);

    return *this;
}
