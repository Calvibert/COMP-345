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

void Indexer::setDocCount(int s) {
	docCount = s;
}

// Takes a Document object on the LS, an Indexer on RS
void operator>>(Document doc, Indexer & indexer) {
	Tokenizer tokenizer;
	std::vector<std::string> tokens = tokenizer.splitIntoTokens(doc.getText());
	std::vector<Indexer::Entry> index = indexer.getIndex();

	std::vector<std::string> docNames = indexer.getDocNames();
	docNames.push_back(doc.getFileName());
	std::map<std::string, Document> docName_doc = indexer.getDocNameDoc();
	docName_doc[doc.getFileName()] = doc;
	indexer.setDocNameDoc(docName_doc);

	for (unsigned i = 0; i < tokens.size(); ++i) {
		bool exists = false;
		for (unsigned j = 0; j < index.size(); ++j) {
			if (index[j].term == tokens[i]) {
				// Token is in index already
				for (unsigned k = 0; k < index[j].docs.size(); ++k) {
					if (index[j].docs[k].getFileName() == doc.getFileName()) {
						index[j].freqs[k]++;
						exists = true;
						break;
					}
					if (k == (index[j].docs.size() - 1)) {
						index[j].docs.push_back(doc.getFileName());
						index[j].freqs.push_back(1);
						exists = true;
						break;
					}
				}
			}
		}

		if (!exists) {
			Indexer::Entry entry;
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

// Helper function to increment the doc count
void Indexer::incrementDocCount() {
	docCount++;
}

// For each entry, compute its tf-idf
void Indexer::normalize() {
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

// Operation to query the index
std::vector<Indexer::query_result> Indexer::query(std::string queryTerms,
		int n) {
	std::vector<std::string> query_terms;
	std::vector<Indexer::query_result> results;
	Tokenizer tokenizer;
	std::vector<Indexer::Entry> index = getIndex();

	if (normalized) {

		query_terms = tokenizer.splitIntoTokens(queryTerms);

		std::vector<double> query_terms_scores;
		for (unsigned i = 0; i < query_terms.size(); i++) {
			Indexer::Entry tempEntry = getEntry(query_terms[i]);
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
			for (std::vector<Indexer::Entry>::const_iterator i_it =
					index.begin(); i_it != index.end(); ++i_it) {
				found = false;
				if (*qt_it == i_it->term) {
					int length;
					found = true;
					for (unsigned j = 0; j < i_it->docs.size(); ++j) {
						Document doc = i_it->docs[j];
						std::string t = doc.getFileName();
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

		// Output the scores
//		for (std::vector<double>::const_iterator it =
//				query_terms_scores.begin(); it != query_terms_scores.end();
//				++it) {
//			std::cout << *it << std::endl;
//		}
//
//		for (std::map<std::string, std::vector<double> >::const_iterator it =
//				docs_tf_idfs.begin(); it != docs_tf_idfs.end(); ++it) {
//			std::cout << it->first << std::endl;
//			std::vector<double> outDbl = it->second;
//			for (unsigned i = 0; i < outDbl.size(); ++i) {
//				std::cout << outDbl[i] << std::endl;
//			}
//		}

		std::vector<query_result> similarities;
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
			query_result tempRes;
			std::string name = it->first;
			std::map<std::string, Document> docName_doc = this->getDocNameDoc();
			Document docu = docName_doc[name];
			tempRes.doc = docu;
			query_denominator = sqrt(query_denominator);
			doc_denominator = sqrt(doc_denominator);
			double denominator = query_denominator * doc_denominator;
			tempRes.score = nominator / denominator;
			results.push_back(tempRes);
		}

		for (unsigned i = 0; i < results.size(); ++i) {
			std::cout << results[i].doc.getFileName() << ": " << results[i].score << std::endl;
		}

	} else {
		std::cout << "Please normalize your data set before querying."
				<< std::endl;
	}

	return results;

}

int Indexer::findInVector(const std::vector<std::string> & vector,
		const std::string & term) {
	for (unsigned i = 0; i < vector.size(); ++i) {
		if (vector[i] == term) {
			return i;
		}
	}
	return -1;
}

std::string Indexer::findInMap(
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

void Indexer::padMap(std::map<std::string, std::vector<double> > & map,
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

void Indexer::incMap(std::map<std::string, std::vector<double> > & map) {
	for (std::map<std::string, std::vector<double> >::iterator it = map.begin();
			it != map.end(); ++it) {
		double zero = 0;
		std::vector<double> tempDbl = it->second;
		tempDbl.push_back(zero);
		it->second = tempDbl;
	}
}

Document Indexer::getDocFromName(std::string name) {
	return docName_doc[name];
//	for (std::map<std::string, Document>::const_iterator it =
//			docName_doc.begin(); it != docName_doc.end(); ++it) {
//		std::cout << "hello, world!" << std::endl;
//		Document doc = it->second;
//		std::cout << doc.getFileName() << std::endl;
//		if (it->first == name) {
//			return it->second;
//		}
//	}
//	Document empty;
//	return empty;
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

std::string Indexer::toString(std::vector<Indexer::query_result> results) {
	std::string output = "";
	if (normalized) {
		if (results.size() > 0) {
			output += "List of the most relevant documents and their score:\n";
			output += "----------------------------------------------------\n";
			for (unsigned i = 0; i < results.size(); i++) {
				output += "Document: " + results[i].doc.getFileName() + "\n"
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

int Indexer::getDocCount() const {
	return docCount;
}

void Indexer::setIndex(std::vector<Indexer::Entry> i) {
	index = i;
}

Indexer::Entry Indexer::getEntry(std::string term) {
	for (unsigned i = 0; i < index.size(); ++i) {
		if (index[i].term == term) {
			return index[i];
		}
	}
	Indexer::Entry empty;
	return empty;
}

std::vector<std::string> Indexer::getDocNames() {
	return docNames;
}

std::map<std::string, Document> Indexer::getDocNameDoc() {
	return docName_doc;
}

void Indexer::setDocNameDoc(std::map<std::string, Document> map) {
	docName_doc = map;
}
