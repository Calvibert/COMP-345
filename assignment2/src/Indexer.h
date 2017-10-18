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
#include <iostream>
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
	friend std::ostream& operator<<(std::ostream& os, const Indexer& id);
	void normalize();
	std::vector<query_result> query(std::string queryTerms, int n = 10);
	std::vector<Indexer::Entry> getIndex();
	void resetNormalized();
	void setDocCount(int s);

	friend Document operator[](int key);

	virtual ~Indexer();

private:
	std::vector<Indexer::Entry> index;
	std::map<std::string, int> docName_wordCount;
	std::map<std::string, Document> docName_doc;
	bool normalized;
	int docCount;

};

void operator>>(Document doc, Indexer indexer);
Document operator[](int key);
#endif /* INDEXER_H_ */
