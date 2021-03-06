/*
 * Indexer.h
 *
 *  Created on: Oct 17, 2017
 *      Author: samue
 */

#include "Indexer.h"
#include "Document.h"
#include "Tokenizer.h"

// Default constructor
Indexer::Indexer() {
	normalized = false;
	docCount = 0;
	index = {};
}

// Return the number of documents processed by the Indexer
int Indexer::size() {
	return docCount;
}
void Indexer::setDocCount(int s){
	docCount = s;
}

// Takes a Document object on the LS, an Indexer on RS
// Processes the Doc's text into tokens
// Processes the tokens into the index data structure
// After this operation, the Indexer must be normalized before being queried
void operator>>(Document doc, Indexer * indexer) {
	// First: Process Document with a tokenizer object
	Tokenizer tokenizer;
	std::vector<std::string> tokens = tokenizer.splitIntoTokens(doc.getText());
	std::vector<Indexer::Entry> index = indexer->getIndex();

	// Second: Take the given data structure and process it into the indexer's data structures
	for (unsigned i=0; i<tokens.size(); i++) {
		for (unsigned j=0; j<index.size(); j++) {
			if (index[j].term == tokens[i]) {
				// Token is in index already
				for (unsigned k=0; k<index[j].docs.size(); k++) {
					if (index[j].docs[k] == doc.getFileName()) {
						// Entry for current doc exists
						// Increment
						index[j].freqs[k]++;
						continue;
					}
					// Add the doc name with freq 1
					index[j].docs.push_back(doc.getFileName());
					index[j].freqs.push_back(1);
					continue;
				}
			}
		}
		// No match: Create a new entry and push it on the vector
		Indexer::Entry entry;
		entry.term = tokens[i];
		entry.docs.push_back(doc.getFileName());
		entry.freqs.push_back(1);
		index.push_back(entry);
	}
	// Set the indexer's index to the current scope index:
	indexer->setIndex(index);
	// Increment the docCount
	indexer->incrementDocCount();
	// Indexer requires to be normalized again
	indexer->resetNormalized();
}

// Helper function to increment the doc count
void Indexer::incrementDocCount() {
	docCount++;
}

// For each entry, compute its tf-idf
// This operation allows querying
void Indexer::normalize() {

	double tf = 0;
	double idf = 0;

	for (unsigned i = 0; i < index.size(); ++i) {
		for (unsigned j = 0; j < index[i].docs.size(); ++j) {
			// For each term-doc pairings, compute the tf-idf
			tf = index[i].freqs[j] / docName_wordCount[index[i].docs[j]];
			idf = log(docCount / index[i].docs.size());
			index[i].tf_idf[j] = tf * idf;
		}
	}

	normalized = true;
}

// Operation to query the index
// The query terms are first tokenized by a Tokenizer
// The results vector of query_result then gets appended by the matching term-document pairs
// It does this while making sure that the appended query_result are among the top n highest
// tf-idf scoring matches.
// The result is then returned
std::vector<Indexer::query_result> Indexer::query(std::string queryTerms,
		int n) {
	std::vector<std::string> query_terms;
	std::vector<Indexer::query_result> results;
	int count;
	int lowestScore;
	Tokenizer tokenizer;



	if (normalized) {
		// First: process the terms in a vector<string>
		query_terms = tokenizer.splitIntoTokens(queryTerms);

		query_result singleResult;
		// Second: Find out which term-doc pair matches with the query term
		for (unsigned i = 0; i < index.size(); ++i) {
			for (unsigned j = 0; j < query_terms.size(); ++j) {
				if (index[i].term == query_terms[j]) {
					// We got a match!
					std::cout << "Match!" << std::endl;
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
		// Print the query results
		toString(results);
	} else {
		std::cout << "Please normalize your data set before querying." << std::endl;
	}

	return results;

}


// Return the index of the Indexer
std::vector<Indexer::Entry> Indexer::getIndex() const {
	return index;
}

// Sets the Indexer's normalized toggle to false.
// normalize() must be run again
void Indexer::resetNormalized() {
	normalized = false;
}

// Meaningful output operator of the Indexer object
std::ostream& operator<<(std::ostream& os, const Indexer& id) {
	os << "Doc count: " << id.docCount << ",";
	os << "" << id.index[0].docs.size();
	return os;
}

//Document operator[](int key){
//
//}

std::string Indexer::toString(std::vector<Indexer::query_result> results) {
	std::string output;
	if (normalized) {
		if (results.size() < 0) {

			output += "List of the most relevant documents and their score:\n";
			output += "------------------------------------------------------";
			for (unsigned i = 0; i < results.size(); i++) {
				output += "Document: " + results[i].doc.getFileName() + "\n"
						+ "Score: ";
				output += results[i].score;
				output += "\n";
				output +=
						"------------------------------------------------------";
			}
		} else {
			output += "Your search term matched no documents.\n";
		}
	}
	return output;
}

int Indexer::getDocCount() const {
	return docCount;
}

void Indexer::setIndex(std::vector<Indexer::Entry> i) {
	index = i;
}
