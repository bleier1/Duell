// The Dice class, which stores information about the dice that the players use in the game.
#pragma once
#include <string>
using namespace std;

class Dice
{
public:
	// Default constructor.
	Dice();
	// Constructor that sets the top number and right number on the dice and the player that "owns" the die.
	Dice(int topInput, int rightInput, char player);
	// Destructor.
	~Dice();
	// The moveDice() function that moves the die in a direction specified by the input.
	void rollDice(string direction);
	// Returns the top number on the die.
	int getTopNum() const;
	// Returns the number on the right side of the die.
	int getRightNum() const;
	// Returns the number on the left side of the die.
	int getLeftNum() const;
	// Returns the player type of the die.
	char getPlayerType() const;
private:
	// The top number on the die.
	int topNum;
	// The number on the die that faces the player.
	int playerFacingNum;
	// The number on the die that is on the bottom.
	int bottomNum;
	// The number on the die that is facing away from the player.
	int awayFacingNum;
	// The number on the die to the left of the top number.
	int leftNum;
	// The number on the die to the right of the top number.
	int rightNum;
	// The character that represents which player has control of the die.
	char playerType;
	// Moves the die upwards.
	void moveUp();
	// Moves the die downwards.
	void moveDown();
	// Moves the die towards the left.
	void moveLeft();
	// Moves the die towards the right.
	void moveRight();
	// Rotates the die's sides to the left.
	void rotateLeft();
	// Rotates the die so that the number in the parameter ends up on the top of the die.
	void rotateToTopNum(int topInput);
	// Rotates the die so that the number in the parameter ends up on the right of the die.
	void rotateToRightNum(int rightInput);
};

