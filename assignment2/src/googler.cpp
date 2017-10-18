//============================================================================
// Name        : assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Document.h"
#include "Tokenizer.h"
#include "Indexer.h"
using namespace std;

vector<string> indexFiles(string inputFile){
	ifstream fin(inputFile);
	string currentLine;
	vector<string> fileNames;

	if(!fin)
		throw "Error opening file. Closing";

	while(getline(fin, currentLine))
		fileNames.push_back(currentLine);

	fin.close();
	return fileNames;

}

int main() {

	string inputfile = "index.txt";
	cout << "Gathering files from index file..." << endl;
	vector<string> filenames = indexFiles(inputfile);
	cout << "Creating Document objects, pushing to indexer" << endl;

	Indexer idx;

	for (vector<string>::const_iterator i = filenames.begin(); i != filenames.end(); ++i){
		Document temp(*i);
		temp >> idx;
		int s = idx.size() + 1;
		idx.setDocCount(s);
		idx.normalize();

	}
	string keywords;
	do{
		cout << "Please enter your query: " << endl;

		getline(cin, keywords);

		vector<Indexer::query_result> results = idx.query(keywords, 10);


//		for (vector<Indexer::query_result>::const_iterator i = results.begin(); i != results.end(); ++i){
//			cout << *i << endl;
//		}


	}while(keywords != "eof");
	return 0;
}
