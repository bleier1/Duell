#include "Game.h"

// Default constructor.
Game::Game()
{
	
}

/* *********************************************************************
Function Name: startScreen
Purpose: To display the start of the program and see what the user wants to do
Parameters:
none
Return Value: an integer that represents what the player wants to do
Local Variables:
userInput, an integer that stores the user's answer to the start screen's squestion
Algorithm:
1) Print the name of the game
2) Ask the user if they would like to begin a new game, continue a saved game, or quit the program
3) Accept input until the input is valid
4) Return the number that the user inputs
Assistance Received: none
********************************************************************* */
int Game::startScreen()
{
	// Number input that signifies what the user wants to do upon booting the program.
	int userInput = 0;
	// Print a welcome message.
	cout << "Duell! The Game of Champions!" << endl;
	cout << endl;
	// Ask the user what they want to do.
	cout << "What would you like to do? Enter the corresponding number to make your decision:" << endl;
	cout << "1: Begin a new game" << endl;
	cout << "2: Continue a saved game" << endl;
	cout << "3: Quit the game" << endl;
	// Enter a while loop to let the player decide what they want to do.
	while (userInput < 1 || userInput > 3)
	{
		cin >> userInput;
		// Check for valid input.
		if (userInput < 1 || userInput > 3)
		{
			// If not, ask again.
			cout << "Input not recognized. Please enter a corresponding number to the options above: ";
		}
	}
	// Return the corresponding number to what the player wants to do.
	if (userInput == 1) return 1;
	if (userInput == 2) return 2;
	return 3;
}

/* *********************************************************************
Function Name: setUpGame
Purpose: To set up a fresh new game of Duell
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Call setUpDice() to set up the dice on the board in the appropriate starting positions
2) Call updateBoard() to update the BoardDisplay object
3) Determine who goes first in the game using determineFirstMove()
Assistance Received: none
********************************************************************* */
void Game::setUpGame()
{
	// Clear the dice on the board.
	gameBoard.clearBoard();
	// Set up the dice on the board.
	gameBoard.setUpDice();
	// Update the BoardView.
	gameDisplay.updateBoard(gameBoard);
	// Determine who goes first.
	determineFirstMove(currentPlayer, nextPlayer);
}

/* *********************************************************************
Function Name: resumeGame
Purpose: To resume a game that was saved to a text file
Parameters:
none
Return Value: a boolean that stores whether or not the game was successfully restored
Local Variables:
filename, a string that stores the filename of the text file to restore from
textFile, an ifstream that contains the text file to be read from
lineBuff, a string that stores a line in a text file
Algorithm:
1) Ask the user for the filename of the text file they want to restore their game from
2) Append .txt to the end of the filename
3) Try opening the file. If the file cannot be opened, there is an error. Return false
4) Read the first line of the file. If it is not "Board:" it is an invalid file. Return false
5) Continue reading the next 8 lines, which should be the rows of the board. Call restoreBoard() for each row
6) Get the next couple of lines, skipping over a blank line. Call restorePlayerWins() on the most recent line to restore
computer wins
7) Get the next couple of lines, skipping over a blank line. Call restorePlayerWins() on the most recent line to restore
human wins
8) Get the next couple of lines, skipping over a blank line. Call restorePlayer() on the most recent line to restore
the next player of the game
9) Close the file, update the BoardView, and return true
Assistance Received: none
********************************************************************* */
bool Game::resumeGame()
{
	// String that stores the name of the text file that will be read from.
	string filename;

	// Ask the user for the filename.
	cout << "Please enter the name of the file you want to read from (without .txt): ";
	cin >> filename;
	// Append ".txt" to the end of it.
	filename += ".txt";

	// The file to be read from.
	ifstream textFile(filename);
	// Buffer to store the line from the text file.
	string lineBuff;

	// Try opening the file.
	if (textFile.is_open())
	{
		// Read the first line of the file.
		getline(textFile, lineBuff);
		// The very first line should be "Board:", if it is not, it is an invalid file and thus must return an error.
		if (lineBuff != "Board:") return false;

		// Continue reading lines from the files. The next 8 lines should be the board spaces.
		for (int i = 8; i > 0; i--)
		{
			getline(textFile, lineBuff);
			// If the board is unable to be restored, return false for an error.
			if (!restoreBoard(lineBuff, i)) return false;
		}

		// Get the next couple lines. Skip over one because it will be blank.
		getline(textFile, lineBuff);
		getline(textFile, lineBuff);
		// Restore the amount of wins for the computer.
		if (!restorePlayerWins(lineBuff)) return false;
		// Get the next couple lines. Skip over one because it will be blank.
		getline(textFile, lineBuff);
		getline(textFile, lineBuff);
		// Restore the amount of wins for the human.
		if (!restorePlayerWins(lineBuff)) return false;
		// Get the next couple lines. Skip over one because it will be blank.
		getline(textFile, lineBuff);
		getline(textFile, lineBuff);
		// Assign the next player to be the current player.
		if (!restorePlayer(lineBuff)) return false;
	}
	// Otherwise, the file cannot be opened and thus will return an error.
	else
	{
		// Return false if there is an error.
		return false;
	}

	// Close the file.
	textFile.close();
	// Update the BoardView.
	gameDisplay.updateBoard(gameBoard);
	// No errors. Return true.
	return true;
}

