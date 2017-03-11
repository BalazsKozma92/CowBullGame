#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {
	

	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro() {
	std::cout << std::endl << std::endl << "Welcome to Cows and Bulls" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinkin of?" << std::endl << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Your max tries: " << MaxTries << std::endl;

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << std::endl << std::endl;
	}

	// TODO summarize game
}

FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Please Type in your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram word (word without repeating letters).";
			std::cout << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength();
			std::cout << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter the word in lowercase.";
			std::cout << std::endl;
			break;
		default:
			// assume the guess is valid
			break;
			std::cout << std::endl;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "YOU WON! ";
	}
	else if (!BCGame.IsGameWon()) {
		std::cout << "Better luck next time. ";
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
