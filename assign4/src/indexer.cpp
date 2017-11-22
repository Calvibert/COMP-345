/*
 * indexer.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "indexer.h"

bool indexer::isNormalized() const {
  return normalized;
}

void indexer::setNormalized(bool normalized) {
  this->normalized = normalized;
}

bool indexer::getNormalizer() {
	return normalized;
}