/* *********************************************************************
Function Name: playRound
Purpose: To go through a round of Duell
Parameters:
none
Return Value: an integer that represents either a human or computer win, or if the game was saved to a file
Local Variables:
winCondition, an integer that stores the result of checkWinCondition for how the game was won
saveAnswer, an integer that stores the answer of whether or not the user wants to save
Algorithm:
1) Display the board, the wins of each player, and who is making the next move.
2) While there is no win condition, play through the game.
3) currentPlayer makes a move and the BoardDisplay is updated and printed to the window.
4) If a win condition is detected, the loop will exit.
5) Otherwise, the user will be asked to save the game and the answer stored in saveAnswer. If they choose to save,
they will be asked for a filename to save it to. winCondition will be assigned a value that signifies a save game exit
and will exit the loop.
6) Otherwise, switch the players and start from the beginning of the while loop.
7) Check the value stored in winCondition for the type of victory. A human win results in returning 1, with 2 for the
computer. The function will also output who won the game and how they did.
Assistance Received: none
********************************************************************* */
int Game::playRound()
{
	// Keep playing the round until a win condition is found. As the game is only beginning, this should return 0.
	int winCondition = checkWinCondition();
	// An integer that stores the answer of whether or not the user wants to save.
	int saveAnswer = 0;
	// Display the board.
	gameDisplay.updateDisplay();
	// Display the number of wins each player has (it should be 0 since it's a fresh game).
	gameTournament.printWins();
	// Display the next player.
	cout << "Next Player: " << currentPlayer->getPlayerName() << endl;
	cout << endl;
	while (winCondition == 0)
	{
		// Make a turn.
		currentPlayer->play(gameBoard);
		// Update the display.
		gameDisplay.updateBoard(gameBoard);
		gameDisplay.updateDisplay();
		// Print the wins.
		gameTournament.printWins();
		// Display the next player.
		cout << "Next Player: " << nextPlayer->getPlayerName() << endl;
		// Check for a win condition on the board using checkWinCondition().
		winCondition = checkWinCondition();
		// If there is a win condition on the board, break.
		if (winCondition > 0) break;
		// Otherwise, ask if the human wants to save.
		while (saveAnswer < 1 || saveAnswer > 2)
		{
			cout << "Save your progress? Press 1 to continue playing or 2 to save and quit: ";
			cin >> saveAnswer;
			// If the input is invalid, ask again.
			if (saveAnswer < 1 || saveAnswer > 2) cout << "Invalid input. Please enter a valid input." << endl;
		}
		// If the user wants to save, save and exit the game.
		if (saveAnswer == 2)
		{
			saveFile();
			// Exit the loop by letting winCondition be equal to 5.
			winCondition = 5;
			break;
		}
		// switch players.
		switchPlayers(currentPlayer, nextPlayer);
		cout << endl;
	}
	// Now determine the type of victory, print out the winner, and then return a number that corresponds to adding
	// to a win total.
	// Human win by key space occupation:
	if (winCondition == 1)
	{
		cout << "The human has landed on the computer's key space. The human wins!" << endl;
		return 1;
	}
	// Computer win by key space occupation:
	if (winCondition == 2)
	{
		cout << "The computer has landed on the human's key space. The computer wins!" << endl;
		return 2;
	}
	// Human win by key die capture:
	if (winCondition == 3)
	{
		cout << "The human has captured the computer's key die. The human wins!" << endl;
		return 1;
	}
	// Computer win by key die capture:
	if (winCondition == 4)
	{
		cout << "The computer has captured the human's key die. The computer wins!" << endl;
		return 2;
	}
	// If the winCondition is 5, there isn't really a win condition, but the human saved the game. Therefore the tournament
	// is over for now.
	if (winCondition == 5)
	{
		cout << "The game has been successfully saved." << endl;
		return 3;
	}
}

