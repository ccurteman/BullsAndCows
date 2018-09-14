// Chris Curteman
// Bulls and Cows

#include <iostream>
#include <string>
#include <Windows.h>
#include "FBullCowGame.h"

using namespace std;

void PrintIntro();
void PlayGame();
string GetValidWord();
string GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void GetHelp();

// TODO Explain how the game works from top to bottom to Lucius
// TODO Delete and Reinit Git on this file to get rid of logs, etc
// TODO Upload zip to GitHub and add a good readme

// Instantiating a new FBullCowGame object in a global scope for ease of use
FBullCowGame BCGame;

int main()
{
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());

	cout << "Thanks for playing!";
	return 0;
}

// Introducing the game and welcoming the player
void PrintIntro()
{
	cout << "|----------------------------------------------\n";
	cout << "| Welcome to Bulls and Cows\n";
	cout << "| (type 'help' to learn how the game works)\n";
	cout << "|----------------------------------------------\n\n";
	return;
}

// PlayGame handles turn tracking and win game status based on valid guesses
void PlayGame()
{
	// Reset to make sure everything is set correctly
	BCGame.Reset();

	// Getting a word from the host for the player to guess
	string word = GetValidWord();

	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n\n";

	// Setting the number of tries the user will get based on word length
	int MaxTries = BCGame.GetMaxTries();

	// Looping through turns while the game is not won
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		string Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		/* This next if statement is technically breaking MVC design, but is
		implemented here in order to skip printing out how many bulls and cows
		the guess generates, which, at the point of a winning guess, is irrelevant.*/
		if (BCGame.IsGameWon())
		{
			break;
		}

		cout << Guess << " is not correct" << "\n";
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	return;
}

// GetValidGuess is called to recieve, validate, and return a guess from the player
string GetValidWord()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	string Word = "";
	do {
		cout << "What is your isogram: ";
		getline(cin, Word); // Getting guess from input

		// Clearing the screen
		system("CLS");
		
		// Checking if user is trying to get help
		string help = "help";
		if (Word == help)
		{
			GetHelp();
			GetValidWord();
		}

		// Checking for the validity of the word via switch statements, which are used for the guess as well
		Status = BCGame.CheckWordValidity(Word);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters \n\n";
			break;
		case EGuessStatus::Has_Number:
			cout << "Please use letters, no numbers \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Please type in all lowercase \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	BCGame.SetHiddenWord(Word);
	return Word;
}

// GetValidGuess is called to recieve, validate, and return a guess from the player
string GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	string Guess = "";
	do {
		int CurrentTry = BCGame.GetCurrentTry();
		int MaxTries = BCGame.GetMaxTries();
		cout << "Try " << CurrentTry << " of " << MaxTries << ".\n";
		cout << "What is your guess: ";
		getline(cin, Guess); // Getting guess from input

		string help = "help";
		if (Guess == help)
		{
			GetHelp();
			GetValidGuess();
		}

		// Checking for the validity of the guess via switch statements
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Please type in all lowercase \n\n";
			break;
		case EGuessStatus::Has_Number:
			cout << "Please use letters, no numbers \n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

// AskToPlayAgain controls the loop inside main
bool AskToPlayAgain()
{
	cout << "\nDo you want to play again? (Y/N): ";
	string Response = "";
	getline(cin, Response);

	// If determines if the game repeats
	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		cout << endl;
		system("CLS");
		return true;
	}
	return false;
}

// PrintGameSummary is called either when the player guesses correctly
// - OR -
// The player runs out of turns
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		cout << "Well done - you win! \n";
	}
	else
	{
		cout << "Better luck next time! \n";
	}
}

// GetHelp prints out some text to help explain the game if the player enters in 'help' as a guess
void GetHelp()
{
	cout << "\n------------------------------------------------------------------------------\n";
	cout << "Bulls and Cows is an old game that dates back close to 100 years ago.\n";
	cout << "It's typically played by two players - a host, and a player.\n";
	cout << "The host writes down a word, usually a 4-letter word, that is an isogram.\n";
	cout << "The player then tries to guess what word the host has written down.\n";
	cout << "The host tells the player if the guess has scored any Bulls or Cows.\n";
	cout << "A Cow is a letter in the players guess that is in the host's word, but in the wrong position of the word.\n";
	cout << "While a Bull is a letter that is in the host's word AND in the right position.\n";
	cout << "For example, if the host word is HEAT, a guess of COIN would result if 0 Cows and 0 Bulls,\n";
	cout << "while a guess of EATS would result in 0 Bulls and 3 Cows - because E, A, and T are present in the word,\n";
	cout << "but not guessed in the right position - and a guess of TEAL would be 2 Bulls and 1 Cow.\n";
	cout << "The game continues in this way until either a player guesses correctly, or runs out of turns.\n";
	cout << "In this program, the host is run by the computer, and the player is you, trying to guess the correct word\n\n";
	cout << "Visit https://en.wikipedia.org/wiki/Bulls_and_Cows for more info on the game.\n";
	cout << "------------------------------------------------------------------------------\n\n";
	return;
}


