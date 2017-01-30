#include "Human.h"

// Default constructor.
Human::Human()
{
	playerName = "Human";
}

// Constructor that gives the Human a name.
Human::Human(string name)
{
	playerName = name;
}

/* *********************************************************************
Function Name: play
Purpose: To let the human play the game of Duell
Parameters:
b, the Board that is being played on
Return Value: none
Local Variables:
helpAnswer, an integer that stores input of whether the player wants the computer's help or not
dieRow and dieColumn, integers that store input of the die that the player wishes to move
spaceRow and spaceColumn, integers that store input of the space that the player wishes to move to
isValidMove, a boolean that determines if the move the player wants to make is valid or not
frontalMove and lateralMove, booleans that store whether or not a frontal or lateral move is initially possible
secondFrontalMove and secondLateralMove, booleans that store whether or not a frontal or lateral move is possible after a
90 degree turn
rowRolls and columnRolls, integers that store how many spaces a die needs to move frontally and laterally to get to the
space
answer, a string that stores the answer of whether the player wants to initially move frontally or laterally
dieNameBefore and dieNameAfter, strings that store the names of a die before it is moved and after it is moved respectively
Algorithm:
1) Ask the player if they want to make a move or get help from the computer. Store result in helpAnswer
2) If helpAnswer is 2, call getHelp
3) Otherwise, enter a while loop to get the coordinates of the die the player wants to move and the space they want to
move to
4) Perform necessary checks for the die and space coordinates. If they do not pass, start at the beginning of the loop again
5) Perform checks to see if the die is able to move to the space without problems. If they do not pass, start at the
beginning of the loop again
6) See if the die can move laterally or frontally from its position. If it can, check to see if it can move again in a
90 degree turn. Should they pass checks, isValidMove becomes true and the move can be made
7) Get the name of the die before it is moved and store it in dieNameBefore
8) If the human is able to move in either direction at first, ask them which direction they would like to move in
9) Make the move, get the die name after it is moved, and store it in dieNameAfter
10) Call printMove() to output the move that was just made to the window
Assistance Received: none
********************************************************************* */
void Human::play(Board & b)
{
	// Integer to store the answer of whether or not the user wants help.
	int helpAnswer = 0;
	// See if the human wants help from the computer.
	while (helpAnswer != 1)
	{
		cout << "Enter 1 to make a move, or enter 2 for a recommendation from the computer: ";
		cin >> helpAnswer;
		// If the user wants to make a move, exit the while loop.
		if (helpAnswer == 1) break;
		// Otherwise, they want help.
		if (helpAnswer == 2)
		{
			getHelp(b);
		}
		// If it's anything besides 1 or 2, it is not valid input.
		else
			cout << "Invalid input, please enter a valid number for what you want to do." << endl;
	}

	// Integers of the row and column that the die the player wants to move is located at:
	int dieRow, dieColumn;
	// Integers of the row and column of the space that the player wants to move to:
	int spaceRow, spaceColumn;
	// Boolean value of whether or not the input is valid.
	bool isValidMove = false;
	// Boolean values of whether or not you can move frontally or laterally.
	bool frontalMove, lateralMove;
	// Boolean values of whether or not you can move frontally or laterally after already moving in that direction.
	bool secondFrontalMove, secondLateralMove;
	// Integers of how many rolls the die will need to get to the new space position.
	int rowRolls, columnRolls;
	// If the player is able to move their die either frontally or laterally first, they must specify which way to go first.
	string answer;
	// Strings that store the name of the die before and after being moved.
	string dieNameBefore, dieNameAfter;
	// Enter a while loop to get the coordinates of what die you want to move and where you want to move to.
	while (!isValidMove)
	{
		cout << "Enter the die you want to move in this format (without quotes): \"x y\": ";
		cin >> dieRow;
		cin >> dieColumn;
		cout << "Enter the space you want to move to in this format (without quotes): \"x y\": ";
		cin >> spaceRow;
		cin >> spaceColumn;
		// If the coordinates entered are greater than what should be accepted, don't accept them.
		if ((dieRow < 1 || dieRow > 8) || (dieColumn < 1 || dieColumn > 9))
		{
			cout << "Coordinates entered are not on the board, please enter a valid die position." << endl;
			continue;
		}
		// If they are, then check the coordinates.
		else
		{
			// If there is a die located at the position entered, and it is your die, we can move it.
			if (b.isDieOn(dieRow, dieColumn) && b.isDiePlayerType(dieRow, dieColumn, 'H')) {}
			// Otherwise, it is not a valid die position.
			else
			{
				cout << "Not a valid die position, please enter a valid die position." << endl;
				continue;
			}
		}
		// The die coordinates are valid, now let's check the space coordinates.
		// Check to see if the row entered is between 1-8 and the column entered is between 1-9.
		if ((spaceRow >= 1 && spaceRow <= 8) && (spaceColumn >= 1 && spaceColumn <= 9))
		{
			// Now check to see if there is a die on the space.
			if (b.isDieOn(spaceRow, spaceColumn))
			{
				// If the die on the space is not one of the other player's, it's not a valid move.
				if (!b.isDiePlayerType(spaceRow, spaceColumn, 'C'))
				{
					cout << "There is already a die on that space. Please enter a valid space position." << endl;
					continue;
				}
				// Otherwise, it's an opponent's dice, and you can move there.
			}
		}
		else
		{
			cout << "Not valid space coordinates, please enter a valid space position." << endl;
			continue;
		}

		// Check to see if the number on the top of the die allows for you to move to the space you want to go to.
		int spacesToMove = b.getDieTopNum(dieRow, dieColumn);
		// These integers are the number of rolls it takes to change from the die position to the space position.
		rowRolls = abs(spaceRow - dieRow);
		columnRolls = abs(spaceColumn - dieColumn);
		// If both of these numbers added together are not equal to the number on top of the die, you cannot move to
		// that space.
		if (rowRolls + columnRolls != spacesToMove)
		{
			cout << "The number on the top of the die is not enough to move to the space, please enter a different position." << endl;
			continue;
		}

		// Everything has passed checks so far, so let's get the number on the top of the die for the amount of spaces we
		// can move.
		// Check to see if the die can be rolled laterally or frontally. These checks will only be performed if
		// the die position is valid.
		lateralMove = canMoveLaterally(b, dieRow, dieColumn, spaceColumn, spacesToMove, 'H');
		frontalMove = canMoveFrontally(b, dieRow, dieColumn, spaceRow, spacesToMove, 'H');
		// If you cannot move either way, it is not a valid space coordinate to move to.
		if (!lateralMove && !frontalMove)
		{
			isValidMove = false;
		}
		// If you can move laterally to a space (at first), that does not mean you are also able to move frontally.
		// If you cannot make it to the space you want to get to because there is a die in the way and the remaining
		// number of spaces to travel is not 0, you cannot travel to that space.
		if (lateralMove)
		{
			if (!canMoveFrontally(b, dieRow, spaceColumn, spaceRow, rowRolls, 'H') && rowRolls != 0)
			{
				secondFrontalMove = false;
			}
			else
			{
				secondFrontalMove = true;
			}
		}
		// Same for frontal rolls. If you can move frontally (at first) but you cannot move laterally afterwards and
		// the remaining number of spaces to travel is not 0, you cannot travel to that space.
		if (frontalMove)
		{
			if (!canMoveLaterally(b, spaceRow, dieColumn, spaceColumn, columnRolls, 'H') && columnRolls != 0)
			{
				secondLateralMove = false;
			}
			else
			{
				secondLateralMove = true;
			}
		}

		// Check the boolean values for moves.
		if ((frontalMove && secondLateralMove) || (lateralMove && secondFrontalMove))
			// The move is valid.
			isValidMove = true;

		// If the space coordinates are not valid, ask to enter a different pair of coordinates.
		if (!isValidMove)
			cout << "The die cannot be rolled to that space from its position. Please enter a different space." << endl;
	}

	// We can make a move. Get the name of the die that we are moving so we can output it later.
	dieNameBefore = b.getDieName(dieRow, dieColumn);

	// If you can move frontally or laterally first, ask which direction to go in first.
	if ((lateralMove && secondFrontalMove) && (frontalMove && secondLateralMove))
	{
		// If the user provides an answer not recognized, ask again with a while loop.
		while (answer != "frontally" && answer != "laterally")
		{
			cout << "Which direction do you want to go in first? Type \"frontally\" or \"laterally\": ";
			cin >> answer;
			// If "frontally," move frontally first and then laterally.
			if (answer == "frontally")
			{
				makeMove(b, dieRow, dieColumn, spaceRow, "frontally");
				makeMove(b, spaceRow, dieColumn, spaceColumn, "laterally");
				// Get the new name of the die.
				dieNameAfter = b.getDieName(spaceRow, spaceColumn);
				// Print the move that was just made.
				printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "frontally");
				// No further moves necessary.
				return;
			}
			// Otherwise, move laterally first.
			else if (answer == "laterally")
			{
				makeMove(b, dieRow, dieColumn, spaceColumn, "laterally");
				makeMove(b, dieRow, spaceColumn, spaceRow, "frontally");
				// Get the new name of the die.
				dieNameAfter = b.getDieName(spaceRow, spaceColumn);
				// Print the move that was just made.
				printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "laterally");
				// No further moves necessary.
				return;
			}
			// Input is not recognized.
			else
				cout << "Direction not recognized, please reenter which way you want to go." << endl;
		}
	}
	// If you can move frontally but not laterally, only move frontally.
	if (frontalMove && secondLateralMove)
	{
		makeMove(b, dieRow, dieColumn, spaceRow, "frontally");
		makeMove(b, spaceRow, dieColumn, spaceColumn, "laterally");
		// Get the new name of the die.
		dieNameAfter = b.getDieName(spaceRow, spaceColumn);
		// Print the move that was just made.
		printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "frontally");
	}
	// If you can move laterally but not frontally, only move laterally.
	if (lateralMove && secondFrontalMove)
	{
		makeMove(b, dieRow, dieColumn, spaceColumn, "laterally");
		makeMove(b, dieRow, spaceColumn, spaceRow, "frontally");
		// Get the new name of the die.
		dieNameAfter = b.getDieName(spaceRow, spaceColumn);
		// Print the move that was just made.
		printMove(dieNameBefore, dieNameAfter, dieRow, dieColumn, spaceRow, spaceColumn, "laterally");
	}
}

