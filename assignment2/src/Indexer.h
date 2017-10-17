/*
 * Indexer.h
 *
 *  Created on: Oct 17, 2017
 *      Author: samue
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include <vector>
#include <string>
#include <map>
#include "Document.h"

class Indexer {
public:
	struct Entry {
		// Members
		std::string term;
		std::vector<std::string> docs;
		std::vector<int> freqs;
		std::vector<double> tf_idf;
	};
	struct query_result {
		Document doc;
		double score;
	};
	Indexer();
	int size();
	void operator>>(const Document doc);
	double normalize();
	std::vector<query_result> query(std::string queryTerms, int optional = 10);
	std::vector<Indexer::Entry> getIndex();
	virtual ~Indexer();

private:
	std::vector<Indexer::Entry> index;
	std::map<Document, int> doc_wordCount;
	bool normalized;
	int docCount;

};

#endif /* INDEXER_H_ */
