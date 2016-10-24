/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    //hhh
    vector<string> words;
    ifstream wordsFile(word_list_fname);
	string word;
	if (wordsFile.is_open()) {
	    while (getline(wordsFile, word)) {
	        words.push_back(word);
	    }
	}
	vector<StringTriple> ret;
	for (unsigned long i = 0 ; i< words.size() ; i ++){
		word = words[i];
		if (word.size() <= 2) continue;
		string FirstWord = word.substr(1);
		string SecondWord  = word.substr(0,1)+word.substr(2,word.size());
		if (SecondWord == FirstWord) continue;
		if(d.homophones(word,FirstWord) && d.homophones(word,SecondWord)){
			ret.push_back(StringTriple(word,FirstWord,SecondWord));
		}


	}
    return ret;
    
}
