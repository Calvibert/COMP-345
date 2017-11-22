/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class indexes and queries complete documents
 *
 */

#include "document_indexer.h"

/**
 * default constructor
 */
document_indexer::document_indexer() {
	normalized = false;
	docCount = 0;
	index = {};
}

/**
 * returns the number of documents processed by the indexer
 * @return the number
 */
int document_indexer::size() {
	return docCount;
}

/**
 * Sets the number of documents processed by the indexer
 * @param s value
 */
void document_indexer::setDocCount(int s) {
	docCount = s;
}

/**
 * Takes a Document object on the LS, an Indexer on RS
 * @param doc document of interest
 * @param indexer document_indexer of interest
 */
void operator>>(index_item doc, document_indexer & indexer) {
	word_tokenizer tokenizer;
	std::vector<std::string> tokens = tokenizer.splitIntoTokens(doc.content());
	std::vector<document_indexer::Entry> index = indexer.getIndex();

	std::vector<std::string> docNames = indexer.getDocNames();
	docNames.push_back(doc.name());
	std::map<std::string, index_item> docName_doc = indexer.getDocNameDoc();
	docName_doc[doc.name()] = doc;
	indexer.setDocNameDoc(docName_doc);

	for (unsigned i = 0; i < tokens.size(); ++i) {
		bool exists = false;
		for (unsigned j = 0; j < index.size(); ++j) {
			if (index[j].term == tokens[i]) {
				// Token is in index already
				for (unsigned k = 0; k < index[j].docs.size(); ++k) {
					if (index[j].docs[k].name() == doc.name()) {
						index[j].freqs[k]++;
						exists = true;
						break;
					}
					if (k == (index[j].docs.size() - 1)) {
						index[j].docs.push_back(doc);
						index[j].freqs.push_back(1);
						exists = true;
						break;
					}
				}
			}
		}

		if (!exists) {
			document_indexer::Entry entry;
			entry.term = tokens[i];
			entry.docs.push_back(doc);
			entry.freqs.push_back(1);
			index.push_back(entry);
		}

	}

	indexer.setIndex(index);
	indexer.incrementDocCount();
	indexer.resetNormalized();
}

/**
 * Helper function to increment document count
 */
void document_indexer::incrementDocCount() {
	docCount++;
}

/**
 * compute tf-idf weight of document
 */
void document_indexer::normalize() {
	double tf;
	double idf;

	for (unsigned i = 0; i < index.size(); ++i) {
		for (unsigned j = 0; j < index[i].docs.size(); ++j) {
			tf = log10(index[i].freqs[j]);
			idf = log10((docCount + 1) / index[i].docs.size());
			double tf_idf = (1 + tf) * idf;
			index[i].tf_idf.push_back(tf_idf);
		}
	}
	normalized = true;
}

/**
 * Queries the index
 * @param queryTerms the query(ies)
 * @param n number of queries
 * @return a vector of query results for the document
 */
