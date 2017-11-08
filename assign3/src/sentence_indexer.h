/*
 * sentence_indexer.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef SENTENCE_INDEXER_H_
#define SENTENCE_INDEXER_H_

#include "indexer.h"
#include "Document.h"
#include "sentence.h"
#include "sentence_tokenizer.h"
#include "word_tokenizer.h"
#include <vector>
#include <string>
#include <math.h>
#include <tgmath.h>
#include <algorithm>

class sentence_indexer: public indexer {
public:
	struct Entry {
			std::string term;
			std::vector<sentence> sents;
			std::vector<double> freqs;
			std::vector<double> tf_idf;
		};
	sentence_indexer();
	virtual ~sentence_indexer();
	void readDocument(std::string fileName);
	void normalize();

	std::vector<sentence> getSentences();
	std::vector<Document> getDocs();
	//void addSentence(sentence & s);
	void addSentences(std::vector<sentence> & vs);
	void addDoc(Document & d);
	void addToIndex(std::string term, sentence & sent);
	sentence getSentence(std::string fileName);
	double getDocCount();
	void incDocCount();

private:
	std::vector<Document> docs;
	std::vector<sentence> sentences;
	std::vector<sentence_indexer::Entry> index;
	bool normalized;
	double docCount;

};

#endif /* SENTENCE_INDEXER_H_ */
