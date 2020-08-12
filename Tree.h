/*
 * Tree.h
 * 
 * COMP15 - FALL2019
 * Elizabeth Hom (ehom01)
 * Last Modified: October 23, 2019
 * 
 * Purpose: Interface for Tree class.
 */

#include <iostream>

#include "Board.h"

using namespace std;

#ifndef TREE_H_
#define TREE_H_

class Tree
{
    public:

        Tree(Board inputBoard);
        ~Tree();
        Tree(const Tree &t);
        Tree& operator=(const Tree &t);

        // Searches for game solution in automatic mode
        bool autoSolve(char target);

    private:

        /*
        * Node
        *
        * Describes a node in the tree by the robot's possible path combinations,
        * row/col indices, character located there, and pointers to nodes in all
        * four directions.
        */
        struct Node {
            string path;
            int row, col;
            char boardChar;
            Node *north, *east, *south, *west;
        };

        // Pointer to root of tree
        Node *root;

        // Builds tree recursively
        Node *makeTree(int height, string currPath, int rowInd, int colInd);

        // Copies tree, necessary for copy constructor
        Node *copy(Node *toCopy);

        // Board from Board class
        Board myBoard;

        // Attempts to find solution to the game
        bool autoSolve(char target, Node *curr);

        // Deletes tree
        void destroy(Node *curr);

        // maxLength of tree = 7 moves
        static const int maxLength = 7;
};

#endif
