#ifndef table_H
#define table_H

#define TABLESIZE 100

struct Item{
	std::string file;
	int line;
	Item *next;
};

struct Word{
	std::string word;
	Item *items;
	Item *last;
	Word *next;
};


int keyGen(std::string key);
int _hash(int key);
void addWord(std::string word, Word *w, std::string file, int line);
#endif
