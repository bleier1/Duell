// The Human class, which lets the user play the game of Duell using inputs and input validation.
#pragma once
#include "Player.h"
#include <iostream>
using namespace std;

class Human :
	public Player
{
public:
	// Default constructor.
	Human();
	// Constructor that gives the Human a name.
	Human(string name);
	// play() function is different for a human than it is for a computer.
	void play(Board & b);
	// Destructor.
	~Human();
private:
	// Outputs the move that was just made.
	void printMove(string dieNameBefore, string dieNameAfter, int dieRow, int dieColumn, int spaceRow, int spaceColumn,
	string direction);
	// Gets help from the computer.
	void getHelp(Board board);
	// Prints the recommendation.
	void recommendMove(Board board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, string strategy);
};

