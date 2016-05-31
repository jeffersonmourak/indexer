#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include "table.h"
#include "file.h"

#define LIMIT 100

using namespace std;

vector <string> split(string str, char delimiter){
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)){
		internal.push_back(tok);
	}

	return internal;

}

void mapFile(string filename){
	ifstream file(filename);

	Word table[LIMIT];

	vector<string>::iterator it;

	string line;
	vector<string> _line;
	int lNumber = 0;

	while(getline(file, line)){
		_line = split(line, ' ');

		for(it=_line.begin(); it < _line.end(); it++ ){
			addWord(*it, table, filename, lNumber);
		}

		lNumber++;

		printMap(table);

	}

}

void printMap(Word *_w){
	ofstream logFile;
	logFile.open("log.txt");
	for(int i = 0; i < LIMIT; i++){
		if(_w[i].word == "")
			continue;

		Word *w = &_w[i];
		while(w != NULL){
			Item *i = w->items;
			logFile << "Word: " << w->word;
			while(i != NULL){
				logFile << " @ " << i->file << " in Line " << i->line << endl;
				i = i->next;
			}
			w = w->next;
		}
	}
	logFile.close();
}
