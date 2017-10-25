/*
 * stopword.h
 *
 *  Created on: Oct 11, 2017
 *      Author: samue
 */

#ifndef STOPWORD_H_
#define STOPWORD_H_

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

class Stopword {
public:

	Stopword();
	virtual ~Stopword();
	std::vector<std::string> fillList(std::string inputFile);
	std::string containsPunctuation(std::string word);
	bool operator()(std::string token);
	void setStopwordList(std::vector<std::string> sl);
	std::vector<std::string> getStopwordList();

private:
	std::vector<std::string> stopwordList;
};

#endif /* STOPWORD_H_ */
