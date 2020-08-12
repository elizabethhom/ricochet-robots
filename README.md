# ricochet-robots
A text-based game where a robot must navigate through a maze by ricocheting off walls in search of the target. *ricochet-robots* can be played in interactive (user controlled) or automatic mode, where the program automatically searches for a solution to the puzzle by using a tree that models all possible paths of the robot's movement from its starting position.

### Compile & Run
* Compile program using "make"
* Run with executable: ./gorobots \<boardFile\>

### Purpose
*ricochet-robots* is inspired by the board game of the same name, where a robot must navigate through a maze by ricocheting off walls in search of the target. The program works in two modes: interactive & automatic mode.
* Interactive mode: Allows the user to control the robot's movements in search of the target.
* Automatic mode: Automates the target seraching, and if found, prints a solution to the puzzle in 7 steps or less.
See end of README.md for example of game play.

### Program Architecture
The program uses two classes: Board and Tree. Board uses a two-dimensional 15x15 array to represent the game board, and is responsible for documenting the robot's position and game board elements (horizontal and vertical walls, robot, target). Tree builds a tree that models all possible paths of the robot's movement from its starting position on the board.

### Files
* main.cpp: Main driver for *ricochet-robots*. Prompts user for robot symbol and starting row and column position. Populates board and runs program (interactive & automatic mode).
* Board.cpp: Implementation of Board class. Oversees game board, board elements, and relevant functions, such as moving robot, printing board, checking win conditions.
* Board.h: Interface of Board class.
* Tree.cpp: Implementation of Tree class. Oversees building of tree that models all possible paths of robot from its starting position, and searching tree for a solution.
* Tree.h: Interface of Tree class.
* Makefile: Contains code that builds the program.

### Game Play Example

