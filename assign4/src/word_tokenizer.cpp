/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class splits the document into word tokens
 *
 */

#include "word_tokenizer.h"

/**
 * default constructor
 */
word_tokenizer::word_tokenizer() {

}
/**
 * constructor
 * @param string representing the text to be split into individual words
 */
word_tokenizer::word_tokenizer(std::string text) {
	std::vector<std::string> tokens = splitIntoTokens(text);
}

/**
 * deconstructor
 */
word_tokenizer::~word_tokenizer() {

}

/**
 * This function takes a string and splits it into individual words, handling most punctuation and abbreviations
 * @param text is the document text to be split
 * @return a vector of individual words
 */
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

/**
 * Overloaded << operator to provide meaningful debug output
 * @param os the string to be returned
 * @param wt an object of word_tokenizer
 * @return the output
 */
std::ostream& operator<<(std::ostream& os, const word_tokenizer& wt){
	for(std::vector<std::string>::const_iterator it = wt.tokens.begin(); it != wt.tokens.end(); ++it){
		os << *it << std::endl;
	}
	return os;
}


