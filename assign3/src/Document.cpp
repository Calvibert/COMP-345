/*
 * Document.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Maude
 */

#include "Document.h"

Document::Document() {
	setFileName("");
	setLongestWord(0);
	setContent("");
}

Document::Document(std::string f){
	setFileName(f);
	setContent(index_item::readFile(f));
	setLongestWord(0);
}

Document::~Document() {
}

// Return the filename of the Document
const std::string Document::name() const{
	return filename;
}

// Return the text in the document
const std::string Document::content(){
	return contents;
}

// Return the number of characters in the text
int Document::size() const{
	return getContent().length();
}


// Various getters and setters
std::string Document::getFileName() const{
	return filename;
}

void Document::setFileName(std::string newName) {
	filename = newName;
}

int Document::getLongestWord() const {
	return longestWord;
}

void Document::setLongestWord(int newLongest) {
	longestWord = newLongest;
}

std::string Document::getContent() const{
	return contents;
}

void Document::setContent(std::string t){
	contents = t;
}

std::ostream& operator<<(std::ostream& os, const Document& d){
	os << d.getContent() << std::endl;
	return os;
}
