/*
 * sentence_tokenizer.h
 *
 *  Created on: Nov 2, 2017
 *      Author: Maude
 */

#ifndef SRC_SENTENCE_TOKENIZER_H_
#define SRC_SENTENCE_TOKENIZER_H_

#include "abstract_tokenizer.h"
#include "sentence.h"

class sentence_tokenizer: public abstract_tokenizer {

public:
	sentence_tokenizer();
	virtual ~sentence_tokenizer();
	bool testForTitle(std::string sentence);
	std::vector<sentence>& splitIntoSentences(Document & doc);
	bool checkIfWhitespace(std::string sentence);
	//void dealWithAbbreviations(std::string& sentence);
	friend std::ostream& operator<<(std::ostream& os,
			sentence_tokenizer& wst);
	std::vector<sentence> getSentences();

private:
	std::vector<sentence> sentences;

};

#endif /* SRC_SENTENCE_TOKENIZER_H_ */
