/*
 * tokenizer.h
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

class tokenizer {
public:
	tokenizer();
	virtual ~tokenizer();
	std::vector<std::string> splitIntoTokens(std::string filename);
	std::string containsPunctuation(std::string word);
};

#endif /* TOKENIZER_H_ */
