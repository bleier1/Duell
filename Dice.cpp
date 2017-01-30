#include "Dice.h"

// Default constructor. If not specified, the top number is assumed to be 1 and the right side is assumed to be 5.
Dice::Dice()
{
	topNum = 1;
	rightNum = 5;
	// Due to the nature of Duell's set up, the playerFacingNum will always initially be 3.
	playerFacingNum = 3;
	// The opposite sides of a die always add up to 7.
	bottomNum = 7 - topNum;
	awayFacingNum = 7 - playerFacingNum;
	leftNum = 7 - rightNum;
	// Player type is N for "no player."
	playerType = 'N';
}

// Constructor that allows specification for the number on top and right of the die.
Dice::Dice(int topInput, int rightInput, char player)
{
	// Dies can be controlled by either a human (H) or computer (C). It is not valid otherwise.
	if (player == 'H' || player == 'C') playerType = player;
	else playerType = 'N';
	// If both topInput and rightInput are 1, this is a key and thus each side must be 1.
	if (topInput == 1 && rightInput == 1)
	{
		topNum = topInput;
		leftNum = 1;
		rightNum = rightInput;
		playerFacingNum = 1;
		bottomNum = 1;
		awayFacingNum = 1;
		return;
	}
	// Otherwise, initialize each side to the same numbers of the default constructor.
	topNum = 1;
	rightNum = 5;
	playerFacingNum = 3;
	// The opposite sides of a die always add up to 7.
	bottomNum = 7 - topNum;
	awayFacingNum = 7 - playerFacingNum;
	leftNum = 7 - rightNum;
	// Now we will adjust each side so that they match the inputs passed into the constructor's parameters. This will
	// be done by rotating the die until the sides appropriately match the topInput and rightInput.
	// First, check the inputs. If they are not valid, then don't change anything about the die.
	if ((topInput < 1 || topInput > 6) || (rightInput < 1 || rightInput > 6))
	{
		topNum = 1;
		rightNum = 5;
	}
	// Otherwise, it's a legal die. Go ahead adjust the sides appropriately.
	else
	{
		// Make the topInput the topNum on the die.
		rotateToTopNum(topInput);
		// Make the rightInput the rightNum on the die.
		rotateToRightNum(rightInput);
	}
	// If it's a computer die, the die needs to be rotated twice so that the point of view of the computer player has
	// the appropriate right side of the die.
	if (playerType == 'C')
	{
		rotateLeft();
		rotateLeft();
	}
}

// Destructor.
Dice::~Dice()
{
}

/* *********************************************************************
Function Name: rollDice
Purpose: To "roll" the die in the direction specified by the parameter
Parameters:
direction, a string. it contains the direction that the die will move
Return Value: none
Local Variables:
none
Algorithm:
1) Determine the direction
2) Move in the direction specified by the string
Assistance Received: none
********************************************************************* */
void Dice::rollDice(string direction)
{
	if (direction == "up")
		moveUp();
	if (direction == "down")
		moveDown();
	if (direction == "left")
		moveLeft();
	if (direction == "right")
		moveRight();
}

/* *********************************************************************
Function Name: getTopNum
Purpose: To return the number on the top of the die
Parameters:
none
Return Value: an integer containing the top number on the die
Local Variables:
number, an int that stores topNum
Algorithm:
1) Return the integer of the die that stores the top number
Assistance Received: none
********************************************************************* */
int Dice::getTopNum() const
{
	int number = topNum;
	return number;
}

/* *********************************************************************
Function Name: getRightNum
Purpose: To return the number on the right of the die
Parameters:
none
Return Value: an integer containing the right number on the die
Local Variables:
number, an int that stores rightNum
Algorithm:
1) Return the integer of the die that stores the right number
Assistance Received: none
********************************************************************* */
int Dice::getRightNum() const
{
	int number = rightNum;
	return number;
}

/* *********************************************************************
Function Name: getLeftNum
Purpose: To return the number on the left of the die
Parameters:
none
Return Value: an integer containing the left number on the die
Local Variables:
number, an int that stores leftNum
Algorithm:
1) Return the integer of the die that stores the left number
Assistance Received: none
********************************************************************* */
int Dice::getLeftNum() const
{
	int number = leftNum;
	return number;
}

/* *********************************************************************
Function Name: getPlayerType
Purpose: To return the player type of the die (i.e. which player has control of that die)
Parameters:
none
Return Value: a character signifying the player that owns the die: H or C
Local Variables:
character, a char that stores playerType
Algorithm:
1) Return the character that corresponds to the player who controls the die
Assistance Received: none
********************************************************************* */
char Dice::getPlayerType() const
{
	char character = playerType;
	return character;
}

/* *********************************************************************
Function Name: moveUp
Purpose: To "roll" the die upwards and update each side appropriately to simulate a die being rolled up
Parameters:
none
Return Value: none
Local Variables:
temp, an integer. it stores the topNum of the die
Algorithm:
1) Initialize temp to store the topNum of the die
2) Switch every integer that needs to be switched around. topNum becomes the number that faces the player
3) playerFacingNum becomes the number on the bottom
4) bottomNum becomes the number that was facing away from the player
5) awayFacingNum becomes the number on the top of the die, which was stored in temp
Assistance Received: none
********************************************************************* */
void Dice::moveUp()
{
	// Initialize a temporary int to store the value of a number on the die.
	int temp = topNum;
	topNum = playerFacingNum;
	playerFacingNum = bottomNum;
	bottomNum = awayFacingNum;
	awayFacingNum = temp;
}

