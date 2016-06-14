#ifndef file_H
#define file_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Item{
	string file;
	int line;
	Item *next;
};

struct Word{
	Item *items;
	Item *last;
};

struct File{
	string filename;
	int words;
};

class Indexer{
	private:
		//variaveis
		map <string, Word> words;
		vector <string> keys;
		vector <File> files;
		
		//funções
		void addWord(std::string word, std::string file, int line);
		vector <string> split(string str, char delimiter);
		void addFile(string filename, int wordsCount);
		void unMapFile(string filename);
		int mapFile(std::string filename);
		void printFiles();
		void loadFiles();
		
	public:
		Indexer();
		void printMap();
		void loadMeta();
		void indexFiles(vector<string> files);
		void unIndexFiles(vector<string> files);
		int isIndexed(string filename);
		map <string, Word> getWords();
		vector <File> getFiles();
		void listFiles();
		void listDec();
		void listAlpha();
		
};



#endif
