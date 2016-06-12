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

Indexer::Indexer(){
	this->loadMeta(); //carrega as palavras indexadas do arquivo log.txt
}

map <string, Word> Indexer::getWords(){
	return this->words;
}

vector <string> Indexer::split(string str, char delimiter){ //função que separa uma frase em palavras separadas, tipo "olá mundo" = {"olá", "mundo"}
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)){
		internal.push_back(tok);
	}

	return internal;

}

void Indexer::loadMeta(){
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
	ifstream _file("files.txt");
	
	while(getline(_file, line)){
		files.push_back(line);
	}
	
	_file.close();
}

void Indexer::addFile(string filename){
	files.push_back(filename);
}

map <string, Word> Indexer::mapFile(string filename){ //função que mapeia o arquivo e salva em WORDS 
	ifstream file(filename);

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

void Indexer::addWord(std::string word, std::string file, int line){ //Função para adiciona uma palavra no dicionário words
	
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

void Indexer::printMap(){ //função para salvar as palavras indexadas
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
		
	logFile.open("files.txt");
	for(it=files.begin(); it < files.end(); it++ ){
		string key = *it;
		logFile << key << endl;
	}
	logFile.close();
}

void Indexer::indexFiles(vector<string> files){
	vector<string>::iterator it;
	
	for(it = files.begin(); it < files.end(); it++){
		if(isIndexed(*it) == 0){
			this->addFile(*it);
			this->mapFile(*it);
			cout << "Arquivo \" " << *it <<"\" inserido na base de buscas." << endl;
		}
		else{
			cout << "Arquivo \" " << *it <<"\" já está inserido na base de buscas." << endl;
		}
	}
	
}

int Indexer::isIndexed(string filename){
		vector<string>::iterator it;
	
	for(it = files.begin(); it < files.end(); it++){
		if(*it == filename)
			return 1;
	}
	return 0;
}

void Indexer::unMapFile(string filename){
	ofstream logFile;
	logFile.open("log.txt");
	

	vector<string>::iterator it;

	for(it=keys.begin(); it < keys.end(); it++ ){
		string key = *it;
		Item *i = words[key].items;
		logFile << *it << ":";
		while(i != NULL){
			if(i->file != filename){
				delete i;
				logFile << i->file << "," << i-> line << ";";
			}
			i = i->next;
		}
		logFile << endl;
	}
	logFile.close();
		
	logFile.open("files.txt");
	for(it=files.begin(); it < files.end(); it++ ){
		string key = *it;
		if(key != filename){
			logFile << key << endl;
		}
	}
	logFile.close();
	this->words.clear();
	this->loadMeta();
}

void Indexer::unIndexFiles(vector<string> files){
	vector<string>::iterator it;
	
	for(it = files.begin(); it < files.end(); it++){
		if(isIndexed(*it) == 1){
			this->unMapFile(*it);
			cout << "Arquivo \" " << *it <<"\" removido da base de buscas." << endl;
		}
		else{
			cout << "Arquivo \" " << *it <<"\" não existe na base de buscas." << endl;
		}
	}
	
}
