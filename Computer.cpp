#include "Computer.h"

// Default constructor.
Computer::Computer()
{
	// Give the computer its name.
	playerName = "Computer";
}

/* *********************************************************************
Function Name: play
Purpose: To let the computer play the game of Duell
Parameters:
board, the Board that is being played on
Return Value: none
Local Variables:
dieRow and dieColumn, integers that store the coordinates of the die to be moved
spaceRow and spaceColumn, integers that store the coordinates of the space to move to
Algorithm:
1) Use the score functions in Player to determine which move to make
2) Check if a key die can be captured. If so, make the move
3) Check if a key space can be captured. If so, make the move
4) Check if the key die needs to be blocked. If so, make the move
5) Check if the key space needs to be blocked. If so, make the move
6) Check if a die can be captured. If so, make the move
7) Otherwise, make a random move
Assistance Received: none
********************************************************************* */
void Computer::play(Board & board)
{
	// Variables to initialize so the computer can properly make its move:
	int dieRow = 0, dieColumn = 0, spaceRow = 0, spaceColumn = 0;
	// The computer needs to decide which die to move. For this, it will look to see if specific scenarios are true or not.
	// The key die results in an immediate win, so find where the human's key die is. If it can be captured, do it.
	if (captureKeyDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'C'))
	{
		// Make the move to capture the key die.
		computerMakesMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "keyDieCapture");
		return;
	}
	// Key space capture results in a win as well, so see if the computer can travel to it.
	if (captureKeySpaceScore(board, dieRow, dieColumn, 1, 5, 'C'))
	{
		// Make the move to capture the key space.
		computerMakesMove(board, dieRow, dieColumn, 1, 5, "keySpaceCapture");
		return;
	}
	// The computer must also make moves to play defensively if it detects that the human could possibly win.
	// If a human's die is close to the computer's key die, block the capture or move the die.
	if (blockKeyDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'C'))
	{
		// Make the move to play defensively.
		computerMakesMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "blockKeyDie");
		return;
	}
	// If a human's die is close to the computer's key space, block the capture or move the die.
	// Assign spaceRow and spaceColumn as the computer's key space coordinates.
	spaceRow = 8;
	spaceColumn = 5;
	if (blockKeySpaceScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'C'))
	{
		// Make the move to play defensively.
		computerMakesMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "blockKeySpace");
		return;
	}
	// If the code flow is at this point, there's no reason to play defensively. Seek a die to capture.
	if (captureDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'C'))
	{
		// Capture the die.
		computerMakesMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "dieCapture");
		return;
	}
	// Otherwise, random move.
	else
	{
		// Randomly move a die to random coordinates.
		randomMove(board, dieRow, dieColumn, spaceRow, spaceColumn, 'C');
		// Make the move.
		computerMakesMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "random");
	}
}

// Destructor.
Computer::~Computer()
{
}

