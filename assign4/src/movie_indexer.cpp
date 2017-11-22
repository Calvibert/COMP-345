/*
 * movieindexer.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: samue
 */

#include "movie_indexer.h"

namespace std {

movie_indexer::movie_indexer() {

}

movie_indexer::~movie_indexer() {

}

void movie_indexer::readDocument(std::string matadatafile,
		std::string plotfile) {
	Document meta(matadatafile);
	Document plot(plotfile);
	movie_tokenizer m_t;
	// Will get all the right info for the initial movies setup
	movies = m_t.splitIntoMovies(meta);

	// Will complete the movies setup
	movies = m_t.addPlot(plot);

	// Let's see what we got
	std::cout << m_t << endl;

	setMovies(m_t.getMovies());

	word_tokenizer w_t;
	std::vector<std::string> contents;

	for (unsigned i = 0; i < movies.size(); ++i) {
		Entry newEntry;
		newEntry.name = movies[i].name();
		newEntry.movie = movies[i];
		contents = w_t.splitIntoTokens(movies[i].content());
		newEntry.content = contents;
		entries.push_back(newEntry);
	}

	setNormalized(false);
}

void movie_indexer::normalize() {
	std::string content;
	std::vector<std::string> tokens;

	std::vector<movie_indexer::Entry> entries = getEntries();

	std::cout << "normalizing" << std::endl;

	// go through the entries
	for (unsigned i = 0; i < entries.size(); ++i) {
		tokens = entries[i].content;

		for (unsigned j = 0; j < tokens.size(); ++j) {
			double f = getFrequency(tokens, tokens[j]);
			double tf = 1 + log10(f);
			double d = getDocumentFrequency(tokens[j]);
			double df = log10(movies.size() / d);
			setTfIdf(tf * df, i);
		}
	}
	std::cout << "Done normalizing." << std::endl;
	setNormalized(true);
}

std::vector<movie> movie_indexer::recommend(std::string movieTitle, int number) {
	std::vector<movie> recommendations;
	std::vector<movie_indexer::Entry> entries = getEntries();

	if (!getNormalizer()) {
		std::cout << "Please normalize the index before querying" << std::endl;
	}

	int index = findMovieByName(movieTitle);

	std::cout << entries[index].name << std::endl;

	std::vector<double> similarities;
	std::vector<movie> movies;
	movie_indexer::Entry sEntry = entries[index];
	for (unsigned i = 0; i < entries.size(); ++i) {
		similarities.push_back(computeSimilarity(sEntry, entries[i]));
	}

	movies = sortResults(similarities, movies, number);

	return recommendations;
}

void movie_indexer::setMovies(std::vector<movie> movs) {
	movies = movs;
}

int movie_indexer::getFrequency(std::vector<std::string> tokens, std::string term) {
	int freq = 0;
	for (unsigned i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == term) {
			++freq;
		}
	}
	return freq;
}

std::vector<movie_indexer::Entry> movie_indexer::getEntries() {
	return entries;
}

int movie_indexer::getDocumentFrequency(std::string term) {
	int docFreq = 0;
	std::vector<Entry> entries = getEntries();
	for (unsigned i = 0; i < entries.size(); ++i) {
		for (unsigned j = 0; j < entries[i].content.size(); ++j) {
			if (entries[i].content[j] == term) {
				++docFreq;
				break;
			}
		}
	}
	return docFreq;
}

void movie_indexer::setTfIdf(double tf_idf, int index) {
	std::vector<movie_indexer::Entry> entries = getEntries();
	entries[index].tf_idf.push_back(tf_idf);
}

std::vector<movie> movie_indexer::getMovies() {
	return movies;
}

int movie_indexer::findMovieByName(std::string title) {
	int index;
	std::vector<movie> movies = getMovies();
	for (unsigned i = 0; i < movies.size(); ++i) {
		if (movies[i].name() == title) {
			index = i;
			break;
		}
	}
	return index;
}

double movie_indexer::computeSimilarity(movie_indexer::Entry sEntry, movie_indexer::Entry eEntry) {
	double similarity;
	double nom;
	double sDenom;
	double eDenom;
	std::vector<double> sMatches;
	std::vector<double> eMatches;
	std::vector<std::string> sContent = sEntry.content;
	std::vector<std::string> eContent = eEntry.content;
	for (unsigned i = 0; i < sContent.size(); ++i) {
		for (unsigned j = 0; j < eContent.size(); ++j) {
			if (sContent[i] == eContent[j]) {
				sMatches.push_back(sEntry.tf_idf[i]);
				eMatches.push_back(eEntry.tf_idf[j]);
			}
		}
	}

	for (unsigned w = 0; w < sMatches.size(); ++w) {
		// compute similarity
		nom += sMatches[w] * eMatches[w];
		sDenom += sMatches[w];
		eDenom += eMatches[w];
	}
	sDenom = sqrt(sDenom);
	eDenom = sqrt(eDenom);
	similarity = nom / (sDenom * eDenom);
	return similarity;
}

std::vector<movie> movie_indexer::sortResults(std::vector<double> similarities, std::vector<movie> movies, int limit) {
	std::vector<movie> m;
	std::vector<double> sorted;
	double currentLowest = 0;
	int lowestIndex;
	int count = 0;

	for (unsigned i = 0; i < similarities.size(); ++i) {
		if (similarities[i] < currentLowest && count < limit) {
			m.push_back(movies[i]);
			++count;
			currentLowest = similarities[i];
			lowestIndex = i;
			continue;
		}
		if (similarities[i] > currentLowest) {
			m[lowestIndex] = movies[i];
		}
	}
	return m;
}

} /* namespace std */
