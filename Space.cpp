#include "Space.h"

// Default constructor for Space.
Space::Space()
{
	hasDie = false;
}

// Constructor for Space that lets a die be placed on it.
Space::Space(Dice d)
{
	dieOnSpace = d;
	hasDie = true;
}

// Destructor for Space.
Space::~Space()
{
}

/* *********************************************************************
Function Name: placeDie
Purpose: To place a die on the space
Parameters:
d, a Dice object that will be placed onto the space
Return Value: none
Local Variables:
none
Algorithm:
1) Assign the dieOnSpace to the Dice d that is passed into the parameters, then assign hasDie to true as there is
a die on the space
Assistance Received: none
********************************************************************* */
void Space::placeDie(Dice d)
{
	dieOnSpace = d;
	// There is now a die on the space.
	hasDie = true;
}

/* *********************************************************************
Function Name: moveDie
Purpose: To move a die from one space to the other
Parameters:
s, a Space passed by parameter that will receive the die on this Space
direction, a string. it contains the direction that the die needs to roll in to reach the Space s
Return Value: none
Local Variables:
none
Algorithm:
1) Roll the die on the space in the direction specified in the parameter
2) Place the die on this space to Space s
3) Change this space's hasDie value to false as there is no longer a die on it
Assistance Received: none
********************************************************************* */
void Space::moveDie(Space & s, string direction)
{
	// First, adjust the die in the direction that it will roll.
	dieOnSpace.rollDice(direction);
	// Now call placeDie() to place the die on this space to the space passed into the function.
	s.placeDie(dieOnSpace);
	// This space no longer has a die.
	hasDie = false;
}

/* *********************************************************************
Function Name: spaceOccupied
Purpose: To determine if the space is occupied by a die or not
Parameters:
none
Return Value: a boolean true or false
Local Variables:
none
Algorithm:
1) If the Space's hasDie value is true, there is a die on the space. Return true
2) Otherwise, there is not a die. Return false
Assistance Received: none
********************************************************************* */
bool Space::spaceOccupied()
{
	if (hasDie) return true;
	return false;
}

/* *********************************************************************
Function Name: clearSpace
Purpose: To "clear" the space on the board
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) hasDie becomes false
Assistance Received: none
********************************************************************* */
void Space::clearSpace()
{
	hasDie = false;
}

/* *********************************************************************
Function Name: getDieTopNum
Purpose: To return the top number of the die on the space
Parameters:
none
Return Value: an integer that contains the top number of the die
Local Variables:
none
Algorithm:
1) Return getTopNum() from the die occupying the space
Assistance Received: none
********************************************************************* */
int Space::getDieTopNum() const
{
	return dieOnSpace.getTopNum();
}

/* *********************************************************************
Function Name: getDieRightNum
Purpose: To return the right number of the die on the space
Parameters:
none
Return Value: an integer that contains the right number of the die
Local Variables:
none
Algorithm:
1) Return getRightNum() from the die occupying the space
Assistance Received: none
********************************************************************* */
int Space::getDieRightNum() const
{
	return dieOnSpace.getRightNum();
}

/* *********************************************************************
Function Name: getDieLeftNum
Purpose: To return the left number of the die on the space
Parameters:
none
Return Value: an integer that contains the left number of the die
Local Variables:
none
Algorithm:
1) Return getLeftNum() from the die occupying the space
Assistance Received: none
********************************************************************* */
int Space::getDieLeftNum() const
{
	return dieOnSpace.getLeftNum();
}

/* *********************************************************************
Function Name: getPlayerDie
Purpose: To return the player type of the die on the space
Parameters:
none
Return Value: a character that contains the player type of the die
Local Variables:
none
Algorithm:
1) Return getPlayerType() from the die occupying the space
Assistance Received: none
********************************************************************* */
char Space::getPlayerDie() const
{
	return dieOnSpace.getPlayerType();
}
