/*
 * Indexer.h
 *
 *  Created on: Oct 17, 2017
 *      Author: samue
 */

#include <math.h>
#include "Indexer.h"
#include "Document.h"

Indexer::Indexer() {
	normalized = false;
	docCount = 0;
}

int Indexer::size() {
	return docCount;
}

void operator>>(const Document doc, std::vector<Indexer::Entry> index) {

}

// For each entry, compute its tf-idf
void Indexer::normalize() {

	double tf = 0;
	double idf = 0;

	for (unsigned i = 0; i < Indexer::index.size(); ++i) {
		for (unsigned j = 0; j < index[i].freqs.size(); ++j) {
			// For each term-doc pairings, compute the tf-idf
			tf = index[i].freqs[j] / docName_wordCount[index[i].docs[j]];
			idf = log(docCount / index[i].docs.size());
			index[i].tf_idf[j] = tf * idf;
		}
	}

	normalized = true;
}

std::vector<Indexer::query_result> Indexer::query(std::string queryTerms,
		int n) {
	std::vector<std::string> query_terms;
	std::vector<Indexer::query_result> results;
	int count;
	int lowestScore;
	if (normalized) {
		// First: process the terms in a vector<string>
		query_terms.push_back(queryTerms);

		query_result singleResult;
		// Second: Find out which term-doc pair matches with the query term
		for (unsigned i = 0; i < index.size(); ++i) {
			for (unsigned j = 0; j < query_terms.size(); ++j) {
				if (index[i].term == query_terms[j]) {
					singleResult.score =
							Indexer::docName_wordCount[index[i].docs[j]];
					singleResult.doc = Indexer::docName_doc[index[i].docs[j]];
					if (singleResult.score > lowestScore) {
						results.push_back(singleResult);

					} else {
						if (count < n) {
							results.push_back(singleResult);
							++count;
							lowestScore = singleResult.score;
						}
					}
				}
			}
		}
	} else {
		// TODO: Print an error message before
	}

	return results;

}

std::vector<Indexer::Entry> Indexer::getIndex() {
	return index;
}

std::ostream& operator<<(std::ostream& os, const Indexer& id) {
	os << "Doc count: " << id.docCount << ",";
	os << "" << id.index[0].docs.size();
}

Indexer::~Indexer() {
	// TODO Auto-generated destructor stub
}
