#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

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
	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
	return word;
}

// Given a term-frequency vector, filter out words matching a certain list.
bool isStopWord(string word, vector<string> stopWords) {
	return find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}

// Helper function to sort the dictionary terms
bool sortTerms(dictionary a, dictionary b) {
	if (a.term.compare(b.term) < 0) {
		// a comes before b
		return true;
	} else {
		if (a.term.compare(b.term) == 0) {
			if (a.docName.compare(b.docName) < 0) {
				return true;
			} else {
				return false;
			}
		}
		// a comes after b or they are equal
		return false;
	}
}

// Uses the sort function with a helper sortTerms
vector<dictionary> sortDict(vector<dictionary> dict) {
	sort(dict.begin(), dict.end(), sortTerms);
	return dict;
}

// Go through a file and count the frequency of each term accordingly
void openingFiles(string inputFile, vector<string> stopWordVector,
	string::size_type & longestWord, string::size_type & longestFilteredWord,
	vector<dictionary> & allTokens, vector<dictionary> & filteredTokens) {

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

		if (currentWord.length() > longestWord) {
			longestWord = currentWord.length();
		}

		temp.term = currentWord;
		temp.docName = inputFile;
		if (int index = find((allTokens).begin(), (allTokens).end(), temp) != (allTokens).end()) {
			//increment(allTokens, temp, index);
			if (isStopWord(currentWord, stopWordVector)) {
				//increment(filteredTokens, temp, index);
			}
		}
		else {
			temp.freq = 1;

			(allTokens).push_back(temp);

			if (!isStopWord(currentWord, stopWordVector)) {
				if (currentWord.length() > longestFilteredWord) {
					longestFilteredWord = currentWord.length();
				}

				(filteredTokens).push_back(temp);
			}
		}
		//Sort the two dictionaries
		allTokens = sortDict(allTokens);
		filteredTokens = sortDict(filteredTokens);

		//Go through filtered words and find the longest
		for (vector<dictionary>::const_iterator i = filteredTokens.begin(); i != filteredTokens.end(); ++i) {
			if (i->term.length() > longestFilteredWord) {
				longestFilteredWord = currentWord.length();
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


void output(vector<dictionary> dict, vector<string> fileNames, int longestWord) {
	string previousWord = "";
	if (longestWord < 8) {
		longestWord = 8;
	}
	// Print first line:
	cout << "-------------------------------------------------------------------------------------------" << endl;

	cout << "| Dictionary ";
	// Print all file names after Dictionary
	for (unsigned i = 0; i < fileNames.size(); i++) {
		cout << setw(longestWord) << "| " << fileNames[i].c_str();
	}

	for (unsigned j = 0; j < dict.size(); j++) {
		// If new term, print it
		if (previousWord != dict[j].term) {
			cout << endl;
			cout << "| " << dict[j].term.c_str();
		}

		int freqPos = find(fileNames.begin(), fileNames.end(), dict[j].term) - fileNames.begin();

		for(int y=0; y < freqPos; y++) {
			cout << "| ";
			if (freqPos == y) {
				cout << setw(fileNames[y].length()) << dict[j].freq;
			} else {
				cout << setw(fileNames[y].length());
			}
		}

		previousWord = dict[j].term;
	}

	cout << "-------------------------------------------------------------------------------------------" << endl;

}

int main(){
	// PART 1: INPUT
	//could replace with a cin asking for a file name, but for the purposes of this, we already know the file's name
	string indexFile = "index.txt";
	vector<string> fileNames;

	try {
		//this will populate the vector with every line in the file (ie every file name we'll be going to next)
		fileNames = openingInput(indexFile);

		// Sort fileNames in alphabetical order
		sort(fileNames.begin(), fileNames.end());
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

	//vector<dictionary> init = std::vector::vector();
	vector<dictionary> allTokensDict;
	vector<dictionary> filteredTokensDict;

	// Will get the length of the longest word for both dictionaries
	string::size_type longestWordLength = 0;
	string::size_type longestFilteredWordLength = 0;

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

	allTokensDict 		= sortDict(allTokensDict);
	filteredTokensDict 	= sortDict(filteredTokensDict);


	// PART 3: OUTPUT
	output(allTokensDict, fileNames, longestWordLength);
	output(filteredTokensDict, fileNames, longestFilteredWordLength);
	// PART 3: END

	return 0;
}
