/*
 * sentence.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "sentence.h"

sentence::sentence() {
	setName("");
	setContent("");
	Document d;
	doc = d;
	pos = 0;
}

sentence::sentence(Document & d, int p, std::string c){
	setName(d.name());
	setContent(c);
	setDocument(d);
	pos = p;
}

sentence::~sentence() {}

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
	os << s.content() << std::endl;
	return os;
}
