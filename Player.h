// The Player class, which is a base class for the Human and Computer classes to make their moves on the board.
#pragma once
#include "Board.h"
#include <stdlib.h>
#include <time.h>
class Player
{
public:
	// Default constructor.
	Player();
	// Assigns the player a name.
	void namePlayer(string name);
	// Gets the player's name.
	string getPlayerName() const;
	// The function that lets the player play the game. This differs between types of players!
	virtual void play(Board & b);
	// Destructor.
	~Player();
protected:
	// The name of the player.
	string playerName;
	// A function that makes the move that the player wants to make to the space coordinates provided in the
	// parameters.
	void makeMove(Board & b, int dieRow, int dieColumn, int spaceCoordinate, string direction);
	// A function that determines if a die can be moved to a space laterally.
	bool canMoveLaterally(Board b, int dieRow, int dieColumn, int spaceColumn, int spacesToMove, char playerType);
	// A function that determines if a die can be moved to a space frontally.
	bool canMoveFrontally(Board b, int dieRow, int dieColumn, int spaceRow, int spacesToMove, char playerType);
	// A function that determines whether or not a key die can be captured.
	bool captureKeyDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType);
	// A function that determines whether or not a key space can be captured.
	bool captureKeySpaceScore(Board board, int & dieRow, int & dieColumn, int spaceRow, int spaceColumn, char playerType);
	// A function that determines whether or not a key die should be blocked.
	bool blockKeyDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType);
	// A function that determines whether or not a key space should be blocked.
	bool blockKeySpaceScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType);
	// A function that determines whether or not a die can be captured.
	bool captureDieScore(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType);
	// A function that determines a random move for a random die.
	void randomMove(Board board, int & dieRow, int & dieColumn, int & spaceRow, int & spaceColumn, char playerType);
private:
	// A function that finds the coordinates of the key die of the player passed into the function.
	void findKeyDie(Board board, int & spaceRow, int & spaceColumn, char playerType);
	// A function that determines if a die can move to a given space.
	bool canMoveToSpace(Board board, int dieRow, int dieColumn, int spaceRow, int spaceColumn, char playerType);
};

