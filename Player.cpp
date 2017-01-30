#include "Player.h"

// Default constructor.
Player::Player()
{
	// The player class will have the name N/A.
	playerName = "N/A";
}

/* *********************************************************************
Function Name: namePlayer
Purpose: To give the Player a name
Parameters:
name, a string that contains the name that the character will be named
Return Value: none
Local Variables:
none
Algorithm:
1) Assign the playerName in the class to name
Assistance Received: none
********************************************************************* */
void Player::namePlayer(string name)
{
	playerName = name;
}

/* *********************************************************************
Function Name: getPlayerName
Purpose: To return the name of the Player
Parameters:
none
Return Value: a string containing the name of the Player
Local Variables:
none
Algorithm:
1) Store the playerName in a string variable called name
2) Return name
Assistance Received: none
********************************************************************* */
string Player::getPlayerName() const
{
	string name = playerName;
	return name;
}

/* *********************************************************************
Function Name: play
Purpose: A virtual function that will let the derived classes Human and Computer play the game of Duell
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
none
Assistance Received: none
********************************************************************* */
void Player::play(Board & b)
{}

// Destructor.
Player::~Player()
{
}

/* *********************************************************************
Function Name: makeMove
Purpose: To make the move that the player wants to make on the board
Parameters:
b, a Board passed by parameter that will be modified so the move can be appropriately made
dieRow, an integer containing the row of the die that will be moved
dieColumn, an integer containing the column of the die that will be moved
spaceCoordinate, an integer containing the row or column that the die will be moved to
direction, a string containing the direction that the die will move in to get to the spaceCoordinate
Return Value: none
Local Variables:
i, an integer used to iterate through for loops
Algorithm:
1) Determine if the direction is moving frontally or laterally
2) Perform a check to see if the spaceCoordinate is greater or less than dieRow or dieColumn
3) Call performRoll() to roll in the appropriate direction determined by the check in the previous step
Assistance Received: none
********************************************************************* */
void Player::makeMove(Board & b, int dieRow, int dieColumn, int spaceCoordinate, string direction)
{
	// First, determine whether to move frontally or laterally.
	if (direction == "frontally")
	{
		// Is the spaceCoordinate entered greater than the dieRow? If so, we must move upwards.
		if (spaceCoordinate > dieRow)
		{
			for (int i = dieRow; i < spaceCoordinate; i++)
			{
				b.performRoll(i, dieColumn, "up");
			}
		}
		// Otherwise, move downwards.
		else
		{
			for (int i = dieRow; i > spaceCoordinate; i--)
			{
				b.performRoll(i, dieColumn, "down");
			}
		}
	}
	// Otherwise, move laterally.
	else
	{
		// Is the spaceCoordinate entered greater than the dieColumn? If so, we must move towards the right.
		if (spaceCoordinate > dieColumn)
		{
			for (int i = dieColumn; i < spaceCoordinate; i++)
			{
				b.performRoll(dieRow, i, "right");
			}
		}
		// Otherwise, move towards the left.
		else
		{
			for (int i = dieColumn; i > spaceCoordinate; i--)
			{
				b.performRoll(dieRow, i, "left");
			}
		}
	}
}