/* *********************************************************************
Function Name: registerWinner
Purpose: To properly increment the win amount of the player who won the game
Parameters:
roundResult, an integer that stores the number that corresponds to who won the game
Return Value: none
Local Variables:
none
Algorithm:
1) If roundResult is 1, call addHumanPoint()
2) Otherwise, call addComputerPoint()
Assistance Received: none
********************************************************************* */
void Game::registerWinner(int roundResult)
{
	// If the roundResult is 1, then the player won.
	if (roundResult == 1) gameTournament.addHumanPoint();
	// Otherwise, the computer won.
	else gameTournament.addComputerPoint();
}

/* *********************************************************************
Function Name: displayResults
Purpose: To display the results of the tournament and who won overall
Parameters:
none
Return Value: none
Local Variables:
none
Algorithm:
1) Print the amount of wins for each player
2) If the human won more than the computer, print that the human was won the tournament
3) If the computer won more than the human, print that the computer was won the tournament
4) If both players won the same amount of times, print that the tournament ends in a draw
Assistance Received: none
********************************************************************* */
void Game::displayResults()
{
	cout << "The final results of this tournament are:" << endl;
	// Display the wins of each player.
	gameTournament.printWins();
	// If the human has more wins than the computer, the player wins the tournament.
	if (gameTournament.getHumanWins() > gameTournament.getComputerWins())
		cout << "The Human is this tournament's winner! Congratulations!" << endl;
	// Likewise, if the computer has more wins, the computer wins the tournament.
	if (gameTournament.getComputerWins() > gameTournament.getHumanWins())
		cout << "The Computer is this tournament's winner! Congratulations!" << endl;
	// But if they are the same, the tournament is a draw.
	if (gameTournament.getComputerWins() == gameTournament.getHumanWins())
		cout << "Both players have the same amount of wins. The tournament ends in a draw!" << endl;
}

/* *********************************************************************
Function Name: saveFile
Purpose: To save the progress of the game to a text file
Parameters:
none
Return Value: none
Local Variables:
fileName, a string that stores the name of the file that will be saved to
textFile, an ofstream object that operates on the file
i and j, integers that iterate through for loops
Algorithm:
1) Get input from the user on what they would like the filename of the file to be and store it in fileName
2) Append .txt to the end of fileName
3) Open the file using textFile
4) Scan through the board and output what it looks like to the text file
5) Output the number of wins each player has to the text file
6) Output the player that is going next to the text file
7) Close the file
Assistance Received: none
********************************************************************* */
void Game::saveFile()
{
	// String that stores the name of the text file.
	string fileName;
	// The file itself.
	ofstream textFile;

	// Ask the user to create a name for the text file.
	cout << "Please enter a name for the file you want to save to (without .txt): ";
	cin >> fileName;
	// Append ".txt" to the end of the fileName.
	fileName += ".txt";
	// Open the file.
	textFile.open(fileName);
	// Start writing the appropriate format of a save file to the file.
	// The file always starts with how the board looks.
	textFile << "Board:" << endl << "\t";

	// Now scan the board for dice.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// If there is a die on the space, output its name to the file.
			if (gameBoard.isDieOn(i, j))
				textFile << gameBoard.getDieName(i, j) << "\t";
			// Otherwise, it's an empty space.
			else
				textFile << "0\t";
		}
		textFile << endl << "\t";
	}
	
	// Output the number of wins that each player has.
	textFile << endl << "Computer Wins: " << gameTournament.getComputerWins() << endl << endl;
	textFile << "Human Wins: " << gameTournament.getHumanWins() << endl << endl;

	// Get the next player.
	textFile << "Next Player: " << nextPlayer->getPlayerName();

	// We're done! Close the file.
	textFile.close();
}

