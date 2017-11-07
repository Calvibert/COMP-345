/*
 * sentence_tokenizer.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: Maude
 */

#include "sentence_tokenizer.h"

sentence_tokenizer::sentence_tokenizer(std::string text) {
	// TODO Auto-generated constructor stub
	std::vector<std::string> sentences = splitIntoSentences(text);
}

sentence_tokenizer::~sentence_tokenizer() {
	// TODO Auto-generated destructor stub
}

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

std::vector<std::string>& sentence_tokenizer::splitIntoSentences(std::string filecontents){
	dealWithAbbreviations(filecontents); //common abbreviations like UN UK IE, etc.

	std::istringstream iss(filecontents);
	std::string currentSentence = "";

	char c, tempc;

	while(iss.good()){
		iss.get(c);
		if(c == ' ' && currentSentence == ""){
			continue;
		}
		if(c == '\n')
			continue;
		//the word is either u.s. u.n, u.k, so we wanna add the periods
		if(c != '.' && c != '!' && c != '?' && c != '\t'){
			currentSentence += c;
		}
		else if (c == ','){
			iss.get(tempc);
			if(isdigit(tempc)){ //What if it's soemthing like "20,000"?
				iss.unget();
				currentSentence += c;
				tempc = '\0';
			}
		}
		else if(c == '.'){
			iss.get(tempc);
			if(testForTitle(currentSentence)){
				currentSentence += c;
				currentSentence += ' ';
			}
			else if(checkIfWhitespace(currentSentence)){
				currentSentence = "";
			}
			else if(isdigit(tempc)){ //What if it's soemthing like "3.5 million"?
				iss.unget();
				currentSentence += c;
				tempc = '\0';
			}
			else if(tempc == '\''){
				iss.unget();
				currentSentence += c;
				//currentSentence += '\''; //it's a quote, this sentence. So we'll add the '' needed at the end
				tempc = '\0';
			}
			else{
				sentences.push_back(currentSentence);
				currentSentence = "";
			}
		}
		else if(checkIfWhitespace(currentSentence)){
			currentSentence = "";
		}
		else{
			sentences.push_back(currentSentence);
			currentSentence = "";
		}
	}
	//currently wont contain the last sentence if a period is forgotten
	return sentences;
}

bool sentence_tokenizer::checkIfWhitespace(std::string sentence){
	int n = sentence.length();
	for(int i = 0; i != n; ++i){
		if(!isspace(sentence[i]))
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const sentence_tokenizer& st){
	for(std::vector<std::string>::const_iterator it = st.sentences.begin(); it != st.sentences.end(); ++it){
		os << *it << std::endl;
	}
	return os;
}
