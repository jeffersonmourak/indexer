#include <cstdlib>
#include <iostream>
#include <map>
#include <algorithm>

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "file.h"
#include "search.h"
#include "termcolor.hpp"

using namespace std;

Search::Search(map <string, Word> w, vector <File> f){
    this->words = w;
    this->files = f;
}

vector <string> Search::split(string str, char delimiter){
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter)){
		internal.push_back(tok);
	}

	return internal;

}

void Search::find(string key){
    transform(key.begin(), key.end(),key.begin(), ::toupper);
    bool notExits = this->words.find(key) == this->words.end();
    if(notExits){
        cout << "Palavra não está contida na base de busca" << endl;
    }
    else{
        vector<File>::iterator it;

    	for(it=files.begin(); it < files.end(); it++ ){
    	    
    	    Item *i = words[key].items;
    	    vector<int> lines;
    	    int count = 0;
        
            while(i != NULL){
    		    if(i->file == it->filename){
    		        count++;
    		        lines.push_back(i->line - 1);
    		    }
    			i = i->next;
    		}
            
            cout << "Foram encontradas " << count << " linhas no arquivo \"" + it->filename << "\": " << endl;
            
            vector<int>::iterator itL;
            
            for(itL=lines.begin(); itL < lines.end(); itL++ ){
                cout << termcolor::red << termcolor::bold << "- linha " << *itL + 1 << ": " << termcolor::reset << "\"";
                this->printLineHighLight(this->getLine(it->filename, *itL), key);
                cout << "\"" << endl;
            }
    	}
    }
}

string Search::getLine(string filename, int line){
    
    ifstream file(filename);
    int l = 0;
    
    string _line;
    
    while(getline(file, _line) && l < line){
    }
    
    file.close();
    return _line;
}

void Search::printLineHighLight(string line, string key){
    vector<string>::iterator it;
        
    vector<string> _line = this->split(line, ' ');
    
    for (it = _line.begin(); it < _line.end(); it++) {
        string k = *it;
        transform(k.begin(), k.end(),k.begin(), ::toupper);
        if(k == key){
            cout << termcolor::green << termcolor::bold << *it << termcolor::reset << " ";
        }
        else{
            cout << *it << " ";
        }
    }
    cout << endl;
    
}