#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class FamilySet
{
public:
    FamilySet(string dictFile, int len);
	//Precondition: Requires a file to pass in as a string and a valid integer for the length len
	//Post-condition: Opens a word file and pushes all words of length len into wordlist

	// Initializes from a word file where the word
	// must be of length len.

	~FamilySet();
	//Precondition: wordList must be initialized
	//Post-condition: Deallocates wordlist

	void filterFamilies(string letter, string guessPattern);
	//Precondition: Requires two strings to be passed in for the letter and guessPattern
	//Post-condition: Filters and organizes words into families based on the current guess and guessPattern

	void setFamily(string family);
	//Precondition: Requires a string to be passed in as the family
	//Post-condition: Sets wordList to the dictionary of the given family and also clears the dictionaries
	string getRandomWord();
	//Precondition: wordList must be initialized
	//Post-condition: Returns a random word from wordList

	vector<string> getWords();
	//Precondition: wordList must be initialized
	//Post-condition: Returns the words from wordList
	int numWords();
	//Precondition: wordList must be initialized
	//Post-condition: Returns the number of words in wordList
	int numFamilies();
	//Precondition: dictionaries must be initialized
	//Post-condition: Returns the number of families currently in dictionaries
	int familySize(string family);
	//Precondition: Requires a string to be passed in as the family
	//Post-condition: Returns the number of words for a given family in dictionaries. If
	//the family doesn't exist, it returns -1

	// Iterator
	void resetFamilyIter();
	//Precondition: dictionaries must be initialized
	//Post-condition: Sets the iterator to the beginning
	string getNextFamily();
	//Precondition: dictionaries must be initialized
	//Post-condition: Returns the current family. If there are no more families left, it returns an empty string
	
private:
    	// This stores all words currently "valid"
	vector<string>* wordlist;
	unordered_map<string, vector<string>*> dictionaries;

	// Used for Iterator.  The const_iterator is the same as an iterator
	// but used for situations where you want to prevent changes to the data.
	unordered_map<string, vector<string>*>::const_iterator famIter;
};
