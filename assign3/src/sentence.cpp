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
	pos = 0;
}

sentence::sentence(std::string f){
	setFileName(f);
	setContent(index_item::readFile(f));
	setLongestWord(0);
	pos = 0;
}

sentence::~sentence() {
}

// Return the filename of the Document
const std::string sentence::name() const{
	return filename;
}

// Return the text in the document
const std::string sentence::content(){
	//readFile();
	return contents;
}

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

std::ostream& operator<<(std::ostream& os, const sentence& s){
	os << s.getContent() << std::endl;
	return os;
}
