#include <cstdlib>
#include <iostream>
#include <map>
#include <algorithm>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "file.h"

using namespace std;

map <string, Word> words;
vector <string> keys;

vector <string> split(string str, char delimiter){
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)){
		internal.push_back(tok);
	}

	return internal;

}

void loadMeta(){
	ifstream file("log.txt");
	vector<string> _line;
	string line;

	vector<string>::iterator it;

	while(getline(file, line)){
		_line = split(line, ':');
		string word = _line[0];
		vector<string> wordData;
		wordData = split(_line[1], ';');
		for(it=wordData.begin(); it < wordData.end(); it++ ){
			vector<string> fileData;
			fileData = split(*it, ',');
			string filename = fileData[0];
			int line = stoi(fileData[1]) - 1;
			addWord(word, filename, line);
		}
	}
	file.close();
}

map <string, Word> mapFile(string filename){
	ifstream file(filename);

	loadMeta();

	vector<string>::iterator it;

	string line;
	vector<string> _line;
	int lNumber = 0;

	while(getline(file, line)){
		_line = split(line, ' ');

		for(it=_line.begin(); it < _line.end(); it++ ){
			addWord(*it, filename, lNumber);
		}

		lNumber++;

	}
	file.close();

	printMap();

	return words;

}

void addWord(std::string word, std::string file, int line){
	
	transform(word.begin(), word.end(),word.begin(), ::toupper);

	bool notExits = words.find(word) == words.end();

	if(notExits){
		keys.push_back(word);
		Item *i = new Item();
		i->file = file;
		i->line = (line + 1);
		i->next = NULL;
		words[word].items = i;
		words[word].last = i;
	}
	else{
		Item *i = new Item();
		i->file = file;
		i->line = (line + 1);
		i->next = NULL;
		words[word].last->next = i;
		words[word].last = i;
	}

}

void printMap(){
	ofstream logFile;
	logFile.open("log.txt");
	

	vector<string>::iterator it;

	for(it=keys.begin(); it < keys.end(); it++ ){
		string key = *it;
		Item *i = words[key].items;
		logFile << *it << ":";
		while(i != NULL){
			logFile << i->file << "," << i-> line << ";";
			i = i->next;
		}
		logFile << endl;
	}
	logFile.close();
}
