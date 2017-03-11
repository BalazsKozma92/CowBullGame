#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() {
	FBullCowCount BullCowCount;
	BullCowCount.Bulls = 0;
	BullCowCount.Cows = 0;

	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "pathfinder";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_LowerCase;
	} else if (Guess.length() != MyHiddenWord.length()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		for (int32 j = 0; j < Guess.length(); j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for each (char Letter in Word) {
		Letter = tolower(Letter);
		//if (LetterSeen.count(Letter)) {
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
			//LetterSeen.insert(std::pair<char, bool>(Letter, true));
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
	for each (auto Letter in Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
