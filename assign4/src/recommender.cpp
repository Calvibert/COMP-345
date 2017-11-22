/*
 * recommender.cpp
 *
 *  Created on: Nov 21, 2017
 *      Author: samue
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>

#include "abstract_tokenizer.h"
#include "word_tokenizer.h"
#include "sentence_tokenizer.h"
#include "index_item.h"
#include "Document.h"
#include "sentence.h"
#include "sentence_indexer.h"
#include "movie_indexer.h"

int main() {

	// Read plot_summaries
	std::movie_indexer mind;
//  Document d("movie.metadata.tsv");
//  Document e("plot_summaries.txt");
//	mind.readDocument("rec_metadata.txt", "rec_plot_sample.txt");
	mind.readDocument("rec_metadata.txt", "rec_plot_sample.txt");

	mind.normalize();
	std::string moviename;
	std::cout << "What movie do you like: " << std::endl;
	getline(std::cin, moviename);
//Taxi Blues

	mind.recommend(moviename);
	std::cout << "Here are some recommendations similar to your movie" << std::endl;

	return 0;
}