/* *********************************************************************
Function Name: computerMakesMove
Purpose: To perform the move that the computer wants to make
Parameters:
board, the Board that is being played on
dieRow, an integer containing the row of the die the computer wants to move
dieColumn, an integer containing the column of the die the computer wants to move
spaceRow, an integer containing the row of the space the computer wants to move to
spaceColumn, an integer containing the column of the space the computer wants to move to
strategy, a string containing the strategy the computer is using to make the move
Return Value: none
Local Variables:
spacesToMove, an integer containing the number on the top of the die to be moved
frontalMove and lateralMove, booleans that store whether or not a frontal or lateral move is initially possible
secondFrontalMove and secondLateralMove, booleans that store whether or not a frontal or lateral move is possible after a
90 degree turn
rowRolls and columnRolls, integers that store how many spaces a die needs to move frontally and laterally to get to the
space
dieNameBefore and dieNameAfter, strings that store the name of the die before and after it is moved
Algorithm:
1) Store the result of getDieTopNum() in spacesToMove.
2) Calculate the rowRolls and columnRolls needed to move to the space.
3) Store the name of the die before it is moved into dieNameBefore.
4) Determine if the die can be moved frontally or laterally from the die coordinates, then again after a 90 degree turn.
5) If both a frontal or lateral move is initially possible, choose which way to go at random.
6) Make the move.
7) Store the name of the die after it is moved into dieNameAfter.
8) Call printMove() to print the move the computer just made to the window.
Assistance Received: none
********************************************************************* */
void Computer::computerMakesMove(Board & board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, string strategy)
{
	// The spaces to move the die.
	int spacesToMove = board.getDieTopNum(dieRow, dieColumn);
	// The amount of spaces needed to traverse to the given coordinates.
	int rowRolls = abs(spaceRow - dieRow);
	int columnRolls = abs(spaceColumn - dieColumn);
	// Boolean values for frontal and lateral moves.
	bool frontalMove = false, lateralMove = false, secondFrontalMove = false, secondLateralMove = false;
	// String values for the die name before and after it's moved.
	string dieNameBefore = board.getDieName(dieRow, dieColumn), dieNameAfter;
	// Random seed.
	srand(time(NULL));
	// Determine if the die can be moved frontally or laterally from the die's coordinates.
	frontalMove = canMoveFrontally(board, dieRow, dieColumn, spaceRow, spacesToMove, 'C');
	lateralMove = canMoveLaterally(board, dieRow, dieColumn, spaceColumn, spacesToMove, 'C');
	// Determine if the die can be moved frontally or laterally after a 90 degree turn.
	if (frontalMove)
	{
		// If you can move frontally (at first) but you cannot move laterally afterwards and
		// the remaining number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveLaterally(board, spaceRow, dieColumn, spaceColumn, columnRolls, 'C') && columnRolls != 0)
			secondLateralMove = false;
		// Otherwise, a second move is possible.
		else secondLateralMove = true;
	}
	if (lateralMove)
	{
		// If you can move laterally (at first) but you cannot move frontally afterwards and the remaining
		// number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveFrontally(board, dieRow, spaceColumn, spaceRow, rowRolls, 'C') && rowRolls != 0)
			secondFrontalMove = false;
		// Otherwise, a second move is possible.
		else secondFrontalMove = true;
	}
	// Check if both ways are possible. If so, the computer will randomly decide if it wants to move laterally or frontally.
	if ((frontalMove && secondLateralMove) && (lateralMove && secondFrontalMove))
	{
		// Generate the number 0 or 1 randomly. 0 will be a frontal move, and 1 will be a lateral move.
		int decision = rand() % 2;
		if (decision == 0)
		{
			// Make the move.
			makeMove(board, dieRow, dieColumn, spaceRow, "frontally");
			makeMove(board, spaceRow, dieColumn, spaceColumn, "laterally");
			// Get the name of the die after it is moved.
			dieNameAfter = board.getDieName(spaceRow, spaceColumn);
			// Print the computer's move.
			printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "frontally", strategy);
			return;
		}
		else
		{
			// Make the move.
			makeMove(board, dieRow, dieColumn, spaceColumn, "laterally");
			makeMove(board, dieRow, spaceColumn, spaceRow, "frontally");
			// Get the name of the die after it is moved.
			dieNameAfter = board.getDieName(spaceRow, spaceColumn);
			// Print the computer's move.
			printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "laterally", strategy);
			return;
		}
	}
	// If we can move frontally, make the move.
	if (frontalMove && secondLateralMove)
	{
		// Make the move.
		makeMove(board, dieRow, dieColumn, spaceRow, "frontally");
		makeMove(board, spaceRow, dieColumn, spaceColumn, "laterally");
		// Get the name of the die after it is moved.
		dieNameAfter = board.getDieName(spaceRow, spaceColumn);
		// Print the computer's move.
		printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "frontally", strategy);
		return;
	}
	if (lateralMove && secondFrontalMove)
	{
		// Make the move.
		makeMove(board, dieRow, dieColumn, spaceColumn, "laterally");
		makeMove(board, dieRow, spaceColumn, spaceRow, "frontally");
		// Get the name of the die after it is moved.
		dieNameAfter = board.getDieName(spaceRow, spaceColumn);
		// Print the computer's move.
		printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "laterally", strategy);
	}
}

