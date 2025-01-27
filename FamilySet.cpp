#include "FamilySet.h"

#include <deque>

FamilySet::FamilySet(string dictFile, int len) {
	//Allocate memory for wordList and open provided file
	wordlist = new vector<string>;
	ifstream file;
	file.open(dictFile);
	//while we have not reached the end of the file, push all words of length len into
	//wordList
	while (!file.eof()) {
		string word;
		getline(file, word);
		if (word.length() == len) {
			wordlist->push_back(word);
		}
	}
}

FamilySet::~FamilySet() {
	delete wordlist;
}

void FamilySet::filterFamilies(string letter, string guessPattern) {
	//reset the families by clearing the dictionaries map
	dictionaries.clear();
	//Iterate through each word in wordList
	for (int i = 0; i < wordlist->size(); i++) {
		//Construct the family
		string word = (*wordlist)[i];
		string family;

		//Check if the letter exists in the word
		//If we can find the letter in the word, it'll be apart of the family
		if (word.find(letter) != string::npos) {
			//if the letter exists, build the family by replacing all characters
			//except first and last with *
			family = word;
			//begin with the full word and iterate through each letter
			for (int j = 0; j < word.length(); j++) {
				//if the character at position j is not the letter, replace it with *
				if(family[j] != letter[0]) {
					family[j] = '*';
				}
			}
		} else {
			//If the letter does not exist in the word, family will be the guessPattern
			family = guessPattern;
		}

		//If family doesn't exist in dictionaries, create a new entry
		if(dictionaries.find(family) == dictionaries.end()) {
			dictionaries[family] = new vector<string>();
		}
		//Push the word into the appropriate family
		dictionaries[family]->push_back(word);
	}
	//reset familyIter after filtering
	resetFamilyIter();
}

void FamilySet::setFamily(string family) {
	//Check if family exists in dictionaries
	 if(dictionaries.find(family) != dictionaries.end()) {
	 	//clears the current wordlist
	 	wordlist->clear();
	 	//sets wordlist to the dictionary of the current family
	 	wordlist = dictionaries[family];
	 	//clears the dictionary
	 	dictionaries.erase(family);
	 }
}

int FamilySet::familySize(string family) {
	// If the family exists, return number of words for a given family
	if(dictionaries.find(family) != dictionaries.end()) {
		return dictionaries[family]->size();
	}
	//otherwise return -1
	return -1;
}

void FamilySet::resetFamilyIter() {
	//Reset the iterator to the beginning
	famIter = dictionaries.begin();
}

string FamilySet::getNextFamily() {
	if(famIter == dictionaries.end()) {
		//Return empty string if there are no more families left
		return "";
	}
	//Get the family name (key in dictionary)
	string family = famIter->first;
	//Move iterator to the next family
	++famIter;
	//return current family name
	return family;
}

string FamilySet::getRandomWord()
{
	int ind = rand() % wordlist->size();
	return wordlist->at(ind);
}

int FamilySet::numWords()
{
	return wordlist->size();
}

int FamilySet::numFamilies()
{
	return dictionaries.size();
}

vector<string> FamilySet::getWords() {
    return *wordlist;
}

