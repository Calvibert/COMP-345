/*
 * sentence_tokenizer.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Maude
 */

#ifndef SRC_SENTENCE_TOKENIZER_H_
#define SRC_SENTENCE_TOKENIZER_H_

#include "abstract_tokenizer.h"

class sentence_tokenizer: public abstract_tokenizer {
public:
	sentence_tokenizer(std::string text);
	virtual ~sentence_tokenizer();
	bool testForTitle(std::string sentence);
	std::vector<std::string>& splitIntoSentences(std::string filecontents);
	bool checkIfWhitespace(std::string sentence);
	//void dealWithAbbreviations(std::string& sentence);
	friend std::ostream& operator<<(std::ostream& os, const sentence_tokenizer& wst);
private:
	std::vector<std::string> sentences;
};

#endif /* SRC_SENTENCE_TOKENIZER_H_ */
