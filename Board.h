// The Board class that implements the model of the board that the game will be played on.
#pragma once
#include "Space.h"
class Board
{
public:
	// Default constructor for Board.
	Board();
	// Destructor.
	~Board();
	// Clears the board.
	void clearBoard();
	// Function to initialize starting dice on the board.
	void setUpDice();
	// Function that places a die on the coordinates passed into the function.
	void placeDie(Dice die, int row, int column);
	// Function that performs a roll on the board.
	bool performRoll(int row, int column, string direction);
	// Function that returns whether or not a die is currently on the space passed into the function.
	bool isDieOn(int row, int column);
	// Function that returns whether or not the die on the space passed into the function is of the player type specified
	// by the parameter.
	bool isDiePlayerType(int row, int column, char playerChar);
	// Function that returns whether or not the die is a key die.
	bool isKeyDie(int row, int column);
	// Function that returns the "name" of the die occupying the space passed into the function.
	string getDieName(int row, int column) const;
	// Function that returns the top number on the die at the space passed into the function.
	int getDieTopNum(int row, int column) const;
private:
	// A container of spaces that make up the board. It will use a 2D array.
	Space boardModel[8][9];
};