std::vector<document_indexer::query_result> document_indexer::query(std::string queryTerms, int n) {
	std::vector<std::string> query_terms;
	std::vector<query_result> results;
	word_tokenizer tokenizer;
	std::vector<document_indexer::Entry> index = getIndex();

	if (normalized) {

		query_terms = tokenizer.splitIntoTokens(queryTerms);

		std::vector<double> query_terms_scores;
		for (unsigned i = 0; i < query_terms.size(); i++) {
			document_indexer::Entry tempEntry = getEntry(query_terms[i]);
			int thisTermDocCount = tempEntry.docs.size();
			double tf_idf = log10((docCount + 1) / (thisTermDocCount));
			if (thisTermDocCount == 0) {
				tf_idf = log10(docCount / 1);
			}
			query_terms_scores.push_back(tf_idf);
		}

		std::map<std::string, std::vector<double> > docs_tf_idfs;
		std::vector<double> emptyDbl;
		for (std::vector<std::string>::iterator it = docNames.begin();
				it != docNames.end(); ++it) {
			docs_tf_idfs[*it] = emptyDbl;
		}

		std::vector<bool> term_checked;
		for (std::vector<std::string>::const_iterator it = query_terms.begin();
				it != query_terms.end(); ++it) {
			term_checked.push_back(false);
		}

		for (std::vector<std::string>::const_iterator qt_it =
				query_terms.begin(); qt_it != query_terms.end(); ++qt_it) {
			bool found = false;
			for (std::vector<document_indexer::Entry>::const_iterator i_it =
					index.begin(); i_it != index.end(); ++i_it) {
				found = false;
				if (*qt_it == i_it->term) {
					int length;
					found = true;
					for (unsigned j = 0; j < i_it->docs.size(); ++j) {
						index_item doc = i_it->docs[j];
						std::string t = doc.name();
						std::vector<double> tempDbl = docs_tf_idfs[t];
						tempDbl.push_back(i_it->tf_idf[j]);
						docs_tf_idfs[t] = tempDbl;
						length = tempDbl.size();
					}
					padMap(docs_tf_idfs, length);
				}
				if (found) {
					break;
				}
			}
			if (!found) {
				incMap(docs_tf_idfs);
			}
		}

		std::vector<document_indexer::query_result> similarities;
		for (std::map<std::string, std::vector<double> >::const_iterator it =
				docs_tf_idfs.begin(); it != docs_tf_idfs.end(); ++it) {
			double nominator = 0;
			double query_denominator = 0;
			double doc_denominator = 0;
			for (unsigned i = 0; i < query_terms_scores.size(); ++i) {
				std::vector<double> doc_terms_scores = it->second;
				nominator += query_terms_scores[i] * doc_terms_scores[i];
				query_denominator += pow(query_terms_scores[i], 2);
				doc_denominator += pow(doc_terms_scores[i], 2);
			}
			document_indexer::query_result tempRes;
			std::string name = it->first;
			std::map<std::string, index_item> docName_doc = this->getDocNameDoc();
			index_item docu = docName_doc[name];
			tempRes.element = docu;
			query_denominator = sqrt(query_denominator);
			doc_denominator = sqrt(doc_denominator);
			double denominator = query_denominator * doc_denominator;
			tempRes.score = nominator / denominator;
			results.push_back(tempRes);
		}
//		std::cout << "before" << std::endl;
//		for (unsigned i = 0; i < results.size(); ++i) {
//			std::cout << results[i].doc.getFileName() << ": "
//					<< results[i].score << std::endl;
//		}
		results = sort(results, n);
		std::cout << "Sorted result" << std::endl;
		for (unsigned i = 0; i < results.size(); ++i) {

			std::cout << results[i].element.name() << ": "
					<< results[i].score << std::endl;
		}

	} else {
		std::cout << "Please normalize your data set before querying."
				<< std::endl;
	}

	return results;

}
/**
 * finds a given term in a vector
 * @param vector the vector to be searched
 * @param term the term to find
 * @return where it was found
 */
int document_indexer::findInVector(const std::vector<std::string> & vector,
		const std::string & term) {
	for (unsigned i = 0; i < vector.size(); ++i) {
		if (vector[i] == term) {
			return i;
		}
	}
	return -1;
}

/**
 * Finds a given term in a map
 * @param map the map to be searched
 * @param term the term to find
 * @return where it was found
 */
std::string document_indexer::findInMap(
		const std::map<std::string, std::vector<double> > & map,
		const std::string & term) {
	for (std::map<std::string, std::vector<double> >::const_iterator it =
			map.begin(); it != map.end(); ++it) {
		if (it->first == term) {
			return it->first;
		}
	}
	return "not found";
}

/**
 * Pad the vector for the elements that weren't in the query term
 * @param map
 * @param length
 */
void document_indexer::padMap(std::map<std::string, std::vector<double> > & map,
		unsigned length) {
	for (std::map<std::string, std::vector<double> >::iterator it = map.begin();
			it != map.end(); ++it) {
		if (it->second.size() < length) {
			double zero = 0;
			std::vector<double> tempDbl = it->second;
			tempDbl.push_back(zero);
			it->second = tempDbl;
		}
	}
}

