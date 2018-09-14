#pragma once
#include <iostream>
#include <string>

using namespace std;

struct FBullCowCount 
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Has_Number
};

class FBullCowGame 
{
public:
	FBullCowGame();

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	string SetHiddenWord(string);
	bool IsGameWon() const;
	EGuessStatus CheckWordValidity(string) const;
	EGuessStatus CheckGuessValidity(string) const;

	void Reset();
	FBullCowCount SubmitValidGuess(string);

private:
	int MyCurrentTry;
	int MyMaxTries;
	string MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(string) const;
	bool IsLowercase(string) const;
	bool HasNumbers(string) const;
};

