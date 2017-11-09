/*
 * sentence_indexer.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "sentence_indexer.h"

sentence_indexer::sentence_indexer() {
	normalized = false;
	docCount = 0;
}

void sentence_indexer::readDocument(std::string fileName) {
	Document doc(fileName);
	addDoc(doc);
	sentence_tokenizer s_t;
	std::vector<sentence> sent_v = s_t.splitIntoSentences(doc);
	addSentences(sent_v);

	word_tokenizer w_t;
	std::vector<std::string> terms;
	for (std::vector<sentence>::const_iterator it = sent_v.begin();
			it != sent_v.end(); ++it) {
		terms = w_t.splitIntoTokens(it->getContent());
		sentence s = getSentence(it->getFileName());
		for (std::vector<std::string>::const_iterator tit = terms.begin();
				tit != terms.end(); ++tit) {
			addToIndex(*tit, s);
		}

	}
	normalized = false;
	incDocCount();
}

void sentence_indexer::addToIndex(std::string term, sentence & sent) {
	for (std::vector<sentence_indexer::Entry>::iterator it = index.begin();
			it != index.end(); ++it) {
		if (it->term == term) {
			std::vector<sentence> tempSents = it->sents;
			std::vector<double> tempFreqs = it->freqs;
			for (unsigned i = 0; i < tempSents.size(); ++i) {
				if ((tempSents[i].getFileName() == sent.getFileName())
						&& (tempSents[i].getPos() == sent.getPos())) {
					tempFreqs[i] = ++tempFreqs[i];
					it->freqs = tempFreqs;
					return;
				}
			}
			tempSents.push_back(sent);
			tempFreqs.push_back(1);
			return;
		}
	}
	sentence_indexer::Entry newEntry;
	newEntry.term = term;
	newEntry.sents.push_back(sent);
	newEntry.freqs.push_back(1);
	index.push_back(newEntry);
}

void sentence_indexer::normalize() {
	double tf;
	double idf;

	for (unsigned i = 0; i < index.size(); ++i) {
		for (unsigned j = 0; j < index[i].sents.size(); ++j) {
			tf = log10(index[i].freqs[j]);
			idf = log10((docCount + 1) / index[i].sents.size());
			double tf_idf = (1 + tf) * idf;
			index[i].tf_idf.push_back(tf_idf);
		}
	}
	normalized = true;
}

std::vector<sentence_indexer::query_result> sentence_indexer::query(std::string queryTerms, int maxWords) {
	std::vector<sentence_indexer::query_result> results;
	std::map<std::string, sentence> sentsNamesSents = getSentenceNamesSents();

	if (!normalized) {
		std::cout << "Please normalize the index before querying." << std::endl;
		return results;
	}

	word_tokenizer wt;
	std::vector<std::string> query_terms = wt.splitIntoTokens(queryTerms);

	std::vector<double> query_terms_scores;
	for (unsigned i = 0; i < query_terms.size(); i++) {
		sentence_indexer::Entry tempEntry = getEntry(query_terms[i]);
		int thisTermDocCount = tempEntry.sents.size();
		double tf_idf = log10((docCount + 1) / (thisTermDocCount));
		if (thisTermDocCount == 0) {
			tf_idf = log10(docCount / 1);
		}
		query_terms_scores.push_back(tf_idf);
	}

	std::map<std::string, std::vector<double> > sents_tf_idfs;
	std::vector<double> emptyDbl;
	for (unsigned it = 0; it < sentences.size(); ++it) {
		std::string filename = sentences[it].getFileName();
		std::string pos = std::to_string(sentences[it].getPos());
		std::string identifier = filename + "-" + pos;
		sentsNamesSents[identifier] = sentences[it];
		sents_tf_idfs[identifier] = emptyDbl;
	}

	std::vector<bool> term_checked;
	for (std::vector<std::string>::const_iterator it = query_terms.begin();
			it != query_terms.end(); ++it) {
		term_checked.push_back(false);
	}

	for (std::vector<std::string>::const_iterator qt_it = query_terms.begin();
			qt_it != query_terms.end(); ++qt_it) {
		bool found = false;
		for (std::vector<sentence_indexer::Entry>::const_iterator i_it = index.begin();
				i_it != index.end(); ++i_it) {
			found = false;
			if (*qt_it == i_it->term) {
				int length;
				found = true;
				for (unsigned j = 0; j < i_it->sents.size(); ++j) {
					sentence sent = i_it->sents[j];
					Document tempDoc = sent.getDocument();
					std::string identifier = tempDoc.getFileName() + "-" + std::to_string(sent.getPos());
					std::vector<double> tempDbl = sents_tf_idfs[identifier];
					tempDbl.push_back(i_it->tf_idf[j]);
					sents_tf_idfs[identifier] = tempDbl;
					length = tempDbl.size();
				}
				padMap(sents_tf_idfs, length);
			}
			if (found) {
				break;
			}
		}
		if (!found) {
			incMap(sents_tf_idfs);
		}
	}

	std::vector<index_item::query_result> similarities;
	for (std::map<std::string, std::vector<double> >::const_iterator it =
			sents_tf_idfs.begin(); it != sents_tf_idfs.end(); ++it) {
		double nominator = 0;
		double query_denominator = 0;
		double sent_denominator = 0;
		for (unsigned i = 0; i < query_terms_scores.size(); ++i) {
			std::vector<double> sents_terms_scores = it->second;
			nominator += query_terms_scores[i] * sents_terms_scores[i];
			query_denominator += pow(query_terms_scores[i], 2);
			sent_denominator += pow(sents_terms_scores[i], 2);
		}
		sentence_indexer::query_result tempRes;
		std::string name = it->first;
		sentence sent = sentsNamesSents[name];
		tempRes.sent = sent;
		query_denominator = sqrt(query_denominator);
		sent_denominator = sqrt(sent_denominator);
		if (sent_denominator == 0) {
			sent_denominator = 1;
		}
		double denominator = query_denominator * sent_denominator;
		tempRes.score = nominator / denominator;
		results.push_back(tempRes);
	}

	return results;
}

void sentence_indexer::padMap(std::map<std::string, std::vector<double> > & map,
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

void sentence_indexer::incMap(std::map<std::string, std::vector<double> > & map) {
	for (std::map<std::string, std::vector<double> >::iterator it = map.begin();
			it != map.end(); ++it) {
		double zero = 0;
		std::vector<double> tempDbl = it->second;
		tempDbl.push_back(zero);
		it->second = tempDbl;
	}
}

void sentence_indexer::addDoc(Document & d) {
	docs.push_back(d);
}

void sentence_indexer::addSentences(std::vector<sentence> & vs) {
	for (std::vector<sentence>::const_iterator it = vs.begin(); it != vs.end();
			++it) {
		sentences.push_back(*it);
	}
}

sentence sentence_indexer::getSentence(std::string fileName) {
	for (std::vector<sentence>::iterator it = sentences.begin();
			it != sentences.end(); ++it) {
		if (it->getFileName() == fileName) {
			return *it;
		}
	}
	sentence empty;
	return empty;
}

void sentence_indexer::incDocCount() {
	++docCount;
}

sentence_indexer::Entry sentence_indexer::getEntry(std::string term) {
	for (unsigned i = 0; i < index.size(); ++i) {
		if (index[i].term == term) {
			return index[i];
		}
	}
	sentence_indexer::Entry empty;
	return empty;
}

std::map<std::string, sentence> sentence_indexer::getSentenceNamesSents() {
	return sentenceNames_sents;
}
