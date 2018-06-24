/*
 * movie.h
 *
 *  Created on: Nov 21, 2017
 *      Author: samue
 */

#ifndef MOVIE_H_
#define MOVIE_H_

#include "index_item.h"

namespace std {

class movie: public index_item {
public:
	movie();
	movie(std::string name, std::string relDate, std::string id) :
			index_item(name), releaseDate(relDate), id(id) {}
	virtual ~movie();

	std::string getId() const;
	void setId(std::string id);
	const std::string& getReleaseDate() const;
	void setReleaseDate(const std::string& releaseDate);

private:
	std::string releaseDate;
	std::string id;
};

} /* namespace std */

#endif /* MOVIE_H_ */
