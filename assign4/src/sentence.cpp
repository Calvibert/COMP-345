/*
 * sentence.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "sentence.h"

sentence::sentence() {
	setFileName("");
	setLongestWord(0);
	setContent("");
	Document d;
	doc = d;
	pos = 0;
}

sentence::sentence(Document & d, int p, std::string c){
	setFileName(d.getFileName());
	setContent(c);
	setLongestWord(0);
	setDocument(d);
	pos = p;
}

sentence::~sentence() {
}

// Return the filename of the Document
std::string sentence::name() const {
	return filename;
}

// Return the text in the document
//std::string sentence::content() const{
//	//readFile();
//	return contents;
//}

// Return the number of characters in the text
int sentence::size() const{
	std::string sentence = getContent().substr(pos); //substr(pos, endOfSentence)
	return sentence.length();
}


// Various getters and setters
std::string sentence::getFileName() const{
	return filename;
}

void sentence::setFileName(std::string newName) {
	filename = newName;
}

int sentence::getLongestWord() const {
	return longestWord;
}

void sentence::setLongestWord(int newLongest) {
	longestWord = newLongest;
}

std::string sentence::getContent() const{
	return contents;
}

void sentence::setContent(std::string t){
	contents = t;
}

int sentence::getPos() const {
	return pos;
}

void sentence::setDocument(Document & d) {
	doc = d;
}

Document sentence::getDocument() {
	return doc;
}

std::ostream& operator<<(std::ostream& os, const sentence& s){
	os << s.getContent() << std::endl;
	return os;
}
