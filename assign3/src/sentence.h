/*
 * sentence.h
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#ifndef SENTENCE_H_
#define SENTENCE_H_

#include "index_item.h"

class sentence: public index_item {
public:
	sentence();
	sentence(std::string f);
	virtual ~sentence();
	//void readFile();
	const std::string name() const;
	const std::string content() ;
	int size() const;

	friend std::ostream& operator<<(std::ostream& os, const sentence& s);

	std::string getFileName() const;
	int getLongestWord() const;
	std::string getContent() const;
	int getPos() const;

protected:
	void setFileName(std::string newName);
	void setLongestWord(int newLongest);
	void setContent(std::string t);

private:
	std::string contents;
	std::string filename;
	int longestWord;
	int pos;
};
#endif /* SENTENCE_H_ */
