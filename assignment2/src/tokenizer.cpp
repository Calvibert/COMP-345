/*
 * tokenizer.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#include "tokenizer.h"

tokenizer::tokenizer() {
	// TODO Auto-generated constructor stub

}

tokenizer::~tokenizer() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> tokenizer::splitIntoTokens(std::string filename){
	std::ifstream fin(filename);
	std::vector<std::string> tokens;
	std::string currentWord;

	if (!fin) {
		throw "Error opening input file. Closing";
	}

	while (fin >> currentWord) {
		// Remove punctuation
		currentWord = containsPunctuation(currentWord);
		// Transform term to lower case using built in method
		transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

		//std::cout << currentWord << std::endl;
		tokens.push_back(currentWord);
	}
	fin.close();
	return tokens;
}

std::string tokenizer::containsPunctuation(std::string word) {
	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
	return word;
}
