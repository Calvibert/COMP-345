/*
 * index_item.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "index_item.h"


void index_item::setContent(const std::string& c) {
	itemContent = c;
}

void index_item::setName(const std::string& n) {
	filename = n;
}
void index_item::setSize(int s) {
	length = s;
}

int index_item::size() const {
	return length;
}
std::string index_item::name() const {
	return filename;
}
std::string index_item::content() const {
	return itemContent;
}
