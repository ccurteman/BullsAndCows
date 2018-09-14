#include "FBullCowGame.h"
#include <map>

using namespace std;

// Game Constructor
FBullCowGame::FBullCowGame() { Reset(); }

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

string FBullCowGame::SetHiddenWord(string HostWord)
{
	MyHiddenWord = HostWord;
	return string(HostWord);
}

int FBullCowGame::GetMaxTries() const 
{ 
	map <int, int> WordLengthToMaxTries{ {3,4},{4,6},{5,8},{6,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

// Reset is called whenever the game is being played again to return certain
// variables to default values
void FBullCowGame::Reset()
{
	// Resetting the hidden word to nothing
	MyHiddenWord = "";

	// Resetting tries, and game state
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
// Checking the validity of the host word
EGuessStatus FBullCowGame::CheckWordValidity(string Word) const
{
	// If the guess isn't an isogram
	if (!IsIsogram(Word))
	{
		return EGuessStatus::Not_Isogram;
	}

	// If the word has numbers in it
	else if (!HasNumbers(Word))
	{
		return EGuessStatus::Has_Number;
	}

	// If the guess isn't all lowercase
	else if (!IsLowercase(Word))
	{
		return EGuessStatus::Not_Lowercase;
	}
}

// This function takes the users guess, and checks it for various mistakes
// using a series of enum values set in the header file
EGuessStatus FBullCowGame::CheckGuessValidity(string Guess) const
{
	// If the guess isn't an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}

	// If the word has numbers in it
	else if (!HasNumbers(Guess))
	{
		return EGuessStatus::Has_Number;
	}

	// If the guess isn't all lowercase
	else if (!IsLowercase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase;
	}

	// If the guess length is wrong
	else if (Guess.length() != MyHiddenWord.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// This helper method checks if any letters repeat in the players guess
bool FBullCowGame::IsIsogram(string Guess) const
{
	if (Guess.length() <= 1) { return true; } // Treat 0 and 1 letter words as isograms
	map <char, bool> LetterSeen; // Setup of our map (dictionary like object)

	for (auto Letter : Guess) 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) 
		{
			return false;
		}
		else 
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

// Another helper method to check for lowercase
bool FBullCowGame::IsLowercase(string Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

// Another method to check if there are any numbers in the word or guess
bool FBullCowGame::HasNumbers(string Guess) const
{
	// Looping through the guess or word to see if it has any numbers in it
	for (auto Letter : Guess)
	{
		if (isdigit(Letter))
		{
			return false;
		}
	}
	return true;
}

// Receives pre-validated guess, counts cows and bulls, and then increments and returns turn count
FBullCowCount FBullCowGame::SubmitValidGuess(string Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int WordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}