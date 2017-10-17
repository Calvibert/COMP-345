/*
 * document.cpp
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#include "Document.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


Document::Document() {
	fileName = "";
	longestWord = 0;
	text = "";
}

Document::Document(std::string newFileName) {
	fileName = newFileName;
	longestWord = 0;
	text = "";
}

const std::string Document::name(){
	return fileName;
}

const int Document::size(){
	return text.length();
}

const std::string Document::content(){
	readDoc();
	return text;
}

void Document::readDoc(){
	std::ifstream fin(fileName);
	if(!fin){
		throw "Error opening file. Closing";

	}
	std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
	setText(content);
}

// Various getters and setters
std::string Document::getFileName() {
	return fileName;
}

void Document::setFileName(std::string newName) {
	fileName = newName;
}

int Document::getLongestWord() {
	return longestWord;
}

void Document::setLongestWord(int newLongest) {
	longestWord = newLongest;
}

std::string Document::getText(){
	return text;
}

void Document::setText(std::string t){
	text = t;
}

// End getters and setters

Document::~Document() {
	// TODO Auto-generated destructor stub
}



