#include "Tournament.h"

// Default constructor.
Tournament::Tournament()
{
	// Initialize the amount of times each player has won. For a new tournament, it is 0 for both, as no games have
	// been played yet.
	humanWins = 0;
	computerWins = 0;
}

/* *********************************************************************
Function Name: addHumanPoint
Purpose: To add a point to the human wins in the tournament
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Increment humanWins by one
Assistance Received: none
********************************************************************* */
void Tournament::addHumanPoint()
{
	humanWins++;
}

/* *********************************************************************
Function Name: addComputerPoint
Purpose: To add a point to the computer wins in the tournament
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Increment computerWins by one
Assistance Received: none
********************************************************************* */
void Tournament::addComputerPoint()
{
	computerWins++;
}

/* *********************************************************************
Function Name: printWins
Purpose: To print the amount of wins each player has to the window
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Print the amount of wins the computer has in the tournament
2) Print the amount of wins the human has in the tournament
Assistance Received: none
********************************************************************* */
void Tournament::printWins()
{
	// Print out how many times the computer has won the game.
	cout << "Computer Wins: " << computerWins << endl;
	cout << endl;
	// Print out how many times the human has won the game.
	cout << "Human Wins: " << humanWins << endl << endl;
}

/* *********************************************************************
Function Name: getHumanWins
Purpose: To return the number of times the human has won a round
Parameters:
none
Return Value: an integer containing the amount of wins
Local Variables:
wins, an integer that stores the amount of wins
Algorithm:
1) Store humanWins in an integer and return that integer
Assistance Received: none
********************************************************************* */
int Tournament::getHumanWins() const
{
	int wins = humanWins;
	return wins;
}

/* *********************************************************************
Function Name: getComputerWins
Purpose: To return the number of times the computer has won a round
Parameters:
none
Return Value: an integer containing the amount of wins
Local Variables:
wins, an integer that stores the amount of wins
Algorithm:
1) Store computerWins in an integer and return that integer
Assistance Received: none
********************************************************************* */
int Tournament::getComputerWins() const
{
	int wins = computerWins;
	return wins;
}

// Destructor.
Tournament::~Tournament()
{
}
