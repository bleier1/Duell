#include "Board.h"

// Default constructor for Board.
Board::Board()
{
	// Duell's board is 8 rows and 9 columns, which the 2D array was already declared as.
}

// Destructor.
Board::~Board()
{
}

/* *********************************************************************
Function Name: clearBoard
Purpose: To clear the board before setting up a new game
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) For every space on the board, hasDie becomes false
Assistance Received: none
********************************************************************* */
void Board::clearBoard()
{
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			boardModel[i - 1][j - 1].clearSpace();
		}
	}
}

/* *********************************************************************
Function Name: setUpDice
Purpose: To set up the starting positions of dice in a game of Duell on the board
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Place all of the dice in the Human's home row in the correct order
2) Place all of the dice in the Computer's home row in the correct order
Assistance Received: none
********************************************************************* */
void Board::setUpDice()
{
	// Place all the human player dice.
	boardModel[0][0].placeDie(Dice(5, 6, 'H'));
	boardModel[0][1].placeDie(Dice(1, 5, 'H'));
	boardModel[0][2].placeDie(Dice(2, 1, 'H'));
	boardModel[0][3].placeDie(Dice(6, 2, 'H'));
	boardModel[0][4].placeDie(Dice(1, 1, 'H'));
	boardModel[0][5].placeDie(Dice(6, 2, 'H'));
	boardModel[0][6].placeDie(Dice(2, 1, 'H'));
	boardModel[0][7].placeDie(Dice(3, 9, 'H'));
	boardModel[0][8].placeDie(Dice(5, 6, 'H'));
	// Place all the computer player dice.
	boardModel[7][0].placeDie(Dice(5, 6, 'C'));
	boardModel[7][1].placeDie(Dice(1, 5, 'C'));
	boardModel[7][2].placeDie(Dice(2, 1, 'C'));
	boardModel[7][3].placeDie(Dice(6, 2, 'C'));
	boardModel[7][4].placeDie(Dice(1, 1, 'C'));
	boardModel[7][5].placeDie(Dice(6, 2, 'C'));
	boardModel[7][6].placeDie(Dice(2, 1, 'C'));
	boardModel[7][7].placeDie(Dice(1, 5, 'C'));
	boardModel[7][8].placeDie(Dice(5, 6, 'C'));
}

/* *********************************************************************
Function Name: placeDie
Purpose: To place the die passed into the parameters onto the row and column passed into the parameters on the board
Parameters:
die, a Dice object that will be placed on the board
row, an integer that corresponds to the row the die will be placed on
column, an integer that corresponds to the column the die will be placed on
Return Value: none
Local Variables:
none
Algorithm:
1) Call placeDie on the row and column in boardModel (minus 1 to each to convert to array coordinates)
Assistance Received: none
********************************************************************* */
void Board::placeDie(Dice die, int row, int column)
{
	// Place the die on the board.
	boardModel[row-1][column-1].placeDie(die);
}

/* *********************************************************************
Function Name: performRoll
Purpose: To make a die on the board roll in a specified direction to another space on the board
Parameters:
row, an integer that corresponds to the row of where the die is located and will move
column, an integer that corresponds to the column of where the die is located and will move
direction, a string that tells the function which direction to move the die
Return Value: a boolean that determines if the roll was successfully performed or not
Local Variables:
none
Algorithm:
1) Determine which direction the die wants to roll
2) Roll in the direction specified by the string passed into the function and return true
3) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Board::performRoll(int row, int column, string direction)
{
	// Perform the roll.
	if (direction == "up")
	{
		boardModel[row - 1][column - 1].moveDie(boardModel[row][column - 1], "up");
		return true;
	}
	if (direction == "down")
	{
		boardModel[row - 1][column - 1].moveDie(boardModel[row - 2][column - 1], "down");
		return true;
	}
	if (direction == "left")
	{
		boardModel[row - 1][column - 1].moveDie(boardModel[row - 1][column - 2], "left");
		return true;
	}
	if (direction == "right")
	{
		boardModel[row - 1][column - 1].moveDie(boardModel[row - 1][column], "right");
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: isDieOn
Purpose: To determine the status of whether or not there is a die on the coordinates passed into the function
Parameters:
row, an integer that corresponds to the row of where the function will check for a die
column, an integer that corresponds to the column of where the function will check for a die
Return Value: a boolean that determines if there is a die on the coordinates or not
Local Variables:
none
Algorithm:
1) Call spaceOccupied() on the space located where row and column are in the boardModel array
2) Return true if the function returns true, return false otherwise
Assistance Received: none
********************************************************************* */
bool Board::isDieOn(int row, int column)
{
	// If there is a die on the space, return true. Otherwise, return false.
	if (boardModel[row - 1][column - 1].spaceOccupied()) return true;
	return false;
}

