/*
 * index_item.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef INDEX_ITEM_H_
#define INDEX_ITEM_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class index_item {
public:
	std::string readFile(std::string filename);
	virtual ~index_item() {}
	//virtual std::string getName() = 0;
	struct query_result {
		index_item* index_item;
		double score;
	};
};

#endif /* INDEX_ITEM_H_ */
