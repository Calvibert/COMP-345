/*
 * indexer.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include "index_item.h"

class indexer {
public:
	struct query_result {
		index_item element;
		double score;
	};
};

#endif /* INDEXER_H_ */
