/*
 * Indexer.h
 *
 *  Created on: Oct 17, 2017
 *      Author: samue
 */

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

double Indexer::normalize() {
	// For each entry, compute its tf-idf
	// tf = freqs / wordTotal;
	// idf = log ( docsCount / docs.size());
	// tf-idf = tf * idf;

	for (unsigned i = 0; i < Indexer::index.size(); i++) {

	}
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
