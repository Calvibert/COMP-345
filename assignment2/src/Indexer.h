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
#include <math.h>
#include <tgmath.h>
#include <algorithm>
#include "Document.h"

class Indexer {
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
	Indexer();

	// Output operation
	friend std::ostream& operator<<(std::ostream& os, const Indexer& id);
	std::string toString(std::vector<Indexer::query_result> results);

	void normalize();
	std::vector<query_result> query(std::string queryTerms, int n = 10);

	int size();
	void resetNormalized();
	void setDocCount(int s);
	void incrementDocCount();
	int getDocCount() const;

	std::map<std::string, Document> getDocNameDoc();
	void setIndex(std::vector<Indexer::Entry> i);
	std::vector<Indexer::Entry> getIndex() const;
	std::map<std::string, double> getDocNameWordCount() const;
	Indexer::Entry getEntry(std::string term);
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
	std::vector<Indexer::Entry> index;
	std::map<std::string, Document> docName_doc;
	std::vector<std::string> docNames;
	bool normalized;
	double docCount;

};

void operator>>(Document doc, Indexer & indexer);
//Document operator[](int key);
#endif /* INDEXER_H_ */
