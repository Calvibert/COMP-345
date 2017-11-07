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


using namespace std;

int main(){
	//bunch of tests

	//Document d("a3data\\a3data\\q3docs\\APW19980916.1169");
	//Document d("a3data\\a3data\\q3docs\\APW19980707.0436");
	//Document d("a3data\\a3data\\q3docs\\APW19980917.0928"); //also contains ...
	//Document d("a3data\\a3data\\q3docs\\APW19980921.0571");

	//Document d("a3data\\a3data\\q3docs\\APW19981001.1247"); //contains ...
	//Document d("a3data\\a3data\\q3docs\\APW19990301.0233");
	//Document d("a3data\\a3data\\q3docs\\APW20000906.0150");

	//Document d("a3data\\a3data\\q3docs\\APW20000906.0166");
	//Document d("a3data\\a3data\\q3docs\\NYT19990904.0099");
	//Document d("a3data\\a3data\\q3docs\\XIE19990503.0043");
	//Document d("testingdocument.txt");
	sentence s ("testingdocument.txt");


	cout << "Hello" << endl;

	word_tokenizer wt(s.getContent());
	cout << "this is word_tokenizer:" << endl;
	cout << wt << endl;

	sentence_tokenizer st(s.getContent());
	cout << "this is sentence_tokenizer:" << endl;
	cout << st << endl;

}