/* *********************************************************************
Function Name: printMove
Purpose: To print the move the computer made to the window
Parameters:
dieNameBefore, a string containing the name of the die before it was moved
dieNameAfter, a string containing the name of the die after it was moved
dieRow, an integer containing the row of the die before it was moved
dieColumn, an integer containing the column of the die before it was moved
spaceRow, an integer containing the row of the die after it was moved
spaceColumn, an integer containing the column of the die after it was moved
direction, a string containing the direction the die initially moved in
strategy, a string containing the strategy the computer used to make the move
Return Value: none
Local Variables:
rowRolls and columnRolls, integers used to store the amount of spaces needed to move frontally and laterally to the space
Algorithm:
1) Calculate the rowRolls and columnRolls needed to make the move.
2) Print the name and coordinates of the die before it was moved.
3) Use strategy to print the reasoning that the computer used to make the move.
4) Print the direction that the computer rolled the die in and by how many spaces. Also print whether or not a 90 degree
turn was made or not.
5) Use strategy to print the reasoning of why the die was rolled where it was rolled to.
6) Print the new name of the die and where it is now located.
Assistance Received: none
********************************************************************* */
void Computer::printMove(string dieNameBefore, string dieNameAfter, int dieRow, int dieColumn, int spaceRow,
	int spaceColumn, string direction, string strategy)
{
	// Determine how many spaces the die was rolled frontally and laterally.
	int rowRolls = abs(spaceRow - dieRow);
	int columnRolls = abs(spaceColumn - dieColumn);
	
	// Start printing out the sentence that describes the move.
	cout << "The computer picked " << dieNameBefore << " at (" << dieRow << "," << dieColumn << ") to roll because ";

	// The strategy is passed into the parameters from the score function that determines the strategy.
	if (strategy == "keyDieCapture")
		// The die picked was within reach of the key die, and that is why it was moved.
		cout << "it was within distance of the human's key die." << endl;
	if (strategy == "keySpaceCapture")
		// The die picked was within reach of the key space, and that is why it was moved.
		cout << "it was within distance of the human's key space." << endl;
	if (strategy == "blockKeyDie")
		// The die picked was needed to block a key die capture.
		cout << "the key die was in danger of being captured, and the capture needed to be blocked." << endl;
	if (strategy == "blockKeySpace")
		// The die picked was needed to block a key space capture.
		cout << "the key space was in danger of being captured, and the capture needed to be blocked." << endl;
	if (strategy == "dieCapture")
		// The die picked was within reach of an enemy die that could be captured.
		cout << "it was within distance of a human's die that was able to be captured." << endl;
	if (strategy == "random")
		// Random move.
		cout << "the computer could not determine a decisive move to make, so it is making a move at random." << endl;

	// Continue to print the computer's move.
	cout << "It rolled it ";

	// Now print how the die was rolled. Use the direction passed into the function to determine how the die was rolled.
	if (direction == "frontally")
	{
		cout << "frontally by " << rowRolls;
		// If columnRolls is not 0, it was then rolled laterally. Display that roll as well.
		if (columnRolls != 0)
		{
			cout << " and laterally by " << columnRolls;
		}
	}
	// Otherwise, it was rolled laterally.
	else
	{
		cout << "laterally by " << columnRolls;
		// If rowRolls is not 0, it was then rolled frontally. Display that roll as well.
		if (rowRolls != 0)
		{
			cout << " and frontally by " << rowRolls;
		}
	}
	
	// Print the rest of the sentence depending on the strategy.
	cout << " because ";

	if (strategy == "keyDieCapture")
		// The die picked was able to capture the key die.
		cout << "those movements allowed it to move to the coordinates of the key die." << endl;
	if (strategy == "keySpaceCapture")
		// The die picked was able to cpature the key space.
		cout << "those movements allowed it to move to the coordinates of the key space." << endl;
	if (strategy == "blockKeyDie")
		// The die picked blocked a key die capture.
		cout << "those movements were able to block a key die capture." << endl;
	if (strategy == "blockKeySpace")
		// The die picked blocked a key space capture.
		cout << "those movements were able to block a key space capture." << endl;
	if (strategy == "dieCapture")
		// The die picked was able to capture an enemy die.
		cout << "those movements allowed it to move to the coordinates of the die it wants to capture." << endl;
	if (strategy == "random")
		// Random move.
		cout << "the die was able to move that way without any problems." << endl;

	// Finish up the statement.
	cout << "The die is now " << dieNameAfter << " at (" << spaceRow << "," << spaceColumn << ")." << endl;
}