/* *********************************************************************
Function Name: canMoveLaterally
Purpose: To determine if a die can be moved laterally on the board
Parameters:
b, the Board that is being played on
dieRow, an integer containing the row of the die that will be checked
dieColumn, an integer containing the column of the die that will be checked
spaceColumn, an integer containing the column of the space that the die wants to move to
spacesToMove, an integer containing the amount of spaces the die will move to reach the column
playerType, a character containing the player type of the die that is being checked
Return Value: a boolean signifying whether or not a lateral move is possible
Local Variables:
i, an integer used to iterate through for loops
Algorithm:
1) Check spacesToMove. If it's 0, the die cannot move anywhere. Return false
2) Check dieColumn and spaceColumn. If they're the same, the die can only be moved frontally. Return false
3) Check whether the lateral move is to the left or to the right
4) For each space in between the dieColumn and spaceColumn, see if there is a die occupying any of them
5) If spacesToMove isn't 1, a die cannot be placed there regardless of who owns the die. Return false
6) Otherwise, if it's of an opponent's playerType, it can be captured and the die can be moved there. Return true
7) But if it's one of the player's dice, you can't capture those. Return false
8) Return true if there were no problems detected
Assistance Received: none
********************************************************************* */
bool Player::canMoveLaterally(Board b, int dieRow, int dieColumn, int spaceColumn, int spacesToMove, char playerType)
{
	// First, if spacesToMove is 0, we can't move anywhere.
	if (spacesToMove == 0) return false;
	// If dieColumn and spaceColumn are the same, we can only move frontally.
	if (dieColumn == spaceColumn) return false;
	// We'll move to the right if the spaceColumn is greater than the dieColumn. Otherwise, we move to the left.
	if (spaceColumn > dieColumn)
	{
		// A for loop to check all of the spaces that we want to visit.
		for (int i = dieColumn; i < spaceColumn; i++)
		{
			// Check if there is a die on the space.
			if (b.isDieOn(dieRow, i+1))
			{
				// If spacesToMove is not 1, you cannot place the die there regardless of whether or not the die on it
				// is yours or the opponent's.
				if (spacesToMove != 1) return false;
				// If it is 1, check the playerType of the die on it.
				else
				{
					// If it is not the playerType passed into the function, it is an opponent's die and can be captured.
					if (!b.isDiePlayerType(dieRow, i+1, playerType)) return true;
					// Otherwise, this is one of the player's own dice and thus cannot be captured or moved to.
					else return false;
				}
			}
			// If there is not, decrement spacesToMove.
			spacesToMove--;
		}
		// We can move this way.
		return true;
	}
	// Move to the left if this is not the case.
	else
	{
		// A for loop to check all of the spaces that we want to visit.
		for (int i = dieColumn; i > spaceColumn; i--)
		{
			// Check if there is a die on the space.
			if (b.isDieOn(dieRow, i-1))
			{
				// If spacesToMove is not 1, you cannot place the die there regardless of whether or not the die on it
				// is yours or the opponent's.
				if (spacesToMove != 1) return false;
				// If it is 1, check the playerType of the die on it.
				else
				{
					// If it is not the playerType passed into the function, it is an opponent's die and can be captured.
					if (!b.isDiePlayerType(dieRow, i-1, playerType)) return true;
					// Otherwise, this is one of the player's own dice and thus cannot be captured or moved to.
					else return false;
				}
			}
			// If there is not, decrement spacesToMove.
			spacesToMove--;
		}
		// We can move this way.
		return true;
	}
}

/* *********************************************************************
Function Name: canMoveFrontally
Purpose: To determine if a die can be moved frontally on the board
Parameters:
b, the Board that is being played on
dieRow, an integer containing the row of the die that will be checked
dieColumn, an integer containing the column of the die that will be checked
spaceRow, an integer containing the row of the space that the die wants to move to
spacesToMove, an integer containing the amount of spaces the die will move to reach the column
playerType, a character containing the player type of the die that is being checked
Return Value: a boolean signifying whether or not a frontal move is possible
Local Variables:
i, an integer used to iterate through for loops
Algorithm:
1) Check spacesToMove. If it's 0, the die cannot move anywhere. Return false
2) Check dieRow and spaceRow. If they're the same, the die can only be moved laterally. Return false
3) Check whether the frontal move is upwards or downards
4) For each space in between the dieRow and spaceRow, see if there is a die occupying any of them
5) If spacesToMove isn't 1, a die cannot be placed there regardless of who owns the die. Return false
6) Otherwise, if it's of an opponent's playerType, it can be captured and the die can be moved there. Return true
7) But if it's one of the player's dice, you can't capture those. Return false
8) Return true if there were no problems detected
Assistance Received: none
********************************************************************* */
bool Player::canMoveFrontally(Board b, int dieRow, int dieColumn, int spaceRow, int spacesToMove, char playerType)
{
	// First, if spacesToMove is 0, we can't move anywhere.
	if (spacesToMove == 0) return false;
	// If dieRow and spaceRow are the same, we can only move laterally.
	if (dieRow == spaceRow) return false;
	// We'll move up if the spaceRow is greater than the dieRow. Otherwise, we move down.
	if (spaceRow > dieRow)
	{
		// A for loop to check all of the spaces that we want to visit.
		for (int i = dieRow; i < spaceRow; i++)
		{
			// Check if there is a die on the space.
			if (b.isDieOn(i + 1, dieColumn))
			{
				// If spacesToMove is not 1, you cannot place the die there regardless of whether or not the die on it
				// is yours or the opponent's.
				if (spacesToMove != 1) return false;
				// If it is 1, check the playerType of the die on it.
				else
				{
					// If it is not the playerType passed into the function, it is an opponent's die and can be captured.
					if (!b.isDiePlayerType(i+1, dieColumn, playerType)) return true;
					// Otherwise, this is one of the player's own dice and thus cannot be captured or moved to.
					else return false;
				}
			}
			// If there is not, decrement spacesToMove.
			spacesToMove--;
		}
		// We can move this way.
		return true;
	}
	// Move down if this is not the case.
	else
	{
		// A for loop to check all of the spaces that we want to visit.
		for (int i = dieRow; i > spaceRow; i--)
		{
			// Check if there is a die on the space.
			if (b.isDieOn(i - 1, dieColumn))
			{
				// If spacesToMove is not 1, you cannot place the die there regardless of whether or not the die on it
				// is yours or the opponent's.
				if (spacesToMove != 1) return false;
				// If it is 1, check the playerType of the die on it.
				else
				{
					// If it is not the playerType passed into the function, it is an opponent's die and can be captured.
					if (!b.isDiePlayerType(i-1, dieColumn, playerType)) return true;
					// Otherwise, this is one of the player's own dice and thus cannot be captured or moved to.
					else return false;
				}
			}
			// If there is not, decrement spacesToMove.
			spacesToMove--;
		}
		// We can move this way.
		return true;
	}
}