/**
 * pad the vector of all elements (none had the query term)
 * @param map
 */
void document_indexer::incMap(std::map<std::string, std::vector<double> > & map) {
	for (std::map<std::string, std::vector<double> >::iterator it = map.begin();
			it != map.end(); ++it) {
		double zero = 0;
		std::vector<double> tempDbl = it->second;
		tempDbl.push_back(zero);
		it->second = tempDbl;
	}
}

/**
 * Getter for the document associated with the name
 * @param name the string/name of interest
 * @return the index_item
 */
index_item document_indexer::getDocFromName(std::string name) {
	return docName_doc[name];
}

/**
 * Getter for the index
 * @return a vector of entires
 */
std::vector<document_indexer::Entry> document_indexer::getIndex() const {
	return index;
}

/**
 * Sets the Indexer's normalized toggle to false.
 * normalize() must be run again
 */
void document_indexer::resetNormalized() {
	normalized = false;
}

/**
 * Meaningful output operator of the Indexer object
 * @param os string to be output
 * @param id the document_indexer
 * @return the output
 */
std::ostream& operator<<(std::ostream& os, const document_indexer& id) {
	os << "Doc count: " << id.docCount << ",";
	os << "" << id.index[0].docs.size();
	return os;
}

/**
 * Displays the results in a meaningful way
 * @param results query results
 * @return the output
 */
std::string document_indexer::toString(std::vector<document_indexer::query_result> results) {
	std::string output = "";
	if (normalized) {
		if (results.size() > 0) {
			output += "List of the most relevant documents and their score:\n";
			output += "----------------------------------------------------\n";
			for (unsigned i = 0; i < results.size(); i++) {
				output += "Document: " + results[i].element.name() + "\n"
						+ "Score: ";
				output += results[i].score;
				output += "\n";
				output +=
						"----------------------------------------------------\n";
			}
		} else {
			output += "Your search term matched no documents.\n";
		}
	}
	return output;
}

/**
 * getter for the document count
 * @return
 */
int document_indexer::getDocCount() const {
	return docCount;
}

/**
 * setter for the index
 * @param i a vector of document_indexer entries
 */
void document_indexer::setIndex(std::vector<document_indexer::Entry> i) {
	index = i;
}

/**
 * getter for an entry
 * @param term to find the entry of
 * @return the entry
 */
document_indexer::Entry document_indexer::getEntry(std::string term) {
	for (unsigned i = 0; i < index.size(); ++i) {
		if (index[i].term == term) {
			return index[i];
		}
	}
	document_indexer::Entry empty;
	return empty;
}

/**
 * getter for the document names
 * @return a vector of document names
 */
std::vector<std::string> document_indexer::getDocNames() {
	return docNames;
}

/**
 * getter for map of document names and their index item
 * @return the map
 */
std::map<std::string, index_item> document_indexer::getDocNameDoc() {
	return docName_doc;
}

/**
 * setter for map of document names and their index item
 * @param map to be set
 */
void document_indexer::setDocNameDoc(std::map<std::string, index_item> map) {
	docName_doc = map;
}

/**
 * Sort the query results
 * @param results to be sorted
 * @param max numeber of them
 * @return the sorted vector of query results
 */
std::vector<document_indexer::query_result> document_indexer::sort(std::vector<document_indexer::query_result> results, int max) {
	std::vector<document_indexer::query_result> sorted;
	std::vector<bool> done;
	for (unsigned i = 0; i<results.size(); ++i) {
		done.push_back(false);
	}
	if (docCount < max) {
		max = docCount;
	}
	for (int i = 0; i<max; ++i) {
		document_indexer::query_result highest;
		highest.score = 0;
		for (unsigned j = 0; j<results.size(); ++j) {
			if (done[j]) {
				continue;
			}
			if (highest.score < results[j].score) {
				highest = results[j];
				done[j] = true;
			}
		}
		sorted.push_back(highest);
	}
	return sorted;
}

