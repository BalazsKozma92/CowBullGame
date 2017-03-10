#include <iostream>
#include <string>

using namespace std;

void PrintIntro();
string GetGuessAndPrintBack();

int main() {
	PrintIntro();
	for (int i = 0; i < 5; i++)
	{
		GetGuessAndPrintBack();
	}
}

string GetGuessAndPrintBack() {
	string Guess = "";
	cout << "Please Type in your guess: ";
	getline(cin, Guess);
	cout << "Your guess was: " << Guess << endl << endl;
	return Guess;
}

void PrintIntro() {
	constexpr int WORD_LENGTH = 10;
	cout << "Welcome to Cows and Bulls" << endl;
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinkin of?" << endl << endl;
	return;
}