/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This splits the document into sentences while building the index and queries the sentence-term matrix
 *
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
#include <map>

class sentence_indexer: public indexer {
public:
	struct Entry {
		std::string term;
		std::vector<sentence> sents;
		std::vector<double> freqs;
		std::vector<double> tf_idf;
	};
	sentence_indexer();
	void readDocument(std::string fileName);
	void normalize();
	std::vector<sentence_indexer::query_result> query(std::string queryTerms,
			int maxWords = 500);

	std::vector<sentence> getSentences();
	std::vector<Document> getDocs();
	void addSentences(std::vector<sentence> & vs);
	void addDoc(Document & d);
	void addToIndex(std::string term, sentence & sent);
	sentence getSentence(std::string fileName);
	double getDocCount();
	void incDocCount();
	bool getNormalized();
	std::map<std::string, sentence> getSentenceNamesSents();

	sentence_indexer::Entry getEntry(std::string term);
	void padMap(std::map<std::string, std::vector<double> > & map,
			unsigned length);
	void incMap(std::map<std::string, std::vector<double> > & map);

private:
	std::vector<Document> docs;
	std::vector<sentence> sentences;
	std::vector<sentence_indexer::Entry> index;
	std::map<std::string, sentence> sentenceNames_sents;
	bool normalized;
	double docCount;

};

#endif /* SENTENCE_INDEXER_H_ */
