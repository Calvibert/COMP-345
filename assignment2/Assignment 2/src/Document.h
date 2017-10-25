/*
 * document.h
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include <vector>

class Document {
public:

	Document();
	Document(std::string fileName);
	friend const operator<<(std::ostream & os,
			Document doc);
	const std::string name(); 	// Return document filename
	const int size();			// Return size in characters
	const std::string content();	// Return content

	void readDoc();

	std::string getFileName();
	void setFileName(std::string newFileName);
	int getLongestWord();
	void setLongestWord(int newLongest);
	std::string getText();
	void setText(std::string t);
	virtual ~Document();

private:
	std::string fileName;
	unsigned longestWord;
	std::string text;
};

#endif /* DOCUMENT_H_ */
