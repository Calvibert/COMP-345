/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * The abstract base class for document and sentence
 *
 */

#ifndef INDEX_ITEM_H_
#define INDEX_ITEM_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class index_item {
public:
	index_item() : filename(""), itemContent(""), length(0) {}
	index_item(std::string filename): filename(filename), itemContent(""), length(0) {}
	index_item(std::string filename, std::string content, int length): filename(filename), itemContent(content), length(length) {}
	virtual ~index_item() {}

	void setContent(const std::string& content);
	void setName(const std::string& name);
	void setSize(int size);

	int size() const;
	std::string name() const;
	std::string content() const;

private:
	std::string filename;
	std::string itemContent;
	int length;
};

#endif /* INDEX_ITEM_H_ */
