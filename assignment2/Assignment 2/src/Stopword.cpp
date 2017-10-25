/*
 * stopword.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#include "Stopword.h"

// Default constructor
Stopword::Stopword() {

}

// Stopword destructor
Stopword::~Stopword() {
	// TODO Auto-generated destructor stub
}

// Given an input list of tokens, it processes that file into a vector and returns it
std::vector<std::string> Stopword::fillList(std::string inputFile){
	std::ifstream fin(inputFile);
	std::vector<std::string> allTokens;
	std::string currentWord;
	if (!fin) {
		throw "Error opening input file. Closing";
	}

	while (fin >> currentWord) {
		// Remove punctuation
		currentWord = containsPunctuation(currentWord);
		// Transform term to lower case using built in method
		transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

		allTokens.push_back(currentWord);
	}
	fin.close();
	return allTokens;
}

// Helper function to check for punctuation
std::string Stopword::containsPunctuation(std::string word) {
	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
	return word;
}

// Return true if the token is in the list, false otherwise
bool Stopword::operator()(std::string token){
	for (std::vector<std::string>::const_iterator i = stopwordList.begin(); i != stopwordList.end(); ++i){
		if ((*i).compare(token))
			return true;
	}
	return false;
}

// Setter
void Stopword::setStopwordList(std::vector<std::string> sl){
	stopwordList = sl;
}

// Getter
std::vector<std::string> Stopword::getStopwordList(){
	return stopwordList;
}
