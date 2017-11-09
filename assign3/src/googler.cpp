//============================================================================
// Name        : assignment2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Document.h"
#include "word_tokenizer.h"
#include "document_indexer.h"
using namespace std;

//vector<string> indexFiles(string inputFile) {
//
//	ifstream fin(inputFile);
//	string currentLine;
//	vector<string> fileNames;
//
//	if (!fin)
//		throw "Error opening file. Closing";
//
//	while (getline(fin, currentLine))
//		fileNames.push_back(currentLine);
//	cout << "hello, world" << endl;
//	fin.close();
//	return fileNames;
//
//}
//
//int main() {
//
//	string inputfile = "googler_index.txt";
//	cout << "Gathering files from index file..." << endl;
//	vector<string> filenames = indexFiles(inputfile);
//	cout << "Creating Document objects, pushing to indexer" << endl;
//
//	document_indexer idxr;
//
//	for (vector<string>::const_iterator i = filenames.begin();
//			i != filenames.end(); ++i) {
//		Document temp(*i);
//		temp >> idxr;
//	}
//
//	idxr.normalize();
//
//	string keywords;
//	cout << "Please enter your query: " << endl;
//
//	getline(cin, keywords);
//
//	// Query with the default 10 best documents match
//	vector<document_indexer::query_result> results = idxr.query(keywords);
//
//
//	return 0;
//}
