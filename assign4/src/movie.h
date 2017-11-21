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
	virtual ~movie();
};

} /* namespace std */

#endif /* MOVIE_H_ */
