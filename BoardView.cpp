#include "BoardView.h"
#include <iostream>

// Default constructor.
BoardView::BoardView()
{
	
}

// Constructor that takes a board passed into the parameters.
BoardView::BoardView(Board board)
{
	gameBoard = board;
}

// Destructor.
BoardView::~BoardView()
{
}

/* *********************************************************************
Function Name: updateDisplay
Purpose: To update the display of the Board contained in the class to the window
Parameters:
none
Return Value: none
Local Variables:
integers col, i, and j, which are used in for loops to help iterate through the board and create the appropriate display
Algorithm:
1) Output the column numbers on the board using a for loop
2) Use two for loops to iterate through the board, with the first loop outputting the row numbers before what is contained
in each row
3) If there is a die on the space of the coordinates being visited in the for loop, output the name. Otherwise output 0
Assistance Received: none
********************************************************************* */
void BoardView::updateDisplay()
{
	// Use a for loop to initialize the column numbers of the board.
	// Properly indent the column numbers first...
	cout << "\t";
	for (int col = 1; col < 10; col++)
	{
		cout << col << "\t";
	}
	cout << endl;
	// Use a for loop to iterate through each of the spaces on the board.
	for (int i = 8; i > 0; i--)
	{
		// Display the row number next to the row.
		cout << i << "\t";
		for (int j = 1; j < 10; j++)
		{
			// If there is a die on the space, print its name.
			if (gameBoard.isDieOn(i, j)) cout << gameBoard.getDieName(i,j) << "\t";
			// Otherwise, the space is empty.
			else cout << "0\t";
		}
		cout << endl;
	}
}

/* *********************************************************************
Function Name: updateBoard
Purpose: To update the board contained in the class
Parameters:
board, the Board that needs to be displayed to the window
Return Value: none
Local Variables:
none
Algorithm:
1) Assign the gameBoard value in the class to the Board in the parameters
Assistance Received: none
********************************************************************* */
void BoardView::updateBoard(Board board)
{
	gameBoard = board;
}
