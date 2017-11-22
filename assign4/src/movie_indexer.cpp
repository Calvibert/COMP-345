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

void movie_indexer::readDocument(std::string matadatafile, std::string plotfile) {
  Document meta(matadatafile);
  Document plot(plotfile);
  movie_tokenizer m_t;
  // Will get all the right info for the initial movies setup
  movies = m_t.splitIntoMovies(meta);

  // Will complete the movies setup
  movies = m_t.addPlot(plot);

  // Let's see what we got
  std::cout << m_t << endl;

  setNormalized(false);
}

void movie_indexer::normalize() {


  setNormalized(true);
}

std::vector<movie> movie_indexer::recommend(std::string movieTitle) {
  std::vector<movie> recommendations;

  if (!getNormalizer()) {
    std::cout << "Please normalize the index before querying" << std::endl;
  }


  return recommendations;
}

} /* namespace std */
