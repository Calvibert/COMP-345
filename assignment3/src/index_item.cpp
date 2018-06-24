/*
 * index_item.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Maude
 */

#include "index_item.h"

// Read the filename. Sets the text in the Document to the content of the file
std::string index_item::readFile(std::string filename) {
	std::ifstream fin(filename);
	if (!fin) {
		std::cout << "Could not open file. Closing" << std::endl;
		std::exit(1);
	}
	std::string content((std::istreambuf_iterator<char>(fin)),
			std::istreambuf_iterator<char>());
	fin.close();

	return content;
}
