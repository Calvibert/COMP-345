/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * The abstract base class containing information and functions for both word_tokenizer and sentence_tokenizer
 *
 */


//contains a pure virtual function somewhere
#ifndef SRC_ABSTRACT_TOKENIZER_H_
#define SRC_ABSTRACT_TOKENIZER_H_

#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

class abstract_tokenizer {
public:
	void dealWithAbbreviations(std::string& sentence);
};

#endif /* SRC_ABSTRACT_TOKENIZER_H_ */
