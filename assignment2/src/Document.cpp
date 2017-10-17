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

// Default constructor
Document::Document() {
	fileName = "";
	longestWord = 0;
	text = "";
}

// Constructor that takes a file name
Document::Document(std::string newFileName) {
	fileName = newFileName;
	longestWord = 0;
	text = "";
}

// Return the filename of the Document
const std::string Document::name(){
	return fileName;
}

// Return the number of characters in the text
const int Document::size(){
	return text.length();
}

// Return the text in the document
const std::string Document::content(){
	readDoc();
	return text;
}

// Read the filename. Sets the text in the Document to the content of the file
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

// Default destructor
Document::~Document() {
	// TODO Auto-generated destructor stub
}



