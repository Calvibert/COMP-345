#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Open the main file and return the list of filenames contained within it
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

// If a word already exists, increment its frequency by 1
void increment(map<string, int> tokens, string currentToken) {
	tokens[currentToken] = ++tokens[currentToken];
}

// If a word contains a character specified in the array, it will remove it.
string containsPunctuation(string word) {
	char skippedChars[] = {'.', ',', ':', ';', ')', '('};

	if (word.find(skippedChars)) {
		word.pop_back();
		return word;
	}
	else {
		return word;
	}
}

// Given a term-frequency vector, filter out words matching a certain list.
bool isStopWord(string word, vector<string> stopWords) {
	return find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}


// Go through a file and count the frequency of each term accordingly
vector< map<string, int> > openingFiles(string inputFile, vector<string> stopWordVector){
	ifstream fin(inputFile);
	vector< map<string, int> > dictionaries;
	map<string, int> allTokens;
	map<string, int> filteredTokens;
	string currentWord;


	if (!fin) {
		throw "Error opening input file. Closing";
	}

	//Loop through file, read each word into the vector of tokens
	while (fin >> currentWord) {
		currentWord = containsPunctuation(currentWord);

		if (filteredTokens[currentWord]) {
			increment(allTokens, currentWord);
			if (isStopWord(currentWord, stopWordVector)) {
				increment(filteredTokens, currentWord);
			}
		} else {
			allTokens[currentWord] = 1;
			if (isStopWord(currentWord, stopWordVector)) {
				filteredTokens[currentWord] = 1;
			}
		}

	}
	
	dictionaries.push_back(allTokens);
	dictionaries.push_back(filteredTokens);

	fin.close();

	return dictionaries;
}

// Read the tokens from a file and return them as a vector of strings
vector<string> readFile(string file) {
	vector<string> tokens;
	ifstream fin(file);
	string currentWord;

	while (fin >> currentWord) {
		tokens.push_back(currentWord);
	}

	fin.close();

	return tokens;
}


int main(){
	// PART 1: INPUT
	//could replace with a cin asking for a file name, but for the purposes of this, we already know the file's name
	string indexFile = "index.txt";
	vector<string> fileNames;

	try {
		//this will populate the vector with every line in the file (ie every file name we'll be going to next)
		fileNames = openingInput(indexFile);
	}
	catch (const char* message) {
		//if the file doesn't open for some reason, it'll display this message instead 
		cerr << message << endl;
	}

	//this is just to test and see what's in the vector. It'll print each element. TO-DO: DELETE LATER
	for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i) {
		cout << *i << endl;
	}
	// PART 1: END
	

	// PART 2: PROCESSING
	cout << "DISPLAYING WHAT'S IN EACH FILE STARTS HERE" << endl << endl;

	//Testing to see if things are displaying properly when reading from the file

	// Stop words
	string stopWordFilename = "stopwords.txt";
	vector<string> stopWordList;

	// File processing
	string currentFile;
	vector< map<string, int> > allTokensDict;
	vector< map<string, int> > filteredTokensDict;
	vector< map<string, int> > fileDictionary;

	// Read words from the stop words list
	stopWordList = readFile(stopWordFilename);

	try{
		//iterate through the vector containing each file name
		for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i){
			//file we're looking at is stored here
			currentFile = *i;

			// Open the file and process every word.
			// Returns all tokens and a filtered tokens dictionary.
			fileDictionary = openingFiles(currentFile, stopWordList);

			// Store in the allTokens dictionary
			allTokensDict.push_back(fileDictionary[0]);

			// Store in filtered dictionary after filtering
			filteredTokensDict.push_back(fileDictionary[1]);

			// Reset the vector
			fileDictionary.clear();

			// PART 2: END

		}
	}
	catch (const char* message){
		//if the file doesn't open for some reason, it'll display this message instead 
		cerr << message << endl;
	}

	// PART 3: OUTPUT


	// PART 3: END

	return 0;
}
