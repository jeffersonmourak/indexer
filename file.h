#ifndef file_H
#define file_H

struct Item{
	std::string file;
	int line;
	Item *next;
};

struct Word{
	Item *items;
	Item *last;
};

void mapFile(std::string filename);
void printMap();

void addWord(std::string word, std::string file, int line);

#endif
