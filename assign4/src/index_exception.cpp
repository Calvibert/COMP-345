/*
 * index_exception.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: Maude
 */

#include "index_exception.h"

index_exception::index_exception(){
	message = "Unknown error";
}

index_exception::index_exception(std::string msg) {
	message = msg;
}

index_exception::~index_exception() {
	// TODO Auto-generated destructor stub
}

const std::string index_exception::getMessage() const {
	return message;
}

const char* index_exception::what() const throw(){
	std::string returnString = "index exception occurred. Reason: " + getMessage();
	return returnString.c_str();
}


