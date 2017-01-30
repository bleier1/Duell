// The Tournament class, which keeps score of who won how many games.
#pragma once
#include <iostream>
#include "Player.h"
using namespace std;

class Tournament
{
public:
	// Default constructor.
	Tournament();
	// Adds one point to the human's win total.
	void addHumanPoint();
	// Adds one point to the computer's win total.
	void addComputerPoint();
	// Prints the number of wins each player has.
	void printWins();
	// Returns the number of wins the human has.
	int getHumanWins() const;
	// Returns the number of wins the computer has.
	int getComputerWins() const;
	// Destructor.
	~Tournament();
private:
	// An integer that keeps track of how many wins the human has.
	int humanWins;
	// An integer that keeps track of how many wins the computer has.
	int computerWins;
};