// Destructor.
Human::~Human()
{
}

/* *********************************************************************
Function Name: printMove
Purpose: To print the move that was just made by the human to the window
Parameters:
dieNameBefore, a string containing the name of the die before it was moved
dieNameAfter, a string containing the name of the die after it was moved
dieRow, an integer containing the row of the die before it was moved
dieColumn, an integer containing the column of the die before it was moved
spaceRow, an integer containing the row of the die after it was moved
spaceColumn, an integer containing the column of the die after it was moved
direction, a string that stores the direction that the die first moved in
Return Value: none
Local Variables:
rowRolls and columnRolls, integers that store the amount of spaces that the die needed to move frontally and laterally
Algorithm:
1) Calculate the rowRolls and columnRolls needed to move
2) Print the name of the die before it was moved and where it originally was
3) Use the direction passed into the function to determine how the die was first moved.
4) Check if there was a 90 degree turn that was made by looking at rowRolls and columnRolls. If greater than 0, print
the number of spaces moved
5) Print the rest of the sentence: the name of the die after it was moved and where it is now located
Assistance Received: none
********************************************************************* */
void Human::printMove(string dieNameBefore, string dieNameAfter, int dieRow, int dieColumn, int spaceRow,
int spaceColumn, string direction)
{
	// Integers to store the spaces traversed in each row and column.
	int rowRolls = abs(spaceRow - dieRow);
	int columnRolls = abs(spaceColumn - dieColumn);
	// Start by printing out the name of the die before it was moved.
	cout << dieNameBefore << " was rolled from square (" << dieRow << "," << dieColumn << ") ";
	// Use the direction passed into the function to determine how the die was rolled.
	// If it was rolled frontally, display so.
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
	// Display the rest of the sentence.
	cout << " to square (" << spaceRow << "," << spaceColumn << "). The die is now " << dieNameAfter << "." << endl;
}

