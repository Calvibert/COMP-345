/*
 * abstracttokenizer.h
 *
 *  Created on: Nov 1, 2017
 *      Author: Maude
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