/* *********************************************************************
Function Name: restoreBoard
Purpose: To restore the status of the board to what it looks like in the text file
Parameters:
buff, a string that contains a row on the board
row, an integer that contains the number of the row that will be restored on the board
Return Value: a boolean that signifies whether or not the board could be successfully restored
Local Variables:
parser, an istringstream that will help parse through the line of text
parsedText, a string that will store the current element being parsed
topNum and rightNum, integers that store the top and right numbers of a die that will be placed on the board
i, an integer that iterates through a for loop
Algorithm:
1) Parse into parsedText using parser nine times
2) If the first character of the parsedText is H or C, it's a die. Convert the top and right numbers into ints and store them
in topNum and rightNum, then place the die on the board
3) If it's a 0, it's an empty space. Do nothing
4) If it's anything else, it's not recognized by the program and will return false
5) If there were no problems, return true
Assistance Received: none
********************************************************************* */
bool Game::restoreBoard(string buff, int row)
{
	// Initialize the stringstream as the buffer.
	istringstream parser(buff);
	// String that stores the current element being parsed.
	string parsedText;
	// Integers that store the top and right numbers on a die.
	int topNum, rightNum;

	// Parse into the string nine times.
	for (int i = 1; i < 10; i++)
	{
		parser >> parsedText;
		// If it is a die name, initialize the die on the board.
		if (parsedText[0] == 'H' || parsedText[0] == 'C')
		{
			// Get the top and right numbers of the die.
			topNum = parsedText[1] - '0';
			rightNum = parsedText[2] - '0';
			// Place the die on the board.
			gameBoard.placeDie(Dice(topNum, rightNum, parsedText[0]), row, i);
		}
		// If it's a 0, it's just an empty space. Do nothing.
		else if (parsedText == "0") {}
		// Otherwise, it is not recognized by the board. Return false for an error.
		else return false;
	}

	// Everything went well. Return true.
	return true;
}

/* *********************************************************************
Function Name: restorePlayerWins
Purpose: To restore the amount of wins a player has on the board
Parameters:
buff, a string that contains a line in the file
Return Value: a boolean that signifies whether or not the wins could be successfully restored
Local Variables:
parser, an istringstream that will help parse through the line of text
parsedText, a string that will store the current element being parsed
playerName, a string that will store the name of the player
winAmount, an integer containing how many times the player has won
i, an integer that iterates through a for loop
Algorithm:
1) Parse into parsedText to get the player's name. If it's Human or Computer, store it in playerName. Otherwise it's a name
not recognized by the program, return false
2) Parse two more times to get the amount of wins
3) Convert to an int and store in winAmount
4) Iterate through a for loop to increment the amount of wins that the player has
5) Return true if all went well
Assistance Received: none
********************************************************************* */
bool Game::restorePlayerWins(string buff)
{
	// Initialize the stringstream as the buffer.
	istringstream parser(buff);
	// String that stores the current element being parsed.
	string parsedText;
	// String that stores the player's name.
	string playerName;
	// Integer that stores how many times the player has won.
	int winAmount;

	// Parse for the player's name.
	parser >> parsedText;
	// If the player is a  "Human" or "Computer," store it in the playerName.
	if (parsedText == "Human" || parsedText == "Computer")
		// Store it in the playerName.
		playerName = parsedText;
	// Otherwise, return false.
	else return false;
	playerName = parsedText;
	// Parse two more times.
	parser >> parsedText;
	parser >> parsedText;
	// parsedText is now the amount of times the player has won.
	winAmount = parsedText[0] - '0';
	// Restore the amount of wins depending on the player.
	for (int i = 0; i < winAmount; i++)
	{
		if (playerName == "Human") gameTournament.addHumanPoint();
		else gameTournament.addComputerPoint();
	}
	
	// Everything went well. Return true.
	return true;
}

