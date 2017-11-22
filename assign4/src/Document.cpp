/**
 * @file
 * @author Maude Braunstein, Samuel Dufresne
 *
 * This class represents a given document
 *
 */

#include "Document.h"

Document::Document() {
	setName("");
	setContent("");
}

Document::Document(std::string f){
	setName(f);
	setContent(Document::readFile(f));
}

Document::~Document() {
}

std::string Document::readFile(std::string filename) {
  std::ifstream fin(filename.c_str());
  if (!fin) {
    std::cout << "Could not open file. Closing" << std::endl;
    std::exit(1);
  }
  std::string content((std::istreambuf_iterator<char>(fin)),
      std::istreambuf_iterator<char>());
  fin.close();

  return content;
}

std::ostream& operator<<(std::ostream& os, const Document& d){
	os << d.content() << std::endl;
	return os;
}

