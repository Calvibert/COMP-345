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
	for (std::vector<sentence>::const_iterator it = sent_v.begin(); it != sent_v.end(); ++it) {
		terms = w_t.splitIntoTokens(it->getContent());
		sentence s = getSentence(it->getFileName());
		for (std::vector<std::string>::const_iterator tit = terms.begin(); tit != terms.end(); ++tit) {
			addToIndex(*tit, s);
		}

	}
	normalized = false;
	incDocCount();
}

void sentence_indexer::addToIndex(std::string term, sentence & sent) {
	for (std::vector<sentence_indexer::Entry>::iterator it = index.begin(); it != index.end(); ++it) {
		if (it->term == term) {
			std::vector<sentence> tempSents = it->sents;
			std::vector<double> tempFreqs = it->freqs;
			for (unsigned i = 0; i < tempSents.size(); ++i) {
				if ((tempSents[i].getFileName() == sent.getFileName()) && (tempSents[i].getPos() == sent.getPos())) {
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

void sentence_indexer::addDoc(Document & d) {
	docs.push_back(d);
}

void sentence_indexer::addSentences(std::vector<sentence> & vs) {
	for (std::vector<sentence>::const_iterator it = vs.begin(); it != vs.end(); ++it) {
		sentences.push_back(*it);
	}
}

sentence sentence_indexer::getSentence(std::string fileName) {
	for (std::vector<sentence>::iterator it = sentences.begin(); it != sentences.end(); ++it) {
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

