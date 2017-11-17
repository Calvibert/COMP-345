/*
 * word_tokenizer.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: Maude
 */

#include "word_tokenizer.h"

word_tokenizer::word_tokenizer() {

}

word_tokenizer::word_tokenizer(std::string text) {
	std::vector<std::string> tokens = splitIntoTokens(text);
}

word_tokenizer::~word_tokenizer() {

}

// It breaks the words down depending on that list of characters
std::vector<std::string>& word_tokenizer::splitIntoTokens(std::string text){
	dealWithAbbreviations(text); //common abbreviations like UN UK IE, etc.
	std::string word;
	std::vector<char> breakwords = {'\n', ',','.', '”', '"', '“', '!', '?', '`', '_',  ' ', '(', ')', '\t', '…'};
	std::string temp = "";

	// Iterate over the characters in the document's text
	for(char& c : text) {
		if (std::find(breakwords.begin(), breakwords.end(), c)!=breakwords.end()) {
			// char in array, reached the end of a word.
			if (word != ""){
				tokens.push_back(word);
				word = "";
			}
			// On to the next char, skip this one
			continue;
		}
		if(word == "" && c == '\'')
			continue;

		// add char to word
		word += tolower(c);
	}
	return tokens;
}

std::ostream& operator<<(std::ostream& os, const word_tokenizer& wt){
	for(std::vector<std::string>::const_iterator it = wt.tokens.begin(); it != wt.tokens.end(); ++it){
		os << *it << std::endl;
	}
	return os;
}
