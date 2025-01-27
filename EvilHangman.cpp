
#include <string>
#include <iostream>
#include <set>

#include "FamilySet.h"
//#include "TreeMap.h"
using namespace std;

bool debug;

bool PromptYesNoMessage(string msg) {
	while (true) {
		cout << msg << " (y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n." << endl;
	}
}

int PromptGuesses() 
{
	while (true) {
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
		cout << "Please enter a valid integer."<< endl;
	}
}

int PromptWordLength() {
	while (true) {
		int len;
		cout << "Please enter word length: ";
		cin >> len;
		if (len > 0)
			return len;
		cout << "Please enter a valid word length." << endl;
	}
}


string PromptGuess(string& guessedLetters)
{
	while (true) {
		string guess = "";
		// Your code here...
		cout << "Please enter your guess as a single letter: ";
		cin >> guess;
		if(!isalpha(guess[0])) {
			cout << "Please enter a valid letter. You're wasting your guesses >:)" << endl;
		}
		guessedLetters = guess;
		return string(1,guess[0]);
	}
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set) 
{
    // filter families by guess and guessProgress/guessPattern
	set.filterFamilies(guess, guessProgress);

    string maxFamily;
	int maxFamilySize = 0;
    /*
     * Use the iterator to loop through each family and
     * figure out the biggest family size.
     * Return this family
     */
	string family;
	//Iterate through the families in the set
	while(!(family = set.getNextFamily()).empty()) {
		//Keeping track of the current family size
		int currentFamilySize = set.familySize(family);
		//Finding the maxFamily by comparing the current size to the max
		if (currentFamilySize > maxFamilySize) {
			//If the current family size is greater than max, set the max family equal to the current family
			maxFamily = family;
			maxFamilySize = currentFamilySize;
		}
	}
    return maxFamily;
}

bool isWin(string guessedProgress)
{
	return guessedProgress.find('*') == string::npos;
}

void PlayEvilHangman(string file) 
{
    int len, guessesLeft;
    string guessProgress = "";      // correctly guessed positions
    string guessedLetters = "";     // letters already guessed by user

    // Prompt user for word length and number of guesses
	len = PromptWordLength();
	guessesLeft = PromptGuesses();

    // Load dictionary based on word length
    cout << "Loading dictionary..." << endl;
    FamilySet families(file, len);

    // Show *'s for the guessProgress at the beginning
    for (int i = 0; i < len; i++)
        guessProgress += "*";

	// Actual game loop...
	while (true) {
		cout << endl << endl;
		cout << guessProgress << endl;
		cout << "Guesses Left: " << guessesLeft << endl;
		cout << "Guessed Letters: " << guessedLetters << endl;

		//Get user's guess
		string guess = PromptGuess(guess);

		//check if letter has already been guessed
		if(guessedLetters.find(guess) != string::npos) {
			cout << "You already guessed " << guess << endl;
			continue;
		}

		//Add guessed letter to the list of guessed letters
		guessedLetters += guess;
		//Select the best family after filtering by the guess
		string bestFamily = ChooseFamily(guess, guessProgress, families);
		//If no family was found, continue with next round
		if(bestFamily.empty()) {
			cout << "No valid family found. Something went wrong!" << endl;
			continue;
		}
		//Update FamilySet to the best family based on the guess
		families.setFamily(bestFamily);

		//Update guessProgress based on best family and fill in correct letters
		vector<string> words = families.getWords();
		//store the words of the current family
		for(int i = 0; i < words.size(); ++i) {
			//iterate through each word in the words vector
			string &word = words[i];
			//get a reference to the current word
			for(int j = 0; j < word.length(); ++j) {
				//loop through each character in the word
				if(word[j] == guess[0]) {
					//check if the current character matches the guessed letter
					guessProgress[j] = word[j];
					//Update the guessProgress at the current position with guessed letter
				}
			}
		}
		//Check the user's progress to see if they won
		if (isWin(guessProgress)) {
			cout << endl << "Wow! You won!" << endl;
			return;
		}
		//If they haven't won, decrement the amount of guesses left
		--guessesLeft;
		//Game over if the user runs out of guesses
		if (guessesLeft <= 0) {
			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " << families.getRandomWord() << endl;
			return;
		}
	}
}

int main()
{
    string file;
    cout << "Enter file: ";
    cin >> file;				// Can comment out this line and include the following while developing
    file = "dictionary.txt";  // Convenient to hard code while developing
	
	while (true) {
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again? "))
			break;
	}
}