/* *********************************************************************
Function Name: getHelp
Purpose: To get help from the computer on a move recommendation
Parameters:
board, the Board that is being played on
Return Value: none
Local Variables:
dieRow and dieColumn, integers that store the coordinates of the die to move
spaceRow and spaceColumn, integers that store the coordinates of the space to move to
Algorithm:
1) Call each score function in Player to help determine a move
2) First try to see if a key die can be captured. If so, recommend the move
3) Then try to see if a key space can be captured. If so, recommend the move
4) Then try to see if the human's key die needs to be blocked. If so, recommend the move
5) Then try to see if the human's key space needs to be blocked. If so, recommend the move
6) Then try to see if an enemy die can be captured. If so, recommend the move
7) Otherwise, just recommend a random move
Assistance Received: none
********************************************************************* */
void Human::getHelp(Board board)
{
	// Variables to initialize so the computer can properly make a suggestion:
	int dieRow = 0, dieColumn = 0, spaceRow = 0, spaceColumn = 0;
	// The computer will determine which of the human's dice that it could move. It needs to check for certain scenarios
	// to make the appropriate move. This is actually quite similar to how Computer.play() works, but it does not actually
	// make moves.
	// The key die results in an immediate win, so find where the human's key die is. If it can be captured, do it.
	if (captureKeyDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'H'))
	{
		// Recommend a move to capture the key die.
		recommendMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "keyDieCapture");
		return;
	}
	// Key space capture results in a win as well, so see if the human can travel to it.
	if (captureKeySpaceScore(board, dieRow, dieColumn, 8, 5, 'H'))
	{
		// Recommend a move to capture the key space.
		recommendMove(board, dieRow, dieColumn, 8, 5, "keySpaceCapture");
		return;
	}
	// The computer must also make moves to play defensively if it detects that the human could possibly win.
	// If a human's die is close to the computer's key die, block the capture or move the die.
	if (blockKeyDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'H'))
	{
		// Recommend a move to block key die capture.
		recommendMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "blockKeyDie");
		return;
	}
	// If a human's die is close to the computer's key space, block the capture or move the die.
	// Assign spaceRow and spaceColumn as the computer's key space coordinates.
	spaceRow = 1;
	spaceColumn = 5;
	if (blockKeySpaceScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'H'))
	{
		// Recommend a move to block key space capture.
		recommendMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "blockKeySpace");
		return;
	}
	// If the code flow is at this point, there's no reason to play defensively. Seek a die to capture.
	if (captureDieScore(board, dieRow, dieColumn, spaceRow, spaceColumn, 'H'))
	{
		// Recommend a move to capture the enemy die.
		recommendMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "dieCapture");
		return;
	}
	// Otherwise, random move.
	else
	{
		// Find a random move to make.
		randomMove(board, dieRow, dieColumn, spaceRow, spaceColumn, 'H');
		// Recommend the move.
		recommendMove(board, dieRow, dieColumn, spaceRow, spaceColumn, "random");
	}
}

