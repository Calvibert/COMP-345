/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class indexes and queries complete documents
 *
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
		std::vector<index_item> docs;
		std::vector<double> freqs;
		std::vector<double> tf_idf;
	};
	document_indexer();

	friend std::ostream& operator<<(std::ostream& os,
			const document_indexer& id);
	std::string toString(std::vector<document_indexer::query_result> results);

	void normalize();
	std::vector<document_indexer::query_result> query(std::string queryTerms, int n = 10);

	int size();
	void resetNormalized();
	void setDocCount(int s);
	void incrementDocCount();
	int getDocCount() const;

	std::map<std::string, index_item> getDocNameDoc();
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
	index_item getDocFromName(std::string name);
	void setDocNameDoc(std::map<std::string, index_item> map);
	std::vector<document_indexer::query_result> sort(std::vector<document_indexer::query_result> results, int max);

private:
	std::vector<document_indexer::Entry> index;
	std::map<std::string, index_item> docName_doc;
	std::vector<std::string> docNames;
	bool normalized;
	double docCount;
};

void operator>>(index_item doc, document_indexer & indexer);

#endif /* DOCUMENT_INDEXER_H_ */
