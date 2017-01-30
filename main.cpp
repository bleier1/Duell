/***********************************************************
* Name: Bryan Leier										   *
* Project : Duell Project #1: C++						   *
* Class : CMPS 366 - Organization of Programming Languages *
* Date : October 4, 2016								   *
************************************************************/
#include "Game.h"

int main()
{
	// The entire game of Duell.
	Game duellGame;
	// Integer value to determine if the player wants to play again.
	int playAgain = 1;
	// Boot to the welcome screen. Have a variable to store what the result of the player's input is.
	int startScreenResult = duellGame.startScreen();
	// If the player wants to start a new game, start the new game.
	if (startScreenResult == 1)
	{
		// Set up the game.
		duellGame.setUpGame();
	}
	// If the player wants to resume a saved game, start loading it.
	if (startScreenResult == 2)
	{
		if (!duellGame.resumeGame())
		{
			cout << "There was an error restoring the save file. The program will now exit. Goodbye!" << endl;
			system("pause");
			return 0;
		}
	}
	// Otherwise, the player wants to exit the program.
	if (startScreenResult == 3)
	{
		cout << "The program will now exit. Goodbye!" << endl;
		system("pause");
		return 0;
	}
	// A game was started/restored. Now play the round!
	// The result of the round will be stored in an integer.
	int roundResult = 0;
	// Now play the game until the user doesn't want to play anymore.
	while (playAgain == 1)
	{
		roundResult = duellGame.playRound();
		// If roundResult is 3, the user saved the game and thus the program must quit.
		if (roundResult == 3) break;
		// Increment the winner's win total in the game's tournament.
		duellGame.registerWinner(roundResult);
		// Ask if the user wants to play again.
		cout << "Would you like to play another round?" << endl;
		cout << "Enter 1 to play again, or enter 2 to quit: ";
		cin >> playAgain;
		// If the input isn't valid, ask again.
		while (playAgain < 1 || playAgain > 2)
		{
			cout << "That is not a valid input. Please enter 1 to play again or enter 2 to quit: ";
			cin >> playAgain;
		}
		// If they want to play again, set up a new round.
		if (playAgain == 1) duellGame.setUpGame();
	}

	// Display the results of the tournament, but only if roundResult is not equal to 3 because it quit a tournament in
	// progress.
	if (roundResult != 3) duellGame.displayResults();
	cout << "The program will now exit. Goodbye!" << endl;
	system("pause");
}