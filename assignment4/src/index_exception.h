/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * Declaration for index_exception, an exception class used to provide explanations for errors for the program
 */
#ifndef INDEX_EXCEPTION_H_
#define INDEX_EXCEPTION_H_

#include <exception>
#include <string>

class index_exception: public std::exception {
public:
	/**
	 * index_exception default constructor
	 */
	index_exception();
	/**
	 * index_exception constructor
	 * @param msg the message to be displayed detailing what went wrong
	 */
	index_exception(std::string message);
	/**
	 * destructor
	 */
	virtual ~index_exception();

	/**
	 * getter for the message
	 * @return a string containing details about what the error was
	 */
	const std::string getMessage() const;

	/**
	 * overridden what() function to provide an explanation of the exception
	 * @return the string message containing details about what the error was
	 */
	virtual const char* what() const throw();
private:
	std::string message;
};

#endif /* INDEX_EXCEPTION_H_ */
