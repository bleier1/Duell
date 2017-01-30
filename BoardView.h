// The BoardView class that provides an ASCII visualization of the Duell board.
#pragma once
#include "Board.h"
class BoardView
{
public:
	// Default constructor.
	BoardView();
	// Constructor that takes a board passed into the parameters.
	BoardView(Board board);
	// Destructor.
	~BoardView();
	// Function that updates the display of the board.
	void updateDisplay();
	// Function that updates the board contained within the class.
	void updateBoard(Board board);
private:
	// The board that the class will be displaying.
	Board gameBoard;
};