/* *********************************************************************
Function Name: recommendMove
Purpose: To print the move recommendation from the computer
Parameters:
board, the Board that is being played on
dieRow, an integer that contains the row of the die to move
dieColumn, an integer that contains the column of the die to move
spaceRow, an integer that contains the row of the space to move to
spaceColumn, an integer that contains the column of the space to move to
strategy, a string that contains the strategy the computer is recommending
Return Value: none
Local Variables:
spacesToMove, an integer that stores the top number of the die located at (dieRow,dieColumn)
rowRolls and columnRolls, integers that store the amount of spaces needed to move frontally and laterally to the space
frontalMove and lateralMove, boolean values that store whether or not a frontal or lateral move is initially possible
secondFrontalMove and secondLateralMove, boolean values that store whether or not a frontal or lateral move is possible
after a potential 90 degree turn
Algorithm:
1) Store the result of getDieTopNum in spacesToMove
2) Calculate the rowRolls and columnRolls needed to move to (spaceRow,spaceColumn)
3) Start printing the recommendation using getDieName to get the name of the die to move.
4) Print the recommendation that goes with the strategy passed in the parameters.
5) Use canMoveFrontally and canMoveLaterally to determine how the die can be moved and print how the human can move it.
6) Print the reason for moving the die in that direction using the strategy passed in the parameters.
Assistance Received: none
********************************************************************* */
void Human::recommendMove(Board board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, string strategy)
{
	// The spaces to move the die.
	int spacesToMove = board.getDieTopNum(dieRow, dieColumn);
	// The amount of spaces needed to traverse to the given coordinates.
	int rowRolls = abs(spaceRow - dieRow);
	int columnRolls = abs(spaceColumn - dieColumn);
	// Boolean values for frontal and lateral moves.
	bool frontalMove = false, lateralMove = false, secondFrontalMove = false, secondLateralMove = false;
	// Random seed.
	srand(time(NULL));

	// Start printing the recommendation.
	cout << "The computer recommends moving " << board.getDieName(dieRow, dieColumn) << " at (" << dieRow << "," <<
		dieColumn << ") because ";
	// Look at the strategy passed into the function.
	if (strategy == "keyDieCapture")
		// The die picked was within reach of the key die.
		cout << "it is within distance of the computer's key die." << endl;
	if (strategy == "keySpaceCapture")
		// The die picked was within reach of the key space, and that is why it was moved.
		cout << "it is within distance of the computer's key space." << endl;
	if (strategy == "blockKeyDie")
		// The die picked was needed to block a key die capture.
		cout << "the key die is in danger of being captured, and the capture needs to be blocked." << endl;
	if (strategy == "blockKeySpace")
		// The die picked was needed to block a key space capture.
		cout << "the key space in danger of being captured, and the capture needs to be blocked." << endl;
	if (strategy == "dieCapture")
		// The die picked was within reach of an enemy die that could be captured.
		cout << "it is within distance of a computer's die that is able to be captured." << endl;
	if (strategy == "random")
		// Random move.
		cout << "the computer could not determine a decisive move to make, so it is making a move at random." << endl;

	// Start printing the rest of the recommendation.
	cout << "It recommends rolling ";

	// Determine if the die can be moved frontally or laterally from the die's coordinates.
	frontalMove = canMoveFrontally(board, dieRow, dieColumn, spaceRow, spacesToMove, 'H');
	lateralMove = canMoveLaterally(board, dieRow, dieColumn, spaceColumn, spacesToMove, 'H');
	// Determine if the die can be moved frontally or laterally after a 90 degree turn.
	if (frontalMove)
	{
		// If you can move frontally (at first) but you cannot move laterally afterwards and
		// the remaining number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveLaterally(board, spaceRow, dieColumn, spaceColumn, columnRolls, 'H') && columnRolls != 0)
			secondLateralMove = false;
		// Otherwise, a second move is possible.
		else secondLateralMove = true;
	}
	if (lateralMove)
	{
		// If you can move laterally (at first) but you cannot move frontally afterwards and the remaining
		// number of spaces to travel is not 0, you cannot travel to that space.
		if (!canMoveFrontally(board, dieRow, spaceColumn, spaceRow, rowRolls, 'H') && rowRolls != 0)
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
			// Recommend to move frontally and not laterally.
			lateralMove = false;
		}
		else
		{
			// Recommend to move laterally and not frontally.
			frontalMove = false;
		}

	}
	// If we can move frontally, make the move.
	if (frontalMove && secondLateralMove)
	{
		// Start printing the move recommendation.
		cout << "frontally by " << rowRolls;
		// If you can also move laterally, describe that as well.
		if (columnRolls != 0)
			cout << " and laterally by " << columnRolls;
	}
	if (lateralMove && secondFrontalMove)
	{
		// Start printing the move recommendation.
		cout << "laterally by " << columnRolls;
		// If you can also move laterally, describe that as well.
		if (rowRolls != 0)
			cout << " and frontally by " << rowRolls;
	}

	// Start printing the rest of the sentence.
	cout << " because ";

	// Look at the strategy passed into the function once more.
	if (strategy == "keyDieCapture")
		// The die picked was within reach of the key die.
		cout << "it can capture the key die with this move." << endl;
	if (strategy == "keySpaceCapture")
		// The die picked was within reach of the key space, and that is why it was moved.
		cout << "it can capture the key space with this move." << endl;
	if (strategy == "blockKeyDie")
		// The die picked was needed to block a key die capture.
		cout << "the key die capture will be blocked with this move." << endl;
	if (strategy == "blockKeySpace")
		// The die picked was needed to block a key space capture.
		cout << "the key space capture will be blocked with this move." << endl;
	if (strategy == "dieCapture")
		// The die picked was within reach of an enemy die that could be captured.
		cout << "the die will be captured with this move." << endl;
	if (strategy == "random")
		// Random move.
		cout << "the die is able to move this way without any problems." << endl;
}
