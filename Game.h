// The Game class, which contains all of the components of Duell, including turns and scorekeeping.
#pragma once
#include "Tournament.h"
#include "Human.h"
#include "Computer.h"
#include "BoardView.h"
#include <iostream>
#include <fstream>
#include <sstream>
class Game
{
public:
	// Default constructor.
	Game();
	// Function that is run when the program is first booted and asks the player what they would like to do.
	int startScreen();
	// Function to set up everything for the game.
	void setUpGame();
	// Function to resume a game from a save file.
	bool resumeGame();
	// The function that actually goes through a round of Duell.
	int playRound();
	// The function that adds to the win count of the player that won the round.
	void registerWinner(int roundResult);
	// Displays the results of the tournament.
	void displayResults();
	// Destructor.
	~Game();
private:
	// The tournament for the game.
	Tournament gameTournament;
	// The board the game will be played on.
	Board gameBoard;
	// The view of the board.
	BoardView gameDisplay;
	// The players in the game.
	Human humanPlayer;
	Computer computerPlayer;
	// Pointers that point to the current and next players in the game.
	Player * currentPlayer;
	Player * nextPlayer;
	// The function that determines who gets the first move of the game.
	void determineFirstMove(Player * & currentPlayer, Player * & nextPlayer);
	// The function that finds if there is a win condition on the board.
	int checkWinCondition();
	// Saves the game to a text file.
	void saveFile();
	// Restores the board from a line of text in the text file.
	bool restoreBoard(string buff, int row);
	// Restores the player wins from a line of text in the text file.
	bool restorePlayerWins(string buff);
	// Restores the next player from the saved game to be the current player.
	bool restorePlayer(string buff);
	// The function that switches the players.
	void switchPlayers(Player * & currentPlayer, Player * & nextPlayer);
	// The function that finds if there is a key die missing on the board.
	int isKeyDieOnBoard();
};

