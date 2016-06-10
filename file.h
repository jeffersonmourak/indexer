#ifndef file_H
#define file_H

#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

struct Item{
	std::string file;
	int line;
	Item *next;
};

struct Word{
	Item *items;
	Item *last;
};

map <string, Word> mapFile(std::string filename);
void printMap();
void addWord(std::string word, std::string file, int line);
void loadMeta();
#endif