/* *********************************************************************
Function Name: findKeyDie
Purpose: To get the coordinates of a key die on the board
Parameters:
board, the Board that is being played on
spaceRow, an integer passed by reference so that it will store the row of the key die
spaceColumn, an integer passed by reference so that it will store the column of the key die
playerType, a character containing the "owner" of the key die
Return Value: none
Local Variables:
i and j, integers used to iterate through for loops and determine the rows and columns
Algorithm:
1) Iterate through the board using for loops
2) If there's a key die on the space, check its player type
3) If it's of playerType, assign spaceRow and spaceColumn to i and j respectively and return
Assistance Received: none
********************************************************************* */
void Player::findKeyDie(Board board, int & spaceRow, int & spaceColumn, char playerType)
{
	// Use a for loop to iterate through the board.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// If there is a key die on the space, check the playerType.
			if (board.isKeyDie(i, j))
			{
				// If it is of the playerType passed into the function, we have found the key die. Register its coordinates.
				if (board.isDiePlayerType(i, j, playerType))
				{
					spaceRow = i;
					spaceColumn = j;
					return;
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: canMoveToSpace
Purpose: To determine if a die can be moved to a space on the board
Parameters:
b, the Board that is being played on
dieRow, an integer containing the row of the die that will be checked
dieColumn, an integer containing the column of the die that will be checked
spaceRow, an integer containing the row of the space that the die wants to move to
spaceColumn, an integer containing the column of the space that the die wants to move to
playerType, a character containing the player type of the die that is being checked
Return Value: a boolean signifying whether or not a move is possible
Local Variables:
topNumber, an integer that stores the top number of the die located at (dieRow,dieColumn)
rowRolls and columnRolls, integers that store the number of spaces needed to move frontally and laterally respectively
frontalMove and lateralMove, booleans that store whether or not a frontal or lateral move is possible
secondFrontalMove and secondLateralMove, booleans that store whether or not a frontal or lateral move is possible after
a 90 degree turn
Algorithm:
1) Get the topNumber, rowRolls, and columnRolls needed to check if a die can be moved
2) If topNumber is not equal to rowRolls + columnRolls, a move is not possible. Return false
3) Check if the coordinates of the space being moved to are valid (on the board). If not return false
4) Check if the die can be moved frontally or laterally
5) If it can't move either way return false
6) If a frontal move is possible, check for a second lateral move. If it isn't possible and the remaining columnRolls
isn't 0, a move is not possible.
7) Otherwise, a move is possible. Return true
8) If a lateral move is possible, check for a second frontal move. If it isn't possible and the remaining rowRolls isn't
0, a move is not possible.
9) Otherwise, a movie is possible. Return true
10) If the function has not returned true yet, a move is not possible. Return false
Assistance Received: none
********************************************************************* */
bool Player::canMoveToSpace(Board board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, char playerType)
{
	// Integer for the top number of a die.
	int topNumber = board.getDieTopNum(dieRow, dieColumn);
	// Integers for the number of rolls needed to go to a space.
	int rowRolls = abs(spaceRow - dieRow);
	int columnRolls = abs(spaceColumn - dieColumn);
	// Boolean values of whether or not you can move frontally or laterally.
	bool frontalMove;
	bool lateralMove;
	// Boolean values of whether or not you can move frontally or laterally after already moving in that direction.
	bool secondFrontalMove;
	bool secondLateralMove;
	
	// First, check to see if the number on the top of the die is able to move enough spaces to travel to the coordinates.
	if (topNumber != rowRolls + columnRolls) return false;

	// Now check to see if the coordinates the die wants to move to are valid positions.
	if ((spaceRow < 1 || spaceRow > 8) || (spaceColumn < 1 || spaceColumn > 9)) return false;

	// Now check if the die can move there without any problems.
	frontalMove = canMoveFrontally(board, dieRow, dieColumn, spaceRow, topNumber, playerType);
	lateralMove = canMoveLaterally(board, dieRow, dieColumn, spaceColumn, topNumber, playerType);
	// If it cannot move either way at first, it cannot move to the space.
	if (!frontalMove && !lateralMove) return false;
	// If it can move frontally, check to see if it can move laterally in a 90 degree turn.
	if (frontalMove)
	{
		// If you can move frontally (at first) but you cannot move laterally afterwards and
		// the remaining number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveLaterally(board, spaceRow, dieColumn, spaceColumn, columnRolls, playerType)
		&& columnRolls != 0)
			secondLateralMove = false;
		// Otherwise, a move is possible.
		else return true;
	}
	// If it can move laterally, check to see if it can move frontally in a 90 degree turn.
	if (lateralMove)
	{
		// If you can move laterally (at first) but you cannot move frontally afterwards and
		// the remaining number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveFrontally(board, dieRow, spaceColumn, spaceRow, rowRolls, playerType) && rowRolls != 0)
			secondFrontalMove = false;
		// Otherwise, a move is possible.
		else return true;
	}

	// Otherwise, there is no possible move.
	return false;
}

