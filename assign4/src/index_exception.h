/*
 * index_exception.h
 *
 *  Created on: Nov 21, 2017
 *      Author: Maude
 */

#ifndef INDEX_EXCEPTION_H_
#define INDEX_EXCEPTION_H_

#include <exception>
#include <string>

class index_exception: public std::exception {
public:
	index_exception();
	index_exception(std::string message);
	virtual ~index_exception();

	const std::string getMessage() const;

	virtual const char* what() const throw();
private:
	std::string message;
};

#endif /* INDEX_EXCEPTION_H_ */
