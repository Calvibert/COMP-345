/*
 * document_indexer.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef DOCUMENT_INDEXER_H_
#define DOCUMENT_INDEXER_H_

#include "indexer.h"
#include "Document.h"
#include "word_tokenizer.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <math.h>
#include <tgmath.h>
#include <algorithm>

class document_indexer: public indexer {
public:
	struct Entry {
		std::string term;
		std::vector<Document> docs;
		std::vector<double> freqs;
		std::vector<double> tf_idf;
	};
	struct query_result {
		Document doc;
		double score;
	};
	document_indexer();

	// Output operation
	friend std::ostream& operator<<(std::ostream& os,
			const document_indexer& id);
	std::string toString(std::vector<document_indexer::query_result> results);

	void normalize();
	std::vector<query_result> query(std::string queryTerms, int n = 10);

	int size();
	void resetNormalized();
	void setDocCount(int s);
	void incrementDocCount();
	int getDocCount() const;

	std::map<std::string, Document> getDocNameDoc();
	void setIndex(std::vector<document_indexer::Entry> i);
	std::vector<document_indexer::Entry> getIndex() const;
	std::map<std::string, double> getDocNameWordCount() const;
	document_indexer::Entry getEntry(std::string term);
	int findInVector(const std::vector<std::string> & vector,
			const std::string & term);
	std::string findInMap(
			const std::map<std::string, std::vector<double> > & map,
			const std::string & term);
	void padMap(std::map<std::string, std::vector<double> > & map,
			unsigned length);
	std::vector<std::string> getDocNames();
	void incMap(std::map<std::string, std::vector<double> > & map);
	Document getDocFromName(std::string name);
	void setDocNameDoc(std::map<std::string, Document> map);

private:
	std::vector<document_indexer::Entry> index;
	std::map<std::string, Document> docName_doc;
	std::vector<std::string> docNames;
	bool normalized;
	double docCount;
};

#endif /* DOCUMENT_INDEXER_H_ */
