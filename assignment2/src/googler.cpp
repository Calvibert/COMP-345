//============================================================================
// Name        : assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Document.h"
using namespace std;

int main() {
	cout << "we're testing Document" << endl;
	Document test("testing.txt");
	string content = test.content();
	cout << content << endl;
	return 0;
}
