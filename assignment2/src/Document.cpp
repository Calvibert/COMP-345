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

using namespace std;

Document::Document() {
	fileName = "";
	longestWord = 0;
}

Document::Document(std::string newFileName) {
	fileName = newFileName;
	longestWord = 0;
}

bool Document::compareEntries(TermDoc item, string term) {
	if (item.term == term) {
		return true;
	}
	return false;
}

bool isStopWord(std::string word, std::vector<std::string> stopWords) {
	return find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}

int Document::findIndex(string word) {
	for (std::vector<TermDoc>::iterator it = dict.begin(); it != dict.end();
			++it) {
		if (compareEntries(*it, word)) {
			int index = it - dict.begin();
			return index;
		}
	}
	return -1;
}

void Document::processFile(vector<string> stopWords) {
	if (fileName != "") {
		std::ifstream fin(fileName);
		std::string currentWord;
		TermDoc temp;

		if (!fin) {
			throw "Error opening input file. Closing";
		}

		// Loop through file, read each word into the vector of tokens
		while (fin >> currentWord) {
			// Remove punctuation
			currentWord = containsPunctuation(currentWord);
			// Transform term to lower case using built in method
			transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

			// Update longestWord if necessary
			if (currentWord.length() > longestWord) {
				longestWord = currentWord.length();
			}

			// Check for the stop word list:
			if (!stopWords.empty()) {
				// Skip rest if it is a stop word
				bool result = isStopWord(currentWord, stopWords);
				if (result) {
					continue;
				}
			}

			// Check if current word is in dict
			if (int index = findIndex(currentWord) > 0) {
				increment(index);
				// If not, add it
			} else {
				// Otherwise, it's a new entry so its frequency is 1. Push to the vector
				temp.freq = 1;
				dict.push_back(temp);
			}

		}
		fin.close();
	}
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
// End getters and setters

Document::~Document() {
	// TODO Auto-generated destructor stub
}



