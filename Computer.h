// The Computer class, which implements how the computer will play Duell against the human.
#pragma once
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
class Computer :
	public Player
{
public:
	// Default constructor.
	Computer();
	// The play() function that the computer uses to play Duell.
	void play(Board & board);
	// Destructor.
	~Computer();
private:
	// Function that the computer uses to make its move.
	void computerMakesMove(Board & board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, string strategy);
	// Function that prints the move and strategy that the computer uses.
	void printMove(string dieNameBefore, string dieNameAfter, int dieRow, int dieColumn, int spaceRow, int spaceColumn,
	string direction, string strategy);
};

