#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> openingInput(string inputFile){
	ifstream fin(inputFile);
	vector<string> fileNames;
	string currentLine;

	if (!fin)
		throw "Error opening input file. Closing";
	
	//Loop through file, read each line into the vector
	while (getline(fin, currentLine))
		fileNames.push_back(currentLine);

	fin.close();

	return fileNames; 
}

vector<string> openingFiles(string inputFile){
	ifstream fin(inputFile);
	vector<string> tokens;
	string currentWord;

	if (!fin)
		throw "Error opening input file. Closing";

	//Loop through file, read each word into the vector of tokens
	while (fin >> currentWord)
		tokens.push_back(currentWord);
	
	fin.close();

	return tokens;
}

int main(){
	//could replace with a cin asking for a file name, but for the purposes of this, we already know the file's name
	string indexFile = "index.txt";
	vector<string> fileNames;

	try{
		//this will populate the vector with every line in the file (ie every file name we'll be going to next)
		fileNames = openingInput(indexFile);
	}
	catch (const char* message){
		//if the file doesn't open for some reason, it'll display this message instead 
		cerr << message << endl;
	}

	//this is just to test and see what's in the vector. It'll print each element. TO-DO: DELETE LATER
	
	for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i)
		cout << *i << endl;
	

	cout << "DISPLAYING WHAT'S IN EACH FILE STARTS HERE" << endl << endl;

	//Testing to see if things are displaying properly when reading from the file
	string currentFile;
	vector<string> allTokens;
	vector<string> filteredTokens;

	try{
		//iterate through the vector containing each file name
		for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i){
			//file we're looking at is stored here
			currentFile = *i;
			//open the file and store every word
			allTokens = openingFiles(currentFile);
			//for clarity on the console, TO-DO: DELETE LATER
			cout << "WHAT FILE IS THIS? Name: " << currentFile << endl;
			//Display each word to see if it works. not formated
			for (vector<string>::const_iterator i = allTokens.begin(); i != allTokens.end(); ++i)
				cout << *i << endl;
			//for clarity on the console, TO-DO: DELETE LATER
			cout << "HERE IS THE END OF THE FILE" << endl << endl;
		}
	}
	catch (const char* message){
		//if the file doesn't open for some reason, it'll display this message instead 
		cerr << message << endl;
	}
	return 0;
}