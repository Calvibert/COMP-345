///*
// * COMP 345: Assignment 1
// * Team members:
// * Samuel Dufresne		26992633
// * Maude Braunstein 	27545967
// */
//
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <algorithm>
//#include <iomanip>
//#include "index_exception.h"
//
//using namespace std;
//
//// Structure used by the program to store term, document name and frequency data
//struct dictionary {
//	string term;
//	string docName;
//	int freq;
//
//	bool operator!=(const dictionary& a) {
//		if (a.term != term || a.docName != docName) {
//			return true;
//		} else {
//			return false;
//		}
//	}
//
//	bool operator==(const dictionary& a) {
//		if (a.term == term && a.docName == docName) {
//			return true;
//		} else {
//			return false;
//		}
//	}
//
//	string toString() {
//		return this->term + ", " + this->docName;
//	}
//};
//
//// Read a file and return a vector<string> of the terms stored as a list.
//vector<string> readFile(string inputFile){
//	ifstream fin(inputFile);
//	vector<string> fileNames;
//	string currentLine;
//
//	if (!fin) {
//		throw index_exception("Error opening file. Please enter a proper file name.");
//	}
//
//	//Loop through file, read each line into the vector
//	while (getline(fin, currentLine)) {
//		fileNames.push_back(currentLine);
//	}
//
//	fin.close();
//	return fileNames;
//}
//
//// If a word contains a character specified in the array, it will remove it.
//string containsPunctuation(string word) {
//	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
//	return word;
//}
//
//// Increments the frequency of the dictionary at the indicated vector index
//void increment(vector<dictionary> &tokens, dictionary &currentDict, int index) {
//	currentDict.freq = currentDict.freq + 1;
//	tokens[index] = currentDict;
//}
//
//
//// Given a term-frequency vector, filter out words matching a certain list.
//bool isStopWord(string word, vector<string> stopWords) {
//	return find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
//}
//
//// Helper function to sort the dictionary terms
//bool sortTerms(dictionary a, dictionary b) {
//	if (a.term.compare(b.term) < 0) {
//		// a comes before b
//		return true;
//	} else {
//		if (a.term.compare(b.term) == 0) {
//			if (a.docName.compare(b.docName) < 0) {
//				return true;
//			} else {
//				return false;
//			}
//		}
//		// a comes after b or they are equal
//		return false;
//	}
//}
//
//// Uses the sort function with a helper sortTerms
//vector<dictionary> sortDict(vector<dictionary> dict) {
//	sort(dict.begin(), dict.end(), sortTerms);
//	return dict;
//}
//
//// Looks for a match of term and docName
//bool compareEntries(dictionary item, string term, string docName) {
//	if (item.term == term) {
//		if (item.docName == docName) {
//			return true;
//		}
//	}
//	return false;
//}
//
//// Looks through the vector and returns the index of the dictionary of matching term and docName
//int findIndex(vector<dictionary> dict, string term, string docName) {
//	for (std::vector<dictionary>::iterator it = dict.begin(); it != dict.end(); ++it) {
//		if (compareEntries(*it, term, docName)) {
//			int index = it - dict.begin();
//			return index;
//		}
//	}
//	return -1;
//}
//
//// Go through a file and count the frequency of each term accordingly
//// Maintains 2 vector<dictionary>. One is stopword-filtered, the other is not.
//// Maintains 2 ints of the longest term in each vector<dictionary>
//void processFile(string inputFile, vector<string> stopWordVector,
//		string::size_type & longestWord, string::size_type & longestFilteredWord,
//		vector<dictionary> & allTokens, vector<dictionary> & filteredTokens) {
//
//	ifstream fin(inputFile);
//	string currentWord;
//	dictionary tempNF, tempF;
//
//	if (!fin) {
//		throw "Error opening input file. Closing";
//	}
//
//	// Loop through file, read each word into the vector of tokens
//	while (fin >> currentWord) {
//		// Remove punctuation
//		currentWord = containsPunctuation(currentWord);
//		// Transform term to lower case using built in method
//		transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
//
//		// Update longestWord if necessary
//		if (currentWord.length() > longestWord) {
//			longestWord = currentWord.length();
//		}
//
//		// Using temporary entries to store the current word and its file name
//		tempNF.term = currentWord;
//		tempNF.docName = inputFile;
//		tempF.term = currentWord;
//		tempF.docName = inputFile;
//
//		string docName = inputFile;
//		string term = currentWord;
//
//		if (findIndex((allTokens), term, docName) > 0) {
//			increment(allTokens, allTokens[findIndex((allTokens), term, docName)],
//					findIndex((allTokens), term, docName));
//		} else {
//			// Otherwise, it's a new entry so its frequency is 1. Push to the vector
//			tempNF.freq = 1;
//			allTokens.push_back(tempNF);
//		}
//
//
//		// Is it a stop word? If not, continue
//		if (!isStopWord(currentWord, stopWordVector)) {
//			// Is this a new entry for the filtered words list? If not, increment its frequency
//			if (findIndex((filteredTokens), term, docName) > 0) {
//				increment(filteredTokens, filteredTokens[findIndex((filteredTokens), term, docName)],
//						findIndex((filteredTokens), term, docName));
//			}
//			//Otherwise, it's a new entry and we push it to the list
//			else {
//				tempF.freq = 1;
//				filteredTokens.push_back(tempF);
//				if (currentWord.length() > longestFilteredWord) {
//					longestFilteredWord = currentWord.length();
//				}
//			}
//		}
//	}
//	fin.close();
//}
//
//// Helper function to calculate the width of the table
//int getTotalWidth(vector<string> fileNames, int longestWord) {
//	// Calculate the total width of the table:
//	int width = longestWord;
//	for (unsigned a = 0; a < fileNames.size(); a++) {
//		width = width + fileNames[a].length();
//	}
//	width = width + (3 * (fileNames.size() + 2) ) - 1;
//	return width;
//}
//
//// Processes the elements to display a table of term-document frequency
//void output(vector<dictionary> dict, vector<string> fileNames, int longestWord) {
//	string previousWord = "";
//	bool firstWord = true;
//	unsigned freqCount = 0;
//
//
//	// If longest word is shorter than dictionary:
//	if (longestWord < 10) {
//		longestWord = 10;
//	}
//
//	unsigned totalWidth = getTotalWidth(fileNames, longestWord);
//
//	// Print first line:
//	cout << " " << setfill('-') << setw(totalWidth) << " " << endl;
//	cout << setfill(' ');
//
//	cout << " | " << setw(longestWord) << "Dictionary";
//	// Print all file names after Dictionary
//	for (unsigned i = 0; i < fileNames.size(); i++) {
//		cout  << " | " << fileNames[i].c_str();
//	}
//	cout << " | ";
//
//	// Prints the terms and their frequency in each document
//	for (unsigned j = 0; j < dict.size(); j++) {
//		// If new term or first term, complete the line and start the new one
//		if (previousWord != dict[j].term) {
//			// Complete the previous row:
//			if (!firstWord) {
//				for (unsigned y = freqCount; y < fileNames.size(); y++) {
//					cout << " | "  << setw(fileNames[y].length()) << "0";
//					if (y == fileNames.size() - 1) {
//						cout << " | ";
//					}
//				}
//			}
//			firstWord = false;
//			// Reset row counter
//			freqCount = 0;
//			// Start new line
//			cout << endl;
//			// Write term
//			cout << " | " << setw(longestWord)  << dict[j].term.c_str();
//		}
//
//
//		// Get the index of the term in fileNames vector
//		unsigned freqPos = find(fileNames.begin(), fileNames.end(), dict[j].docName) - fileNames.begin();
//
//		// Go through every fileName row until it reaches the position of the current element
//		for(unsigned y=freqCount; y < freqPos + 1; y++) {
//			cout << " | ";
//			if (y == freqPos) {
//				cout << setw(fileNames[y].length()) << dict[j].freq;
//			} else {
//				cout << setw(fileNames[y].length()) << "0";
//			}
//			freqCount++;
//
//			// last freq input of the line
//			if (y == (fileNames.size() - 1)) {
//				cout << " | ";
//			}
//		}
//
//		previousWord = dict[j].term;
//	}
//	// Finish padding the last line
//	for (unsigned y = freqCount; y < fileNames.size(); y++) {
//		cout << " | " << setw(fileNames[y].length()) << "0";
//		if (y == fileNames.size() - 1) {
//			cout << " | ";
//		}
//	}
//
//	cout << endl;
//	// Print last line
//	cout << " " << setfill('-') << setw(totalWidth) << " " << endl;
//	cout << setfill(' ');
//
//}
//
//int main(){
//	// PART 1: INPUT
//
//	string indexFile = "ind_index.txt";
//	vector<string> fileNames;
//
//	bool condition = true;
//	do{
//		try {
//			// Populates the vector with every line in the file (ie every file name we'll be going to next)
//			fileNames = readFile(indexFile);
//			condition = true;
//			// Sort fileNames in alphabetical order.
//			//This is necessary for the correct sorting of the terms and proper display.
//			sort(fileNames.begin(), fileNames.end());
//		}
//		catch (index_exception& e) {
//			cout << e.what() << endl;
//			condition = false;
//		}
//	}while(!condition);
//	// PART 1: END
//
//
//	// PART 2: PROCESSING
//	// Process stop words file
//	string stopWordFilename = "ind_stopwords.txt";
//	vector<string> stopWordList;
//	// Read words from the stop words list
//	stopWordList = readFile(stopWordFilename);
//
//	// File processing and storing
//	string currentFile;
//	vector<dictionary> allTokensDict;
//	vector<dictionary> filteredTokensDict;
//	// Will get the length of the longest word for both dictionaries
//	string::size_type longestWordLength = 0;
//	string::size_type longestFilteredWordLength = 0;
//
//
//	try{
//		// Iterate through the vector containing each file name
//		for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i){
//			// File we're looking at is updated here
//			currentFile = *i;
//
//			// Open the file and process every word.
//			processFile(currentFile, stopWordList, longestWordLength, longestFilteredWordLength,
//					allTokensDict, filteredTokensDict);
//		}
//	}
//	catch (const char* message){
//		//if the file doesn't open for some reason, it'll display this message instead
//		cerr << message << endl;
//	}
//
//	allTokensDict 		= sortDict(allTokensDict);
//	filteredTokensDict 	= sortDict(filteredTokensDict);
//	// PART 2: END
//
//
//	// PART 3: OUTPUT
//	cout << "DICTIONARY CONTAINING ALL TOKENS:" << endl;
//	output(allTokensDict, fileNames, longestWordLength);
//	cout << "FILTERED DICTIONARY CONTAINING NO STOP WORDS:" << endl;
//	output(filteredTokensDict, fileNames, longestFilteredWordLength);
//	// PART 3: END
//
//	return 0;
//}
