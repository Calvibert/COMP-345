/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * The abstract base class containing information and functions for both word_tokenizer and sentence_tokenizer
 *
 */
#include "abstract_tokenizer.h"

/**
 * a function to help the porogram parse through words containing punctuation
 * @param sentence a string with problematic words and abbreviations
 */
void abstract_tokenizer::dealWithAbbreviations(std::string& sentence){
	//using temp because we dont want the output to be all lowercase, but making it all lowercase makes comparisons easier
	std::string temp = sentence;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//We make the replacement in the old string, so the positions change slightly if it encounters
	//more than one instance of "U.N.". We need to shift it by 2 every time it finds one (or some other value, depends on length of
	//what we're replacing)
	int counter = 0;

	std::string abbreviations[] = {"u.n.", "u.k.", "u.s.", "a.m.", "p.m.", "i.e.", "etc.", "e.g.", "..."};
	std::string change[] = {"UN", "UK", "US", "am", "pm", "ie", "etc", "eg", "…"};

	//Find all U.N.s
	size_t pos = temp.find("u.n.", 0);
	while (pos != std::string::npos){ //find all instances of "U.N', replace with UN without periods
		sentence.replace((pos + counter), 4, "UN");
		counter -= 2;
		pos = temp.find("u.n.", pos+1);
	}


	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all U.S.s
	pos = temp.find("u.s.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "US");
		counter -= 2;
		pos = temp.find("u.s.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all U.K.s
	pos = temp.find("u.k.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "UK");
		counter -= 2;
		pos = temp.find("u.k.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all a.ms.
	pos = temp.find("a.m.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "am");
		counter -= 2;
		pos = temp.find("a.m.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all p.m. s
	pos = temp.find("p.m.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "pm");
		counter -= 2;
		pos = temp.find("p.m.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all e.g.s
	pos = temp.find("e.g.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "eg");
		counter -= 2;
		pos = temp.find("e.g.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all i.e.s
	pos = temp.find("i.e.", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 4, "ie");
		counter -= 2;
		pos = temp.find("i.e.", pos+1);
	}
	temp = sentence;
	counter = 0;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	//Find all ellipses
	pos = temp.find("...", 0);
	while (pos != std::string::npos){
		sentence.replace((pos + counter), 3, "…");
		counter -= 2;
		pos = temp.find("...", pos+1);
	}
}
