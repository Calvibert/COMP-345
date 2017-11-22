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

namespace std {

class movie_indexer: public indexer {
public:
  struct Entry {
    std::string term;
    std::vector<movie> movies;
    std::vector<double> freqs;
    std::vector<double> tf_idf;
  };
  movie_indexer();
  virtual ~movie_indexer();
  void readDocument(std::string matadatafile, std::string plotfile);
  void normalize();
  std::vector<movie> recommend(std::string movieTitle);

  std::vector<movie> getMovies();

private:
  std::vector<movie> movies;
};

} /* namespace std */

#endif /* MOVIE_INDEXER_H_ */
