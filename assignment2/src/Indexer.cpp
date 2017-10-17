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
double Indexer::normalize() {

	int tf = 0;
	int idf = 0;

	for (unsigned i = 0; i < Indexer::index.size(); i++) {
		for (unsigned j = 0; j < index[i].freqs.size(); j++) {
			// For each term-doc pairings, compute the tf-idf
			tf = index[i].freqs[j] / doc_wordCount[index[i].docs[j]];
			idf = log(docCount / index[i].docs.size());
			index[i].tf_idf = tf * idf;
		}
	}

	normalized = true;
}

std::vector<Indexer::query_result> Indexer::query(std::string queryTerms,
		int optional) {

}

std::vector<Indexer::Entry> Indexer::getIndex() {
	return index;
}

Indexer::~Indexer() {
	// TODO Auto-generated destructor stub
}
