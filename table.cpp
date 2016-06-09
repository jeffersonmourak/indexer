#include <iostream>
#include <algorithm>

#include "table.h"



using namespace std;

int keyGen(string key){
	int i = 0;
	char a = key[i];
	int k = 0;

	for(i=0; a != '\0'; i++){
		a = key[i];
		k+= (int)a;
	}

	return k;
}
int _hash(int key){
	return key % 100;
}


void addWord(std::string word, Word *w, std::string file, int line){
	
	transform(word.begin(), word.end(),word.begin(), ::toupper);
	
	int key = keyGen(word);
	int index = _hash(key);
	line = line + 1;
	if(w[index].word == ""){
		w[index].word = word;
		w[index].next = NULL;
		w[index].items = new Item();
		w[index].items->file = file;
		w[index].items->line = line;
		w[index].items->next = NULL;
		w[index].last = w[index].items;

		return;
	}
	else{
		if(w[index].word.compare(word) == 0){
			Item *i = new Item();
			i->file = file;
			i->line = line;
			i->next = NULL;
			w[index].last->next = i;
			w[index].last = i;
		}
		else{
			Word *_w = &w[index];
			while(_w->next != NULL){
				if(_w->word.compare(word) == 0){
					cout << "FIND " << word << endl;
					Item *i = new Item();
					i->file = file;
					i->line = line;
					i->next = NULL;
					_w->last->next = i;
					_w->last = i;
					return;
				}
				_w = _w->next;
			}
			cout << "Adding " << word << endl;
			_w->next = new Word();
			_w = _w->next;
			_w->word = word;
			_w->next = NULL;
			_w->items = new Item();
			_w->items->file = file;
			_w->items->line = line;
			_w->items->next = NULL;
			_w->last = _w->items;

		}
	}



}
