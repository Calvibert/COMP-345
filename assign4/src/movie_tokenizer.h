/*
 * movietokenizer.h
 *
 *  Created on: Nov 22, 2017
 *      Author: samue
 */

#ifndef MOVIE_TOKENIZER_H_
#define MOVIE_TOKENIZER_H_

#include "Document.h"
#include "movie.h"
#include "abstract_tokenizer.h"

namespace std {

class movie_tokenizer: public abstract_tokenizer {
public:
  movie_tokenizer();
  virtual ~movie_tokenizer();

  std::vector<movie>& splitIntoMovies(Document & doc);
  std::vector<movie>& addPlot(Document & doc);
  bool testForTitle(std::string sentence);
  bool checkIfWhitespace(std::string sentence);
  int getMovieFromId(std::string id);
  bool is_digits(const std::string &str);

  std::vector<movie> getMovies();

  friend ostream& operator<<(ostream& os, const movie_tokenizer& dt);

private:
  std::vector<movie> movies;

};

} /* namespace std */

#endif /* MOVIE_TOKENIZER_H_ */
