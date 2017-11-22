/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class represents a given document
 *
 */

#ifndef SRC_DOCUMENT_H_
#define SRC_DOCUMENT_H_

#include "index_item.h"
#include "document_indexer.h"
#include <cstdlib>

class Document: public index_item {
public:
	Document();
	Document(std::string f);
	virtual ~Document();

	std::string readFile(std::string filename);

	friend std::ostream& operator<<(std::ostream& os, const Document& d);

};

#endif /* SRC_DOCUMENT_H_ */
