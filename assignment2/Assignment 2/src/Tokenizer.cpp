/*
 * tokenizer.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#include "Tokenizer.h"

// Default constructor
Tokenizer::Tokenizer() {

}

// Default destructor
Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}

// Given a string, processes the words into a vector<string> and returns it
// The tokenization strategy is dependent on the breakwords.
// It breaks the words down depending on that list of characters
std::vector<std::string> Tokenizer::splitIntoTokens(std::string text){
	std::vector<std::string> tokens;
	std::string word;
	std::vector<char> breakwords = {'\n', ',', ' ', '.'};

	// Iterate over the characters in the document's text
	for(char& c : text) {
		if (std::find(breakwords.begin(), breakwords.end(), c)!=breakwords.end()) {
			// char in array, reached the end of a word.
			if (word != ""){
				tokens.push_back(word);
				word = "";
			}
			// On to the next char
			continue;
		}
		// add char to word
		word += tolower(c);
	}

	return tokens;
}
