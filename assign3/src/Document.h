/*
 * Document.h
 *
 *  Created on: Nov 1, 2017
 *      Author: Maude
 */

#ifndef SRC_DOCUMENT_H_
#define SRC_DOCUMENT_H_

#include "index_item.h"

class Document: public index_item {
public:
	Document();
	Document(std::string f);
	virtual ~Document();
	//void readFile();
	const std::string name() const;
	const std::string content() ;
	int size() const;

	friend std::ostream& operator<<(std::ostream& os, const Document& d);

	std::string getFileName() const;
	int getLongestWord() const;
	std::string getContent() const;

protected:
	void setFileName(std::string newName);
	void setLongestWord(int newLongest);
	void setContent(std::string t);

private:
	std::string contents;
	std::string filename;
	int longestWord;
	int wordCount;
};

#endif /* SRC_DOCUMENT_H_ */
