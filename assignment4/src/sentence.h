/*
 * sentence.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef SENTENCE_H_
#define SENTENCE_H_

#include "index_item.h"
#include "Document.h"

class sentence: public index_item {
public:
	sentence();
	sentence(Document & d, int p, std::string c);
	virtual ~sentence();

	int getPos() const;
	Document getDocument();
	void setDocument(Document & d);

	friend std::ostream& operator<<(std::ostream& os, const sentence& s);

private:
	Document doc;
	int pos;

};
#endif /* SENTENCE_H_ */
