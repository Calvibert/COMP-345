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

//	struct TermDoc {
//			// Members
//			std::string term;
//			int freq;
//
//			// Not equal operator
//			bool operator!=(const TermDoc& a) {
//				if (a.term != term) {
//					return true;
//				} else {
//					return false;
//				}
//			}
//
//			// Equal operator
//			bool operator==(const TermDoc& a) {
//				if (a.term == term) {
//					return true;
//				} else {
//					return false;
//				}
//			}
//		};

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
	//std::vector<TermDoc> dict;
	unsigned longestWord;
	std::string text;
};

#endif /* DOCUMENT_H_ */
