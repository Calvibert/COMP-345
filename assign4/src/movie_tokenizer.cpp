/*
 * movietokenizer.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: samue
 */

#include "movie_tokenizer.h"

namespace std {

movie_tokenizer::movie_tokenizer() {
	vector<movie> empty;
	movies = empty;
}

movie_tokenizer::~movie_tokenizer() {

}

bool movie_tokenizer::testForTitle(std::string sentence) {
	int n = sentence.length();
	std::transform(sentence.begin(), sentence.end(), sentence.begin(),
			::tolower);
	std::string temp, temp2;

	if (n > 1) {
		temp = sentence.substr(n - 2, n);
		if (n > 2)
			temp2 = sentence.substr(n - 3, n);
	} else
		return false;
	//how else can we deal with this? it's not just these
	if (temp == "mr")
		return true;
	else if (temp == "ms")
		return true;
	else if (temp == "dr")
		return true;
	else if (temp == "mx")
		return true;
	else if (temp2 == "mrs")
		return true;
	else
		return false;
}

bool movie_tokenizer::checkIfWhitespace(std::string sentence) {
	int n = sentence.length();
	for (int i = 0; i != n; ++i) {
		if (!isspace(sentence[i]))
			return false;
	}
	return true;
}

std::vector<movie>& movie_tokenizer::splitIntoMovies(Document & doc) {
	std::string filecontents = doc.content();
	vector<std::string> parameters;
	dealWithAbbreviations(filecontents);
	std::string filename = doc.name();

	int count = 0;

	std::string currentSentence = "";
	std::istringstream iss(filecontents);

	int position = 0;
	char c, tempc;

	while (iss.good()) {
		iss.get(c);
		//Ignoring the whitespace at the start of a sentence after a period
		if (c == ' ' && currentSentence == "") {
			continue;
		}
		//If it's a new-line, this indicates the end of a "sentence"
		if (c == '\n') {
			movie newMovie(parameters[1], parameters[2], parameters[0]);
			movies.push_back(newMovie);
			parameters.clear();
			currentSentence = "";
			count = 0;
			continue;
		}
		//Common markers of the end of the sentence. If it's not one of those, it's a letter we want to add
		//To our current sentence
		if (c != '.' && c != '!' && c != '?' && c != '\t') {
			currentSentence += c;
		}
		//Sometimes a period isn't the end of a sentence. It could be a decimal in a number, it could be a person's title, it could be
		//part of an abbreviation, it could be the end of a sentence that's also part of a quote (which therefore
		//ends with a quotation mark and not a period). We must handle these cases
		else if (c == '.') {
			//Looking at the next character in the string will help us figure out which case it is, so we save it
			iss.get(tempc);
			//Checking if it's a person's title, like Dr. or Mrs. If it is, we want to keep this period and not skip it
			if (testForTitle(currentSentence)) {
				currentSentence += c;
				currentSentence += ' ';
			}

			//Is the next character a digit? Then we're dealig with a number like 3.5 million. Again, we want to keep this period and not skip it
			else if (isdigit(tempc)) {
				iss.unget(); //Go back a step. We'll store the next character on the next iteration of the loop
				currentSentence += c;
				tempc = '\0'; //reset tempc
			}
			//What if the sentence is a quote? It will have the format ''The quick brown fox.''
			//Here, the end of the sentence isn't the period but the quote. We want to keep this period
			else if (tempc == '\'') {
				iss.unget();
				currentSentence += c;
				tempc = '\0';
			}
			//If we get here, it's just a regular period. This means our sentence is done and we can add it to the vector
			else {
				if (count == 0 || count == 2 || count == 3) {
					parameters.push_back(currentSentence);
				}
				count++;
				currentSentence = "";

			}
		}
		//If there's a bunch of whitespace in a row, we don't want that inside the sentence (ex: tabs are the beginning of a paragraph)
		else if (checkIfWhitespace(currentSentence)) {
			currentSentence = "";
		}
		//After all this, we know we've reached the end of the sentence and can add it to the vector
		else {
			if (count == 0 || count == 2 || count == 3) {
				parameters.push_back(currentSentence);
			}
			count++;
			currentSentence = "";
		}
		++position;
	}

	return movies;
}

std::vector<movie>& movie_tokenizer::addPlot(Document & doc) {
	std::string filecontents = doc.content();
	dealWithAbbreviations(filecontents);
	std::string filename = doc.name();

	std::string id;
	std::string content;

	std::string currentSentence = "";
	std::istringstream iss(filecontents);

	int position = 0;
	char c, tempc;

	int index = 0;

	while (iss.good()) {
		iss.get(c);

//    std::cout << currentSentence << std::endl;

		//Ignoring the whitespace at the start of a sentence after a period
		if (c == ' ' && currentSentence == "") {
			continue;
		}

		//If it's a new-line, this indicates the end of a "sentence"
		if (c == '\n') {
			movie tempMovie = movies[index];
			std::string tempContent = tempMovie.content() + currentSentence + ". ";
			tempMovie.setContent(tempContent);
			movies[index] = tempMovie;
			currentSentence = "";
			continue;
		}

		if (c != '.' && c != '!' && c != '?' && c != '\t') {
			currentSentence += c;
		}

		else if (c == '.') {
			iss.get(tempc);
			if (testForTitle(currentSentence)) {
				currentSentence += c;
				currentSentence += ' ';
			} else if (isdigit(tempc)) {
				iss.unget(); //Go back a step. We'll store the next character on the next iteration of the loop
				currentSentence += c;
				tempc = '\0'; //reset tempc
			} else if (tempc == '\'') {
				iss.unget();
				currentSentence += c;
				tempc = '\0';
			}
			//If we get here, it's just a regular period. This means our sentence is done and we can add it to the vector
			else {
				// content
				movie tempMovie = movies[index];
				std::string tempContent = tempMovie.content() + currentSentence + ". ";
				tempMovie.setContent(tempContent);
				movies[index] = tempMovie;
				std::cout << tempMovie.content() << std::endl;
				currentSentence = "";
				continue;
			}
		}

		else if (checkIfWhitespace(currentSentence)) {
			currentSentence = "";
		}
		//After all this, we know we've reached the end of the sentence and can add it to the vector
		else {
			if (is_digits(currentSentence)) {
				id = currentSentence;
				index = getMovieFromId(id);
				currentSentence = "";
				continue;
			}
		}
		++position;
	}

	return movies;
}

int movie_tokenizer::getMovieFromId(std::string id) {
	for (unsigned i = 0; i < movies.size(); ++i) {
		if (id == movies[i].getId()) {
			return i;
		}
	}
	return -1;
}

bool movie_tokenizer::is_digits(const std::string &str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

std::vector<movie> movie_tokenizer::getMovies() {
	return movies;
}

ostream& operator<<(ostream& os, const movie_tokenizer& mt) {
	std::vector<movie> elements = mt.movies;
	for (unsigned i = 0; i < elements.size(); ++i) {
		os << "ID: " << elements[i].getId() << endl << "Title: "
				<< elements[i].name() << endl << "Plot summary: "
				<< elements[i].content() << std::endl;
	}

	return os;
}

} /* namespace std */
