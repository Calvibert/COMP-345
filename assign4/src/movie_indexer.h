/*
 * movieindexer.h
 *
 *  Created on: Nov 22, 2017
 *      Author: samue
 */

#ifndef MOVIE_INDEXER_H_
#define MOVIE_INDEXER_H_

#include "indexer.h"
#include "sentence.h"
#include "movie.h"
#include "movie_tokenizer.h"
#include <vector>
#include <tgmath.h>

namespace std {

class movie_indexer: public indexer {
public:
	struct Entry {
		std::string name;
		movie movie;
		std::vector<std::string> content;
		std::vector<double> tf_idf;
	};
	movie_indexer();
	virtual ~movie_indexer();
	void readDocument(std::string matadatafile, std::string plotfile);
	void normalize();
	std::vector<movie> recommend(std::string movieTitle, int number = 5);

	int getFrequency(std::vector<std::string> tokens, std::string term);
	int getDocumentFrequency(std::string term);
	int findMovieByName(std::string title);
	double computeSimilarity(movie_indexer::Entry sEntry, movie_indexer::Entry eEntry);
	std::vector<movie> sortResults(std::vector<double> similarities, std::vector<movie> movies, int limit);

	std::vector<movie> getMovies();
	void setMovies(std::vector<movie> movies);
	std::vector<movie_indexer::Entry> getEntries();
	void setTfIdf(double tf_idf, int index);

private:
	std::vector<movie> movies;
	std::vector<movie_indexer::Entry> entries;

};

} /* namespace std */

#endif /* MOVIE_INDEXER_H_ */
