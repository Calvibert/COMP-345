/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * Declaration for index_exception, an exception class used to provide explanations for errors for the program
 */
#include "index_exception.h"

/**
 * index_exception default constructor
 */
index_exception::index_exception(){
	message = "Unknown error";
}

/**
 * index_exception constructor
 * @param msg the message to be displayed detailing what went wrong
 */
index_exception::index_exception(std::string msg) {
	message = msg;
}

/**
 * destructor
 */
index_exception::~index_exception() {
	// TODO Auto-generated destructor stub
}

/**
 * getter for the message
 * @return a string containing details about what the error was
 */
const std::string index_exception::getMessage() const {
	return message;
}

/**
 * overridden what() function to provide an explanation of the exception
 * @return the string message containing details about what the error was
 */
const char* index_exception::what() const throw(){
	std::string returnString = "index exception occurred. Reason: " + getMessage();
	return returnString.c_str();
}


