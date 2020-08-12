/********************************************
* Comp 15 - Fall 2019
* Project 1
* ELIZABETH HOM
* 23 OCT 2019
* 
* Tree.h
*
* Tree interface
* Class interface for the Tree Class
*********************************************/

#include <iostream>

#include "Board.h"

using namespace std;

#ifndef TREE_H_
#define TREE_H_

class Tree
{
    public:
        // parametrized constructor
        Tree(Board inputBoard);

        // destructor
        ~Tree();

        // calls private autoSolve, searches tree for solution
        bool autoSolve(char target);

        // copy constructor
        Tree(const Tree &t);

        // assignment operator
        Tree& operator=(const Tree &t);

    private:
        // Tree node struct, contains path to reach node, row, col index of
        // robot at that node, board character at that node, pointers to all
        // four directions
        struct Node {
            string path;
            int row, col;
            char boardChar;
            Node *north, *east, *south, *west;
        };

        // pointer to root of tree
        Node *root;

        // builds the tree recursively
        Node *makeTree(int height, string currPath, int rowInd, int colInd);

        // copies the tree, necessary for copy constructor
        Node *copy(Node *toCopy);

        // board from Board class
        Board myBoard;

        // attempts to find a solution to the game
        bool autoSolve(char target, Node *curr);

        // deletes the tree
        void destroy(Node *curr);

        // constant for maxLength of tree (7 moves)
        static const int maxLength = 7;
};

#endif