/* *********************************************************************
Function Name: restorePlayer
Purpose: To restore the next player in the game
Parameters:
buff, a string that contains a line in the file
Return Value: a boolean that signifies whether or not the player could be successfully restored
Local Variables:
parser, an istringstream that will help parse through the line of text
parsedText, a string that will store the current element being parsed
Algorithm:
1) Parse into parsedText until it contains the name of the next player
2) If the name is not Human or Computer, it is invalid. Return false
3) Determine the player. If parsedText is Human, the human is the current player. Otherwise, it's the computer
4) Assign the pointers appropriately
5) Return true if there were no problems
Assistance Received: none
********************************************************************* */
bool Game::restorePlayer(string buff)
{
	// Initialize the stringstream as the buffer.
	istringstream parser(buff);
	// String that stores the current element being parsed.
	string parsedText;
	
	// Parse until we get to the "next" player.
	parser >> parsedText;
	parser >> parsedText;
	parser >> parsedText;

	// If parsedText is not "Human" or "Computer," the file is invalid. Return false.
	if (parsedText == "Human" || parsedText == "Computer")
	{
		// Determine who the player is.
		if (parsedText == "Human")
		{
			// Assign the pointers appropriately. Human should be the current player now.
			currentPlayer = &humanPlayer;
			nextPlayer = &computerPlayer;
		}
		else
		{
			// Computer should be the current player now.
			currentPlayer = &computerPlayer;
			nextPlayer = &humanPlayer;
		}
	}
	// Otherwise, the file is invalid. Return false
	else return false;
	
	// All seems to have went well. Return true.
	return true;
}

// Destructor.
Game::~Game()
{
}

/* *********************************************************************
Function Name: determineFirstMove
Purpose: To determine who will go first in a new round of Duell
Parameters:
currentPlayer and nextPlayer, Player pointers passed by reference that will keep track of the turns in the game
Return Value: none
Local Variables:
player1DieToss and player2DieToss, integers that will contain a random number between 1 and 6
Algorithm:
1) Store random numbers in player1DieToss and player2DieToss
2) Output to the window that a die toss is occurring to determine who goes first
3) If the numbers are the same, keep generating random numbers until they are not
4) Output what each player rolled
5) If player1DieToss is higher, the human will go first
6) Otherwise, the computer will go first
7) Assign to the currentPlayer pointer the winner of the die toss, and the loser to nextPlayer
Assistance Received: none
********************************************************************* */
void Game::determineFirstMove(Player * & currentPlayer, Player * & nextPlayer)
{
	// Initialize the random seed.
	srand(time(NULL));
	// The die toss result of the first player.
	int player1DieToss = rand() % 5 + 1;
	// The die toss result of the second player.
	int player2DieToss = rand() % 5 + 1;
	// Each round begins with a die toss to determine who goes first.
	cout << "The round will begin with a die toss. The player with the highest number will go first." << endl;
	// If the players happen to roll the same number, they will need to roll once again.
	while (player1DieToss == player2DieToss)
	{
		cout << "The players both rolled a " << player1DieToss << "! A die toss must occur once again." << endl;
		player1DieToss = rand() % 5 + 1;
		player2DieToss = rand() % 5 + 1;
	}
	cout << "The Human rolled a " << player1DieToss << " and the Computer rolled a " << player2DieToss << "." << endl;
	// If Player1 rolled higher, they go first.
	if (player1DieToss > player2DieToss)
	{
		cout << "The Human goes first." << endl;
		currentPlayer = &humanPlayer;
		nextPlayer = &computerPlayer;
	}
	// If Player2 rolled higher, they go first.
	else
	{
		cout << "The Computer goes first." << endl;
		currentPlayer = &computerPlayer;
		nextPlayer = &humanPlayer;
	}
}

