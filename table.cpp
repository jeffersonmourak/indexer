#include <iostream>
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
	}
	else{
		Word *_w = &w[index];

		while(_w->next != NULL){
			if(_w->word == word){
				Item *i = _w->items;

				while(i->next != NULL){
					i = i->next;
				}

				Item *newItem = new Item();
				newItem->file = file;
				newItem->line = line;
				i->next = newItem;

			}
			_w = _w->next;
		}

		Word *newWord = new Word();
		newWord->word = word;
		newWord->next = NULL;
		newWord->items = new Item();
		newWord->items->file = file;
		newWord->items->line = line;
		newWord->items->next = NULL;
		_w->next = newWord;

		return;

	}



}