/* *********************************************************************
Function Name: captureKeyDieScore
Purpose: To determine if a key die can be captured or not
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die that can capture the key die
dieColumn, an integer passed by reference that will contain the column of the die that can capture the key die
spaceRow, an integer passed by reference that will contain the row of the key die
spacesColumn, an integer passed by reference that will contain the column of the key die
playerType, a character containing the player type of the player "calling" the function
Return Value: a boolean signifying whether or not a key die capture is possible
Local Variables:
i and j, integers used to iterate through for loops
Algorithm:
1) Use findKeyDie() to get the coordinates of the enemy key die and put them into spaceRow and spaceColumn
2) After finding the key die coordinates, scan the board for the player's dice
3) For each die found that belongs to the player, see if it can move to the key die's coordinates
4) If so, put i and j into dieRow and dieColumn and return true
5) If nothing can be found, return false
Assistance Received: none
********************************************************************* */
bool Player::captureKeyDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType)
{
	// First, find the coordinates of the key die. Use a for loop to iterate through the board.
	if (playerType == 'H') findKeyDie(board, spaceRow, spaceColumn, 'C');
	else findKeyDie(board, spaceRow, spaceColumn, 'H');
	// Now that we have found the opponent's key die, scan the board for your dice positions.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// See if there a player's die occupying the space.
			if (board.isDieOn(i, j) && board.isDiePlayerType(i, j, playerType))
			{
				// Check if it can move there without any problems. Return if we can.
				if (canMoveToSpace(board, i, j, spaceRow, spaceColumn, playerType))
				{
					dieRow = i;
					dieColumn = j;
					return true;
				}
			}
		}
	}
	// Capturing the key die is not feasible.
	return false;
}

/* *********************************************************************
Function Name: captureKeySpaceScore
Purpose: To determine if a key space can be captured or not
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die that can capture the key die
dieColumn, an integer passed by reference that will contain the column of the die that can capture the key die
spaceRow, an integer containing the key space's row
spacesColumn, an integer containing the key space's column
playerType, a character containing the player type of the player "calling" the function
Return Value: a boolean signifying whether or not a key space capture is possible
Local Variables:
i and j, integers used to iterate through for loops
Algorithm:
1) Scan the board for the player's dice
2) For each die found, check if it can move to the key space
3) If so, put i and j into dieRow and dieColumn respectively. Return true
4) If nothing can be found, return false
Assistance Received: none
********************************************************************* */
bool Player::captureKeySpaceScore(Board board, int & dieRow, int & dieColumn, int spaceRow, int spaceColumn, char playerType)
{
	// The coordinates of the key space are passed into the function. All we need to do is scan the board for the
	// player's dice to see if any of them can occupy it.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// See if a player's die is occupying the space.
			if (board.isDieOn(i, j) && board.isDiePlayerType(i, j, playerType))
			{
				// Check if it can move there without any problems. Return if we can.
				if (canMoveToSpace(board, i, j, spaceRow, spaceColumn, playerType))
				{
					dieRow = i;
					dieColumn = j;
					return true;
				}
			}
		}
	}
	// Capturing the key space is not feasible.
	return false;
}

