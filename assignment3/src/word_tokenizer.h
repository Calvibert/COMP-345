/*
 * word_tokenizer.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Maude
 */

#ifndef SRC_WORD_TOKENIZER_H_
#define SRC_WORD_TOKENIZER_H_

#include "abstract_tokenizer.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

class word_tokenizer: public abstract_tokenizer {
public:
	word_tokenizer();
	word_tokenizer(std::string text);
	virtual ~word_tokenizer();
	std::vector<std::string>& splitIntoTokens(std::string filename);
	friend std::ostream& operator<<(std::ostream& os, const word_tokenizer& wt);
private:
	std::vector<std::string> tokens;
};

#endif /* SRC_WORD_TOKENIZER_H_ */
