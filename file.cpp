#include <cstdlib>
#include <iostream>
#include <map>
#include <algorithm>

#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>

#include "file.h"

using namespace std;

Indexer::Indexer(){
	this->loadMeta(); //carrega as palavras indexadas do arquivo log.txt
	this->loadFiles();
}

map <string, Word> Indexer::getWords(){
	return this->words;
}
vector <File> Indexer::getFiles(){
	return this->files;
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
		if(_line.size() == 2){
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
		
	}
	file.close();
}

void Indexer::addFile(string filename, int wordsCount){
	File *n = new File();
	n->filename = filename;
	n->words = wordsCount;
	
	files.push_back(*n);
}

int Indexer::mapFile(string filename){ //função que mapeia o arquivo e salva em WORDS 
	ifstream file(filename);
	
	int wordsCount = 0;
	vector<string>::iterator it;
	
	string line;
	vector<string> _line;
	int lNumber = 0;

	while(getline(file, line)){
		_line = split(line, ' ');

		for(it=_line.begin(); it < _line.end(); it++ ){
			addWord(*it, filename, lNumber);
			wordsCount++;
		}

		lNumber++;

	}
	file.close();

	
	return wordsCount;
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
	
	vector<File>::iterator _it;

}

//Listar por ordem decrescente
void Indexer::listDec(){
	vector<File> desc = files;
	vector<File>::iterator itX, itY;
	File temp;
	
	for(itX=desc.begin(); itX < desc.end(); itX++){
		int x = distance(desc.begin(), itX);
		for(itY=itX; itY < desc.end(); itY++){
			int y = distance(desc.begin(), itY);
			if(desc[x].words < desc[y].words){
				temp = desc[y];
				desc[y] = desc[x];
				desc[x] = temp;
			}
		}
	}
	cout << "Arquivos contidos na base de busca: " << endl;
	for(itX = desc.begin(); itX < desc.end(); itX++){
		cout << itX->filename << endl;
	}
}

void Indexer::listAlpha(){

	char names[files.size()][100];
	char exchange[100];
	int i, x, y ,z;
	for(i = 0; i < files.size(); i++){
		strcpy(names[i], files[i].filename.c_str());
	}
	
	for( x=0;x<=files.size()-2;x++)
	{
	    for( y=0;y<=files.size()-2;y++)
	    {
	        for( z=0;z<=99;z++)
	        {
	            if(int(names[y][z])>int(names[y+1][z]))
	            {   
	                strcpy(exchange,names[y]);
	                strcpy(names[y],names[y+1]);
	                strcpy(names[y+1],exchange);
	                break;
	            }
	            else if(int(names[y][z])<int(names[y+1][z]))
            		break;  
	        }   
	    }
	} 
	
	cout << "Arquivos contidos na base de busca: " << endl;
	for(x=0;x<=files.size()-1;x++)
    	cout << names[x] << endl;

}


//Listar por ordem de inserção
void Indexer::listFiles(){
	vector <File>::iterator it;
	
	cout << "Arquivos contidos da base de busca: " << endl;
	for(it = files.begin(); it < files.end(); it++){
		cout << it->filename << endl;
	}
}

//Insere arquivo na base de busca
void Indexer::indexFiles(vector<string> files){
	vector<string>::iterator it;
	
	for(it = files.begin(); it < files.end(); it++){
		if(isIndexed(*it) == 0){
			int wordsCount = this->mapFile(*it);
			this->addFile(*it, wordsCount);
			this->printMap();
			this->printFiles();
			cout << "Arquivo \" " << *it <<"\" inserido na base de buscas." << endl;
		}
		else{
			cout << "Arquivo \" " << *it <<"\" já está inserido na base de buscas." << endl;
		}
	}
	
}

int Indexer::isIndexed(string filename){
	return 0;
	//MUDAR ESSA PORRA
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
				
				logFile << i->file << "," << i-> line << ";";
			}
			i = i->next;
		}
		logFile << endl;
	}
	logFile.close();


	this->words.clear();
	this->loadMeta();
}

void Indexer::unIndexFiles(vector<string> filename){
	vector<string>::iterator it;
	
	for(it = filename.begin(); it < filename.end(); it++){
		if(isIndexed(*it) == 1){
			this->unMapFile(*it);
			cout << "Arquivo \" " << *it <<"\" removido da base de buscas." << endl;
		}
		else{
			cout << "Arquivo \" " << *it <<"\" não existe na base de buscas." << endl;
		}
	}
	
}

void Indexer::printFiles(){
	
	ofstream logFile;
	logFile.open("files.txt");
	
	vector<File>::iterator it;
	
	for(it = files.begin(); it < files.end(); it++){
		logFile << it->filename << ":" << it->words << endl;
	}
	
	logFile.close();
}

void Indexer::loadFiles(){
	ifstream file("files.txt");
	vector<string> _line;
	string line;

	vector<string>::iterator it;

	while(getline(file, line)){
		_line = split(line, ':');
		File *n = new File();
		n->filename = _line[0];
		n->words = stoi(_line[1]);
		files.push_back(*n);
	}
}

// void Indexer::listAlpha(){
	
// }

// void Indexer::listDec(){
	
// }
