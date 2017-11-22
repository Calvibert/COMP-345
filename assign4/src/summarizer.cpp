/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * The main for the summarizer. Reads user's input for index file and question file, displays sumamrizer results
 *
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
#include "index_exception.h"


using namespace std;

/**
 * Indexes the user-entered file
 * @param inputFile filename
 * @return a vector of strings containing filenames
 */
vector<string> indexFiles(string inputFile) {
	ifstream fin(inputFile);
	string currentLine;
	vector<string> fileNames;


	if (!fin)
		throw index_exception("Error opening file. Please enter a proper file name.");

	while (getline(fin, currentLine))
		fileNames.push_back(currentLine);

	fin.close();
	return fileNames;

}

int main(){
	string filename;
	vector<string> filenames;
	bool condition = true;
	do{
		cout << "Enter the index file name: " << endl;
		cin >> filename;

		try{
			filenames = indexFiles(filename);
			condition = true;
		}
		catch(index_exception& e){
			cout << e.what() << endl;
			condition = false;
		}

	}while(!condition);

	sentence_indexer sidx;

	for (unsigned i = 0; i < filenames.size(); ++i) {
		sidx.readDocument(filenames[i]);
	}

	sidx.normalize();

	string questionfile = "";
	Document doc;
	condition = true;
	do{
		cout << "Enter the name of a question file: " << endl;
		cin >> questionfile;
		try{
			Document doc(questionfile);
			condition = true;
		}
		catch(index_exception& e){
			cout << e.what() << endl;
			condition = false;
		}
	}while(!condition);

	std::vector<sentence_indexer::query_result> results = sidx.query(doc.content());


	for (unsigned i = 0; i < results.size(); ++i) {
		if (results[i].score > 0) {
			index_item sent = results[i].element;
			cout << sent.content() << endl;
		}

	}
	return 0;
}


