/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * The abstract base class for document and sentence
 *
 */

#include "index_item.h"

/**
 * setter for the content of a document or sentence
 * @param c the content to be set
 */
void index_item::setContent(const std::string& c) {
	itemContent = c;
}
/**
 * setter for file name
 * @param n name to be set
 */
void index_item::setName(const std::string& n) {
	filename = n;
}
/**
 * setter for length
 * @param s new size
 */
void index_item::setSize(int s) {
	length = s;
}

/**
 * getter for length
 * @return length of object
 */
int index_item::size() const {
	return length;
}
/**
 * getter for filename
 * @return filename
 */
std::string index_item::name() const {
	return filename;
}
/**
 * getter for content
 * @return item content
 */
std::string index_item::content() const {
	return itemContent;
}
