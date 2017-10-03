#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct dictionary {
		string term;
		string docName;
		int freq;

		bool operator!=(const dictionary& a) {
		if (a.term != term || a.docName != docName) {
			return true;
		} else {
			return false;
		}
		}

		bool operator==(const dictionary& a) {
		if (a.term == term && a.docName == docName) {
			return true;
		} else {
			return false;
		}
	}
};

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
void increment(vector<dictionary>* tokens, dictionary currentDict, int index) {
	++currentDict.freq;
	(*tokens)[index] = currentDict;
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
void openingFiles(string inputFile, vector<string> stopWordVector,
		string::size_type *longestWord, string::size_type *longestFilteredWord,
		vector<dictionary>* allTokens, vector<dictionary>* filteredTokens){
	ifstream fin(inputFile);
	string currentWord;
	dictionary temp;


	if (!fin) {
		throw "Error opening input file. Closing";
	}

	//Loop through file, read each word into the vector of tokens
	while (fin >> currentWord) {
		// remove punctuation
		currentWord = containsPunctuation(currentWord);
		// to lower case
		transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

		if (currentWord.length() > *longestWord) {
			*longestWord = currentWord.length();
		}

		temp.term = currentWord;
		temp.docName = inputFile;

		if (int index = find((*allTokens).begin(), (*allTokens).end(), temp) != (*allTokens).end()) {
			//increment(allTokens, temp, index);
			if (isStopWord(currentWord, stopWordVector)) {
				//increment(filteredTokens, temp, index);
			}
		} else {

			temp.freq = 1;

			(*allTokens).push_back(temp);

			if (isStopWord(currentWord, stopWordVector)) {
				if (currentWord.length() > *longestFilteredWord) {
					*longestFilteredWord = currentWord.length();
				}

				(*filteredTokens).push_back(temp);
			}
		}

	}
	
	fin.close();

}

// Read the tokens from a file and return them as a vector of strings
vector<string> readFile(string file) {
	vector<string> tokens;
	ifstream fin(file);
	string currentWord;

	while (fin >> currentWord) {
		transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
		tokens.push_back(currentWord);
	}

	fin.close();

	return tokens;
}


void outputDictionary(vector< map<string, int> >,int longestWord) {

	//print all documents
	//iterate through all documents

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



	// Stop words
	string stopWordFilename = "stopwords.txt";
	vector<string> stopWordList;

	// File processing
	string currentFile;

	vector<dictionary> *allTokensDict;
	vector<dictionary> *filteredTokensDict;

	// Will get the length of the longest word for both dictionaries
	string::size_type *longestWordLength = 0;
	string::size_type *longestFilteredWordLength = 0;;

	// Read words from the stop words list
	stopWordList = readFile(stopWordFilename);

	try{
		//iterate through the vector containing each file name
		for (vector<string>::const_iterator i = fileNames.begin(); i != fileNames.end(); ++i){
			//file we're looking at is stored here
			currentFile = *i;

			// Open the file and process every word.
			// Returns all tokens and a filtered tokens dictionary.
			openingFiles(currentFile, stopWordList, longestWordLength, longestFilteredWordLength, allTokensDict, filteredTokensDict);

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