/* *********************************************************************
Function Name: isDiePlayerType
Purpose: To determine if the die on the coordinates passed into the function is of the player type passed into the function
Parameters:
row, an integer that corresponds to the row of where the die is located
column, an integer that corresponds to the column of where the die is located
playerChar, a character that corresponds to the player type of the die that will be checked
Return Value: a boolean that determines if there the die is of the player type playerChar
Local Variables:
none
Algorithm:
1) Call getPlayerDie() on the space located where row and column are in the boardModel array
2) Compare that to playerChar
3) Return true if it is the same, return false otherwise
Assistance Received: none
********************************************************************* */
bool Board::isDiePlayerType(int row, int column, char playerChar)
{
	// If the die on the space is of the same player type as playerChar, return true. Otherwise, return false.
	if (boardModel[row - 1][column - 1].getPlayerDie() == playerChar) return true;
	return false;
}

/* *********************************************************************
Function Name: isKeyDie
Purpose: To determine if the die on the coordinates passed into the function is a key die or not
Parameters:
row, an integer that corresponds to the row of where the die is located
column, an integer that corresponds to the column of where the die is located
Return Value: a boolean that determines if there the die is a key die or not
Local Variables:
topNum and rightNum, integers that store the results of getTopNum() and getRightNum() respectively
Algorithm:
1) Call spaceOccupied() on the space that corresponds to the row and column coordinates. Return false is that
function returns false
2) Otherwise, there's a die on the space. Get the top and right numbers of the die on the space
3) If those numbers are both 1, it's a key die. Return true. Otherwise return false
Assistance Received: none
********************************************************************* */
bool Board::isKeyDie(int row, int column)
{
	// Check if there is even a die on the space. If there isn't, return false.
	if (!boardModel[row - 1][column - 1].spaceOccupied()) return false;
	// Get the top number on the die occupying the space.
	int topNum = boardModel[row - 1][column - 1].getDieTopNum();
	// Get the right number on the die occupying the space.
	int rightNum = boardModel[row - 1][column - 1].getDieRightNum();
	// If they are both 1, this is a key die.
	if (topNum == 1 && rightNum == 1) return true;
	// Otherwise, it is not.
	return false;
}

/* *********************************************************************
Function Name: getDieName
Purpose: To return the name of the die on the coordinates passed into the function
Parameters:
row, an integer that corresponds to the row of where the die is located
column, an integer that corresponds to the column of where the die is located
Return Value: a string containing the name of the die on the space
Local Variables:
topNum and RightNum, integers that store the results of getTopNum() and getRightNum() respectively
Algorithm:
1) Store the results of getTopNum() and getRightNum()/getLeftNum() in topNum and rightNum respectively
2) If the player type of the die is H, get the rightNum. If the player type of the die is C, get the leftNum
3) Return a string contatenating the character of the player type, and the top and right number converted to strings
Assistance Received: none
********************************************************************* */
string Board::getDieName(int row, int column) const
{
	// Integers for the topNum and rightNum of the die.
	int topNum = 0;
	int rightNum = 0;
	// Get the top number on the die occupying the space.
	topNum = boardModel[row-1][column-1].getDieTopNum();
	// Get the right number on the die occupying the space.
	// If it's a human, get the rightNum. If it's a computer, get the leftNum.
	if (boardModel[row-1][column-1].getPlayerDie() == 'H') rightNum = boardModel[row-1][column-1].getDieRightNum();
	if (boardModel[row-1][column-1].getPlayerDie() == 'C') rightNum = boardModel[row-1][column-1].getDieLeftNum();
	// Convert these to strings, concatenate together with the player type, and return it.
	return string((boardModel[row-1][column-1].getPlayerDie()) + to_string(topNum) + to_string(rightNum));
}

/* *********************************************************************
Function Name: getDieTopNum
Purpose: To return the top number of the die on the coordinates passed into the function
Parameters:
row, an integer that corresponds to the row of where the die is located
column, an integer that corresponds to the column of where the die is located
Local Variables:
none
Algorithm:
1) Call getDieTopNum() on the coordinates of boardModel that correspond to row and column and return the result
Assistance Received: none
********************************************************************* */
int Board::getDieTopNum(int row, int column) const
{
	return boardModel[row-1][column-1].getDieTopNum();
}