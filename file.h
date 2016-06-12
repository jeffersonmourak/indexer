#ifndef file_H
#define file_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

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


class Indexer{
	private:
		//variaveis
		map <string, Word> words;
		vector <string> keys;
		vector <string> files;
		
		//funções
		void addWord(std::string word, std::string file, int line);
		vector <string> split(string str, char delimiter);
		void addFile(string filename);
		void unMapFile(string filename);
		map <string, Word> mapFile(std::string filename);
		
		
	public:
		Indexer();
		void printMap();
		void loadMeta();
		void indexFiles(vector<string> files);
		void unIndexFiles(vector<string> files);
		int isIndexed(string filename);
		map <string, Word> getWords();
		
};



#endif
