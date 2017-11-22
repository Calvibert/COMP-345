/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class splits the document into sentence tokens
 *
 */

#include "sentence_tokenizer.h"

/**
 * Constructor
 */
sentence_tokenizer::sentence_tokenizer() {
	std::vector<sentence> empty;
	sentences = empty;
}

/**
 * destructor
 */
sentence_tokenizer::~sentence_tokenizer() {
	// TODO Auto-generated destructor stub
}

/**
 * This function finds cases of titles in sentences, like Dr. Mrs. Mr. and allows it not to be split when finding the period (lets the function that calls it know)
 * @param sentence of interest, check for a title
 * @return whether or not a title was found in the sentence
 */
bool sentence_tokenizer::testForTitle(std::string sentence){
	int n = sentence.length();
	std::transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);
	std::string temp, temp2;

	if(n > 1){
		temp = sentence.substr(n-2, n);
		if(n >2)
			temp2 = sentence.substr(n-3, n);
	}
	else
		return false;
	//how else can we deal with this? it's not just these
	if(temp == "mr")
		return true;
	else if (temp == "ms")
		return true;
	else if(temp == "dr")
		return true;
	else if (temp == "mx")
		return true;
	else if (temp2 == "mrs")
		return true;
	else
		return false;
}
/**
 * This function splits an input document into tokens of sentences
 * @param doc a Document containing information on a file
 * @return a vector of sentences
 */
std::vector<sentence> & sentence_tokenizer::splitIntoSentences(Document & doc){
	std::string filecontents = doc.content();
	sentence newSentence;
		dealWithAbbreviations(filecontents);
		std::string filename = doc.name();

		std::string currentSentence = "";
		std::istringstream iss(filecontents);

		int position = 0;

		char c, tempc;

		while(iss.good()){
			iss.get(c);
			//Ignoring the whitespace at the start of a sentence after a period
			if(c == ' ' && currentSentence == ""){
				continue;
			}
			//If it's a new-line, we don't want to add it to the sentence so we skip it
			if(c == '\n')
				continue;
			//Common markers of the end of the sentence. If it's not one of those, it's a letter we want to add
			//To our current sentence
			if(c != '.' && c != '!' && c != '?' && c != '\t'){
				currentSentence += c;
			}
			//Sometimes a period isn't the end of a sentence. It could be a decimal in a number, it could be a person's title, it could be
			//part of an abbreviation, it could be the end of a sentence that's also part of a quote (which therefore
			//ends with a quotation mark and not a period). We must handle these cases
			else if(c == '.'){
				//Looking at the next character in the string will help us figure out which case it is, so we save it
				iss.get(tempc);
				//Checking if it's a person's title, like Dr. or Mrs. If it is, we want to keep this period and not skip it
				if(testForTitle(currentSentence)){
					currentSentence += c;
					currentSentence += ' ';
				}

				//Is the next character a digit? Then we're dealig with a number like 3.5 million. Again, we want to keep this period and not skip it
				else if(isdigit(tempc)){
					iss.unget(); //Go back a step. We'll store the next character on the next iteration of the loop
					currentSentence += c;
					tempc = '\0'; //reset tempc
				}
				//What if the sentence is a quote? It will have the format ''The quick brown fox.''
				//Here, the end of the sentence isn't the period but the quote. We want to keep this period
				else if(tempc == '\''){
					iss.unget();
					currentSentence += c;
					tempc = '\0';
				}
				//If we get here, it's just a regular period. This means our sentence is done and we can add it to the vector
				else{
					sentence newSentence(doc, (position - currentSentence.length()), currentSentence);
					sentences.push_back(newSentence);
					currentSentence = "";
				}
			}
			//If there's a bunch of whitespace in a row, we don't want that inside the sentence (ex: tabs are the beginning of a paragraph)
			else if(checkIfWhitespace(currentSentence)){
				currentSentence = "";
			}
			//After all this, we know we've reached the end of the sentence and can add it to the vector
			else{
				sentence newSentence(doc, (position - currentSentence.length()-1), currentSentence);
				sentences.push_back(newSentence);
				currentSentence = "";
			}
			++position;
		}
		//currently wont contain the last sentence if a period is forgotten
		return sentences;
}
/**
 * a helper function to find whitespace and make sure a line that's all whitespace isn't added as a sentence
 * @param sentence is a string to check for whitespace
 * @return whether or not the sentence contains anything that isn't whitespace
 */
bool sentence_tokenizer::checkIfWhitespace(std::string sentence){
	int n = sentence.length();
	for(int i = 0; i != n; ++i){
		if(!isspace(sentence[i]))
			return false;
	}
	return true;
}
/**
 * getter for sentences
 * @return a vector of sentences
 */
std::vector<sentence> sentence_tokenizer::getSentences() {
	return sentences;
}