/* *********************************************************************
Function Name: blockKeyDieScore
Purpose: To determine if a key die capture needs to be blocked or not
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die that can block the capture
dieColumn, an integer passed by reference that will contain the column of the die that can block the capture
spaceRow, an integer passed by reference that will contain the row of the die that can capture the key die
spacesColumn, an integer passed by reference that will contain the column of the die that can capture the key die
playerType, a character containing the player type of the player "calling" the function
Return Value: a boolean signifying whether or not a block is possible
Local Variables:
keyDieRow and keyDieColumn, integers that will store the coordinates of the player's key die
opponentType, a character that stores the player type of the opponent of the player "calling" the function
i, j, playerRow, playerCol, a, b, c, and d, integers that iterate through for loops to scan the board
Algorithm:
1) Use findKeyDie() to get the coordinates of the player's key die and put them into keyDieRow and keyDieColumn
2) Scan the board for the opponent's dice
3) If a die is found and is able to move to the key die coordinates without problems, a block is necessary. Enter
more for loops
4) Scan the board for the player's dice
5) If a die is found, see if it can capture the die that threatens to capture the key die. If it can, assign dieRow to 
playerRow, dieColumn to playerCol, spaceRow to i, spaceColumn to j, and return true
6) Otherwise, see if the die can block the offending die's path
7) If the offending die and the key die are in the same row, try to move to a space in between the columns that separate
them
8) If the offending die and the key die are in the same column, try to move to a space in between the rows that separate
them
9) If a blocking move is possible, assign dieRow to playerRow, dieColumn to playerCol, spaceRow to the appropriate row,
spaceColumn to the appropriate column, and return true
10) Otherwise, if all else fails, just try moving the key die away by one space in any direction, assign the parameters
appropriately, and return true
11) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Player::blockKeyDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType)
{
	// Integers to store key die coordinates.
	int keyDieRow = 0;
	int keyDieColumn = 0;
	// Character to store the opponent's playerType.
	char opponentType;
	if (playerType = 'H') opponentType = 'C';
	if (playerType = 'C') opponentType = 'H';

	// Find the player's key die coordinates.
	findKeyDie(board, keyDieRow, keyDieColumn, playerType);
	// Now scan the board for the opponent's dice.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// See if an opponents's die is occupying the space.
			if (board.isDieOn(i, j) && board.isDiePlayerType(i, j, opponentType))
			{
				// Check if it can move there without any problems.
				if (canMoveToSpace(board, i, j, keyDieRow, keyDieColumn, opponentType))
				{
					// We need to create a problem/capture the offending die.
					// Scan the board for the player's dice.
					for (int playerRow = 8; playerRow > 0; playerRow--)
					{
						for (int playerCol = 1; playerCol < 10; playerCol++)
						{
							// See if the player's die is occupying the space.
							if (board.isDieOn(playerRow, playerCol) && board.isDiePlayerType(playerRow,
								playerCol, playerType))
							{
								// Check if it can move to the offending die without any problems.
								if (canMoveToSpace(board, playerRow, playerCol, i, j, playerType))
								{
									// Return 1 if it can, as the die can be captured with this move.
									dieRow = playerRow;
									dieColumn = playerCol;
									spaceRow = i;
									spaceColumn = j;
									return true;
								}
								// Otherwise, try to block the die's path.
								// See if the offending die and the key die are in the same row.
								if (keyDieRow == i)
								{
									// If key die is to the left of the offending die, only search between those
									// spaces:
									if (keyDieColumn < j)
									{
										for (int a = keyDieColumn; a < j; a++)
										{
											// Check if the die can move there.
											if (canMoveToSpace(board, playerRow, playerCol, keyDieRow, a,
												playerType))
											{
												// The die can be blocked. Move there.
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = keyDieRow;
												spaceColumn = a;
												return true;
											}
										}
									}
									// Otherwise, the key die is to the right:
									else
									{
										for (int b = j; b > keyDieColumn; b--)
										{
											// Check if the die can move there.
											if (canMoveToSpace(board, playerRow, playerCol, keyDieRow, b,
												playerType))
											{
												// The die can be blocked. Move there.
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = keyDieRow;
												spaceColumn = b;
												return true;
											}
										}
									}
								}
								// See if the offending die and the key die are in the same column.
								if (keyDieColumn == j)
								{
									// If the key die is above the offending die, only search between those spaces:
									if (keyDieRow > i)
									{
										for (int c = i; c < keyDieRow; c++)
										{
											// Check if the die can move there.
											if (canMoveToSpace(board, playerRow, playerCol, c, keyDieColumn,
												playerType))
											{
												// The die can be blocked. Move there.
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = c;
												spaceColumn = keyDieColumn;
												return true;
											}
										}
									}
									// Otherwise, it's below the key die:
									else
									{
										for (int d = keyDieRow; d > i; d--)
										{
											// Check if the die can move there.
											if (canMoveToSpace(board, playerRow, playerCol, d, keyDieColumn,
												playerType))
											{
												// The die can be blocked. Move there.
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = d;
												spaceColumn = keyDieColumn;
												return true;
											}
										}
									}
								}
							}
						}
					}
					// When all else fails, try moving the key die away.
					// If they're in the same row, move to a different row:
					if (keyDieRow == i)
					{
						// Try moving the the row below.
						if (canMoveToSpace(board, keyDieRow, keyDieColumn, keyDieRow - 1, keyDieColumn,
							playerType))
						{
							// Move there.
							dieRow = keyDieRow;
							dieColumn = keyDieColumn;
							spaceRow = keyDieRow - 1;
							spaceColumn = keyDieColumn;
							return true;
						}
						// Try moving the row above.
						if (canMoveToSpace(board, keyDieRow, keyDieColumn, keyDieRow + 1, keyDieColumn,
							playerType))
						{
							// Move there.
							dieRow = keyDieRow;
							dieColumn = keyDieColumn;
							spaceRow = keyDieRow + 1;
							spaceColumn = keyDieColumn;
							return true;
						}
					}
					// If they're in the same column move to a different column:
					if (keyDieColumn == j)
					{
						// Try moving to the column to the right.
						if (canMoveToSpace(board, keyDieRow, keyDieColumn, keyDieRow, keyDieColumn + 1,
							playerType))
						{
							// Move there.
							dieRow = keyDieRow;
							dieColumn = keyDieColumn;
							spaceRow = keyDieRow;
							spaceColumn = keyDieColumn + 1;
							return true;
						}
						// Try moving to the column to the left.
						if (canMoveToSpace(board, keyDieRow, keyDieColumn, keyDieRow, keyDieColumn - 1,
							playerType))
						{
							// Move there.
							dieRow = keyDieRow;
							dieColumn = keyDieColumn;
							spaceRow = keyDieRow;
							spaceColumn = keyDieColumn - 1;
							return true;
						}
					}
				}
			}
		}
	}
	// Blocking the key die from being captured is not necessary or feasible.
	return false;
}

/* *********************************************************************
Function Name: blockKeySpaceScore
Purpose: To determine if a key space capture needs to be blocked or not
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die that can block the capture
dieColumn, an integer passed by reference that will contain the column of the die that can block the capture
spaceRow, an integer passed by reference that will contain the row of the die that can capture the key die
spacesColumn, an integer passed by reference that will contain the column of the die that can capture the key die
playerType, a character containing the player type of the player "calling" the function
Return Value: a boolean signifying whether or not a block is possible
Local Variables:
keySpaceRow and keySpaceColumn, integers that will store the coordinates of the player's key space
opponentType, a character that stores the player type of the opponent of the player "calling" the function
i, j, playerRow, playerCol, a, b, c, d, e, and f, integers that iterate through for loops to scan the board
Algorithm:
1) Store spaceRow and spaceColumn into keySpaceRow and keySpaceColumn
2) Scan the board for the opponent's dice
3) If a die is found and is able to move to the key space coordinates without problems, a block is necessary. Enter
more for loops
4) Scan the board for the player's dice
5) If a die is found, see if it can capture the die that threatens to capture the key space. If it can, assign dieRow to
playerRow, dieColumn to playerCol, spaceRow to i, spaceColumn to j, and return true
6) Otherwise, see if the die can block the offending die's path
7) If the offending die and the key space are in the same row, try to move to a space in between the columns that separate
them
8) If the offending die and the key space are in the same column, try to move to a space in between the rows that separate
them
9) If a blocking move is possible, assign dieRow to playerRow, dieColumn to playerCol, spaceRow to the appropriate row,
spaceColumn to the appropriate column, and return true
10) Otherwise, try moving the die within the column of the key space. If possible, assign the appropriate values and return
true
11) Otherwise, return false
Assistance Received: none
********************************************************************* */
bool Player::blockKeySpaceScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType)
{
	// Integers to store the key space row and column, as they may be overwritten with new coordinates to move to.
	int keySpaceRow = spaceRow;
	int keySpaceColumn = spaceColumn;
	// Opponent player type.
	char opponentType;
	if (playerType == 'H') opponentType = 'C';
	if (playerType == 'C') opponentType = 'H';

	// The coordinates of the key space are passed into the function. Scan the board for the opponent's dice to see if
	// any of them can occupy it.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// See if an opponents's die is occupying the space.
			if (board.isDieOn(i, j) && board.isDiePlayerType(i, j, opponentType))
			{
				// See if the die can move to the key space.
				if (canMoveToSpace(board, i, j, keySpaceRow, keySpaceColumn, opponentType))
				{
					// We need to create a problem/capture the offending die. Scan the board for the player's dice.
					for (int playerRow = 8; playerRow > 0; playerRow--)
					{
						for (int playerCol = 1; playerCol < 10; playerCol++)
						{
							// See if the player's die is occupying the space.
							if (board.isDieOn(playerRow, playerCol) && board.isDiePlayerType(playerRow,
								playerCol, playerType))
							{
								// See if the die can move to the offending die's position.
								if (canMoveToSpace(board, playerRow, playerCol, i, j, playerType))
								{
									// We can capture the die.
									dieRow = playerRow;
									dieColumn = playerCol;
									spaceRow = i;
									spaceColumn = j;
									return true;
								}
								// Otherwise, see if the die can block the path to the key space.
								// See if the offending die and key space are in the same row:
								if (keySpaceRow == i)
								{
									// If spaceColumn is less than the column of the offending die, it's left of the die:
									if (keySpaceColumn < j)
									{
										for (int a = keySpaceColumn; a < j; a++)
										{
											// If we can move to a spot between them, move there.
											if (canMoveToSpace(board, playerRow, playerCol, keySpaceRow, a, playerType))
											{
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = keySpaceRow;
												spaceColumn = a;
												return true;
											}
										}
									}
									// Otherwise, it's right of the die.
									else
									{
										for (int b = j; b > keySpaceRow; b--)
										{
											// If we can move to a spot between them, move there.
											if (canMoveToSpace(board, playerRow, playerCol, keySpaceRow, b, playerType))
											{
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = keySpaceRow;
												spaceColumn = b;
												return true;
											}
										}
									}
								}
								// See if the offending die and key space are in the same column.
								if (keySpaceColumn == j)
								{
									// If the keySpaceRow is less than i, it's below the die:
									if (keySpaceRow < i)
									{
										for (int c = keySpaceRow; c < i; c++)
										{
											// If we can move to a spot between them, move there.
											if (canMoveToSpace(board, playerRow, playerCol, c, keySpaceColumn, playerType))
											{
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = c;
												spaceColumn = keySpaceColumn;
												return true;
											}
										}
									}
									// Otherwise, it's above the die:
									else
									{
										for (int d = i; d < keySpaceRow; d--)
										{
											// If we can move to a spot between them, move there.
											if (canMoveToSpace(board, playerRow, playerCol, d, keySpaceColumn, playerType))
											{
												dieRow = playerRow;
												dieColumn = playerCol;
												spaceRow = d;
												spaceColumn = keySpaceColumn;
												return true;
											}
										}
									}
								}
								// Otherwise, try moving within the column of the key space.
								// Iteration is different depending on the row of the key space.
								if (keySpaceRow == 8)
								{
									for (int e = 1; e < keySpaceRow; e++)
									{
										// Try moving to the space.
										if (canMoveToSpace(board, playerRow, playerCol, e, keySpaceColumn, playerType))
										{
											dieRow = playerRow;
											dieColumn = playerCol;
											spaceRow = e;
											spaceColumn = keySpaceColumn;
											return true;
										}
									}
								}
								else
								{
									for (int f = keySpaceRow; f > 1; f--)
									{
										// Try moving to the space.
										if (canMoveToSpace(board, playerRow, playerCol, f, keySpaceColumn, playerType))
										{
											dieRow = playerRow;
											dieColumn = playerCol;
											spaceRow = f;
											spaceColumn = keySpaceColumn;
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// Blocking the key space from being captured is not necessary or feasible.
	return false;
}

/* *********************************************************************
Function Name: captureDieScore
Purpose: To determine if a die can be captured or not
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die that can capture the enemy
dieColumn, an integer passed by reference that will contain the column of the die that can capture the enemy die
spaceRow, an integer passed by reference that will contain the row of the enemy die
spacesColumn, an integer passed by reference that will contain the column of the enemy die
playerType, a character containing the player type of the player "calling" the function
Return Value: a boolean signifying whether or not a die capture is possible
Local Variables:
opponentType, a character used to store the player type of the opponent of the player "calling" the function
i and j, integers used to iterate through for loops
Algorithm:
1) Scan the board for the opponent's dice
2) For each die found, scan the board for the player's die
3) For each player die found, see if it can capture the opponent's die
4) If it can, store playerRow into dieRow, playerCol into dieColumn, i into spaceRow, j into spaceColumn, and return true
5) Otherwise, if nothing can be found for any of the dice, return false
Assistance Received: none
********************************************************************* */
bool Player::captureDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType)
{
	// Character to store opposing player type.
	char opponentType;
	if (playerType == 'H') opponentType = 'C';
	if (playerType == 'C') opponentType = 'H';
	// Scan the board for opponent's dice.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// See if an opponents's die is occupying the space.
			if (board.isDieOn(i, j) && board.isDiePlayerType(i, j, opponentType))
			{
				// Scan the board for dice of the player's type.
				for (int playerRow = 8; playerRow > 0; playerRow--)
				{
					for (int playerCol = 1; playerCol < 10; playerCol++)
					{
						// See if a player's die is occupying the space.
						if (board.isDieOn(playerRow, playerCol) && board.isDiePlayerType(playerRow, playerCol, playerType))
						{
							// See if that die can move to the space occupied by the enemy die. If we can, return true.
							if (canMoveToSpace(board, playerRow, playerCol, i, j, playerType))
							{
								dieRow = playerRow;
								dieColumn = playerCol;
								spaceRow = i;
								spaceColumn = j;
								return true;
							}
						}
					}
				}
			}
		}
	}
	// Moving to this space is not feasible.
	return false;
}

/* *********************************************************************
Function Name: randomMove
Purpose: To make a random move on the board
Parameters:
board, the Board that is being played on
dieRow, an integer passed by reference that will contain the row of the die to move
dieColumn, an integer passed by reference that will contain the column of the die to move
spaceRow, an integer passed by reference that will contain the row of the space to move to
spacesColumn, an integer passed by reference that will contain the column of the space to move to
playerType, a character containing the player type of the player "calling" the function
Return Value: none
Local Variables:
alreadyChecked, an array of boolean values that corresponds to rows already checked on the board
randomRow, an integer that stores a random row value
rowRolls and columnRolls, integers that store the number of spaces needed to travel from the die's space to the random space
topNum, an integer that stores the topNumber of the die
Algorithm:
1) Get a random number between 1 and 8.
2) Check the alreadyChecked array to see if that row has already been checked or not.
3) If not, search that row for one of the player's dice.
4) If there is a die there, attempt to make a random move by getting the topNum and assigning it to rowRolls.
5) Try to make the random move in every possible direction before decrementing rowRolls and incrementing columnRolls.
6) Once a move can be made, assign the appropriate values to the variables passed by reference into the function.
Assistance Received: none
********************************************************************* */
void Player::randomMove(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType)
{
	// Array of boolean values to look at whether or not that row has already been checked.
	bool alreadyChecked[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	// Integer that will store a random row value.
	int randomRow;
	// Integer that will store the row rolls and column rolls necessary to make a move.
	int rowRolls = 0, columnRolls = 0;
	// The top number of the die.
	int topNum = 0;
	// Random seed.
	srand(time(NULL));
	// We will enter a semi-permanent while loop to let this perform to the best of its ability. The function
	// returns once a move has been successfully made.
	while (1)
	{
		// Get a random number between 1 and 8.
		randomRow = rand() % 8 + 1;
		// Look in the alreadyChecked array to see if the randomly generated number's row has been checked. If not,
		// search the row.
		if (!alreadyChecked[randomRow - 1])
		{
			// Search the row to see if there are dice of the player's in it.
			for (int i = 1; i < 10; i++)
			{
				// If there is a die on the space of the playerType, attempt to make a random move.
				if (board.isDieOn(randomRow, i) && board.isDiePlayerType(randomRow, i, playerType))
				{
					// Initialize possible moves with row and column traversal.
					topNum = board.getDieTopNum(randomRow, i);
					rowRolls = topNum;
					columnRolls = 0;
					while (rowRolls > 0)
					{
						// See if a move to the coordinates of the die plus/minus (to the left/right of) the row and column
						// rolls needed to travel is possible. There will be four different ways to move.
						if (canMoveToSpace(board, randomRow, i, randomRow + rowRolls, i + columnRolls, playerType))
						{
							// A move is possible. Return the coordinates of the possible move.
							dieRow = randomRow;
							dieColumn = i;
							spaceRow = randomRow + rowRolls;
							spaceColumn = i + columnRolls;
							return;
						}
						// Try randomRow - rowRolls.
						if (canMoveToSpace(board, randomRow, i, randomRow - rowRolls, i + columnRolls, playerType))
						{
							// A move is possible. Return the coordinates of the possible move.
							dieRow = randomRow;
							dieColumn = i;
							spaceRow = randomRow - rowRolls;
							spaceColumn = i + columnRolls;
							return;
						}
						// Try i - columnRolls.
						if (canMoveToSpace(board, randomRow, i, randomRow + rowRolls, i - columnRolls, playerType))
						{
							// A move is possible. Return the coordinates of the possible move.
							dieRow = randomRow;
							dieColumn = i;
							spaceRow = randomRow + rowRolls;
							spaceColumn = i - columnRolls;
							return;
						}
						// Try randomRow - rowRolls and i - columnRolls.
						if (canMoveToSpace(board, randomRow, i, randomRow - rowRolls, i - columnRolls, playerType))
						{
							// A move is possible. Return the coordinates of the possible move.
							dieRow = randomRow;
							dieColumn = i;
							spaceRow = randomRow - rowRolls;
							spaceColumn = i - columnRolls;
							return;
						}
						// Otherwise, a move is not possible. Try different columns and rows to move by.
						rowRolls--;
						columnRolls++;
					}
				}
			}
			// Check off the row in the array, as it's now been checked.
			alreadyChecked[randomRow - 1] = true;
		}
	}
}
