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
	//void readFile();
	std::string name() const;
//	std::string content() const;
	int size() const;

	friend std::ostream& operator<<(std::ostream& os, const sentence& s);

	std::string getFileName() const;
	int getLongestWord() const;
	std::string getContent() const;
	int getPos() const;
	Document getDocument();

protected:
	void setFileName(std::string newName);
	void setLongestWord(int newLongest);
	void setContent(std::string t);
	void setDocument(Document & d);

private:
	std::string contents;
	std::string filename;
	Document doc;
	int longestWord;
	int pos;

};
#endif /* SENTENCE_H_ */
