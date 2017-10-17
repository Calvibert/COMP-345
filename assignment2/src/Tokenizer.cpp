/*
 * tokenizer.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
	// TODO Auto-generated constructor stub

}

Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> Tokenizer::splitIntoTokens(std::string text){
	std::vector<std::string> tokens;
	std::string word;
	std::vector<char> breakwords;

	// Iterate over the characters in the document's text
	for(char& c : text) {
		if (std::find(breakwords.begin(), breakwords.end(), c)!=breakwords.end()) {
			// char in array, reached the end of a word.
			tokens.push_back(word);
			word = "";
			// On to the next char
			continue;
		}
		// add char to word
		word += tolower(c);
	}

	return tokens;
}

std::string Tokenizer::containsPunctuation(std::string word) {
	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
	return word;
}