/* *********************************************************************
Function Name: switchPlayers
Purpose: To switch the players so that the next player can make their turn
Parameters:
currentPlayer and nextPlayer, Player pointers passed by reference that contain who goes next in the game
Return Value: none
Local Variables:
temp, a Player pointer that is used to help switch the values between the two pointers in the parameters
Algorithm:
1) Assign currentPlayer to temp
2) Assign nextPlayer to currentPlayer
3) Assign temp to nextPlayer
Assistance Received: none
********************************************************************* */
void Game::switchPlayers(Player *& currentPlayer, Player *& nextPlayer)
{
	// Temporary pointer.
	Player * temp;
	// Switch the players.
	temp = currentPlayer;
	currentPlayer = nextPlayer;
	nextPlayer = temp;
}

/* *********************************************************************
Function Name: checkWinCondition
Purpose: To see if a win condition exists on the board
Parameters:
none
Return Value: an integer that corresponds to the type of victory on the board
Local Variables:
keyDieResult, an integer that stores the result whose key die is no longer on the board
Algorithm:
1) Check the key spaces of each player. If there is a die of an enemy type occupying the key space of a player, the game is
over
2) If not, check for the key dice of each player. If a player's key die is missing from the board, the game is over
3) Otherwise, if no win conditions exist, return 0
Assistance Received: none
********************************************************************* */
int Game::checkWinCondition()
{
	// First, check the key spaces. If the die playerType does not match the space of the player it should belong to,
	// the player with their die on that space wins the game.

	// Check the player's key space.
	if (gameBoard.isDieOn(1, 5))
	{
		// If the die on it is not a human type, the human loses and the game is over.
		if (gameBoard.isDiePlayerType(1, 5, 'C')) return 2;
	}
	// Now check the computer's key space.
	if (gameBoard.isDieOn(8, 5))
	{
		// If the die on it is not a computer type, the computer loses and the game is over.
		if (gameBoard.isDiePlayerType(8, 5, 'H')) return 1;
	}

	// Now look for the key dies for each player.
	int keyDieResult = isKeyDieOnBoard();
	// If the result is 1, the computer's key die is captured and the computer loses the game.
	if (keyDieResult == 1) return 3;
	// If the result is 2, the human's key die is captured and the human loses the game.
	if (keyDieResult == 2) return 4;
	// Otherwise, 0 was found, which means both key dice are on the board and the key spaces are not occupied. Nobody
	// has won yet.
	return 0;
}

/* *********************************************************************
Function Name: isKeyDieOnBoard
Purpose: To determine if there is a key die missing from the board or not
Parameters:
none
Return Value: an integer that corresponds to a player's key die missing on the board
Local Variables:
humanKeyDie and computerKeyDie, booleans that contain whether or not a key die is missing
i and j, integers that iterate through for loops
Algorithm:
1) Scan the board for the key dice
2) If there is a die on the space, check if it's the key die. If it is, check the playerType of it
3) If it's a human key die, humanKeyDie becomes true. If it's a computer key die, computerKeyDie becomes true
4) If the computer's key die is missing, return 1. If the human's is missing, return 2. Otherwise return 0 if they are both
on the board
Assistance Received: none
********************************************************************* */
int Game::isKeyDieOnBoard()
{
	// Initialize boolean values for the key dies of each player and whether or not they're on the board.
	bool humanKeyDie = false;
	bool computerKeyDie = false;
	// Search the board for the key die. Use a for loop to iterate through the board.
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 10; j++)
		{
			// If there is a key die on the space, check the playerType.
			if (gameBoard.isKeyDie(i, j))
			{
				// If it is a human type, humanKeyDie is true.
				if (gameBoard.isDiePlayerType(i, j, 'H')) humanKeyDie = true;
				// If it is a computer type, computerKeyDie is true.
				if (gameBoard.isDiePlayerType(i, j, 'C')) computerKeyDie = true;
			}
		}
	}
	// If both are true, return 0.
	if (humanKeyDie && computerKeyDie) return 0;
	// If the human's key die is present but not the computer's, return 1.
	if (humanKeyDie && !computerKeyDie) return 1;
	// If the computer's key die is present but not the human's, return 2.
	if (!humanKeyDie && computerKeyDie) return 2;
}
