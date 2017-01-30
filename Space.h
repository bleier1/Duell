// The Space class, which stores information about the die on it... if it's even there!
#pragma once
#include "Dice.h"
class Space
{
public:
	// Default constructor for Space.
	Space();
	// Constructor for Space that places a die on the space.
	Space(Dice d);
	// Destructor for Space.
	~Space();
	// Function that places a die on the space.
	void placeDie(Dice d);
	// Function that moves a die from one space to another space.
	void moveDie(Space & s, string direction);
	// Function that returns if a die is on the space or not.
	bool spaceOccupied();
	// Function that clears the space on the board.
	void clearSpace();
	// Function that returns the number on the top of the die.
	int getDieTopNum() const;
	// Function that returns the number on the right of the die.
	int getDieRightNum() const;
	// Function that returns the number on the left of the die.
	int getDieLeftNum() const;
	// Function that returns the "owner" of the die.
	char getPlayerDie() const;
private:
	// The die that is currently occupying the space.
	Dice dieOnSpace;
	// Boolean value that determines whether or not there is a die occupying the space.
	bool hasDie;
};

