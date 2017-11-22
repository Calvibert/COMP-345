/*
 * movie.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: samue
 */

#include "movie.h"

namespace std {

movie::movie() {
	// TODO Auto-generated constructor stub

}

movie::~movie() {
	// TODO Auto-generated destructor stub
}

void movie::setReleaseDate(const std::string& releaseDate) {
  this->releaseDate = releaseDate;
}

const std::string& movie::getReleaseDate() const {
  return releaseDate;
}

void movie::setId(std::string id) {
  this->id = id;
}

std::string movie::getId() const {
  return id;
}


} /* namespace std */
