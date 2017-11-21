/*
 * summarizer.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Maude
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

#include "abstract_tokenizer.h"
#include "word_tokenizer.h"
#include "sentence_tokenizer.h"
#include "index_item.h"
#include "Document.h"
#include "sentence.h"
#include "sentence_indexer.h"


using namespace std;

vector<string> indexFiles(string inputFile) {
	ifstream fin(inputFile);
	string currentLine;
	vector<string> fileNames;

	if (!fin)
		throw "Error opening file. Closing";

	while (getline(fin, currentLine))
		fileNames.push_back(currentLine);

	fin.close();
	return fileNames;

}


int main(){

	cout << "Enter the index file name: " << endl;
	string filename;
	cin >> filename;

	vector<string> filenames = indexFiles(filename);
	sentence_indexer sidx;

	for (unsigned i = 0; i < filenames.size(); ++i) {
		sidx.readDocument(filenames[i]);
	}

	sidx.normalize();

	cout << "Enter the name of a question file: " << endl;
	string questionfile;
	cin >> questionfile;

	Document doc(questionfile);
	cout << doc.name() << endl;

	std::vector<sentence_indexer::query_result> results = sidx.query(doc.content());


	for (unsigned i = 0; i < results.size(); ++i) {
		if (results[i].score > 0) {
			index_item sent = results[i].element;
			cout << sent.content() << endl;
		}

	}

}