/* *********************************************************************
Function Name: moveDown
Purpose: To "roll" the die downwards and update each side appropriately to simulate a die being rolled down
Parameters:
none
Return Value: none
Local Variables:
temp, an integer. it stores the topNum of the die
Algorithm:
1) Initialize temp to store the topNum of the die
2) Switch every integer that needs to be switched around. topNum becomes the number that faces away from the player
3) awayFacingNum becomes the number on the bottom
4) bottomNum becomes the number that was facing towards the player
5) playerFacingNum becomes the number on the top of the die, which was stored in temp
Assistance Received: none
********************************************************************* */
void Dice::moveDown()
{
	// Initialize a temporary int to store the value of a number on the die.
	int temp = topNum;
	topNum = awayFacingNum;
	awayFacingNum = bottomNum;
	bottomNum = playerFacingNum;
	playerFacingNum = temp;
}

/* *********************************************************************
Function Name: moveLeft
Purpose: To "roll" the die to the left and update each side appropriately to simulate a die being rolled to the left
Parameters:
none
Return Value: none
Local Variables:
temp, an integer. it stores the topNum of the die
Algorithm:
1) Initialize temp to store the topNum of the die
2) Switch every integer that needs to be switched around. topNum becomes the number on the right of the die
3) rightNum becomes the number on the bottom
4) bottomNum becomes the number that was on the left of the die
5) leftNum becomes the number on the top of the die, which was stored in temp
Assistance Received: none
********************************************************************* */
void Dice::moveLeft()
{
	// Initialize a temporary int to store the value of a number on the die.
	int temp = topNum;
	topNum = rightNum;
	rightNum = bottomNum;
	bottomNum = leftNum;
	leftNum = temp;
}

/* *********************************************************************
Function Name: moveRight
Purpose: To "roll" the die to the right and update each side appropriately to simulate a die being rolled to the right
Parameters:
none
Return Value: none
Local Variables:
temp, an integer. it stores the topNum of the die
Algorithm:
1) Initialize temp to store the topNum of the die
2) Switch every integer that needs to be switched around. topNum becomes the number on the left of the die
3) leftNum becomes the number on the bottom
4) bottomNum becomes the number that was on the right of the die
5) rightNum becomes the number on the top of the die, which was stored in temp
Assistance Received: none
********************************************************************* */
void Dice::moveRight()
{
	// Initialize a temporary int to store the value of a number on the die.
	int temp = topNum;
	topNum = leftNum;
	leftNum = bottomNum;
	bottomNum = rightNum;
	rightNum = temp;
}

/* *********************************************************************
Function Name: rotateLeft
Purpose: To "rotate" the die to the left and update each side appropriately to simulate a die being rotated to the left
Parameters:
none
Return Value: none
Local Variables:
temp, an integer. it stores the topNum of the die
Algorithm:
1) Initialize temp to store the playerFacingNum of the die
2) Switch every integer that needs to be switched around. playerFacingNum becomes the number on the left of the die
3) leftNum becomes the number facing away from the player
4) awayFacingNum becomes the number on the right of the die
5) rightNum becomes the number that was facing the player, which was stored in temp
Assistance Received: none
********************************************************************* */
void Dice::rotateLeft()
{
	// Initialize a temporary int to store the value of a number on the die.
	int temp = playerFacingNum;
	playerFacingNum = leftNum;
	leftNum = awayFacingNum;
	awayFacingNum = rightNum;
	rightNum = temp;
}

/* *********************************************************************
Function Name: rotateToTopNum
Purpose: To rotate the die so that the number passed into the parameter is on the top of the die
Parameters:
topInput, an integer. it contains the number that will end up on the top of the die
Return Value: none
Local Variables:
none
Algorithm:
1) Determine what number topInput is storing
2) Rotate the die appropriately according to what that number is. The function assumes the top number on the die is
always 1
Assistance Received: none
********************************************************************* */
void Dice::rotateToTopNum(int topInput)
{
	// If the topInput is 1, nothing needs to be done to the die.
	if (topInput == 1) return;
	// If it's 2, it needs to be moved towards the right.
	if (topInput == 2)
	{
		moveRight();
		return;
	}
	// If it's 3, it needs to be moved upwards.
	if (topInput == 3)
	{
		moveUp();
		return;
	}
	// If it's 4, it needs to be moved downwards.
	if (topInput == 4)
	{
		moveDown();
		return;
	}
	// If it's 5, it needs to be moved to the left.
	if (topInput == 5)
	{
		moveLeft();
		return;
	}
	// If it's 6, it needs to be moved upwards twice.
	if (topInput == 6)
	{
		moveUp();
		moveUp();
		return;
	}
}

/* *********************************************************************
Function Name: rotateToRightNum
Purpose: To rotate the die so that the number passed into the parameter is on the right of the die
Parameters:
rightInput, an integer. it contains the number that will end up on the right of the die
Return Value: none
Local Variables:
none
Algorithm:
1) While the rightNum of the die is not equal to the rightInput, rotate left until it is. The function assumes that
the right number is already on the left, right, towards, or away from the player
Assistance Received: none
********************************************************************* */
void Dice::rotateToRightNum(int rightInput)
{
	// Rotate left until rightNum equals the rightInput.
	while (rightNum != rightInput)
	{
		rotateLeft();
	}
}
