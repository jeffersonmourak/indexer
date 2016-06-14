#ifndef SEARCH_H
#define SEARCH_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#include "file.h"

using namespace std;

class Search{
    private:
        map <string, Word> words;
        vector <File> files;
        string getLine(string filename, int line);
        void printLineHighLight(string line, string key);
        vector <string> split(string str, char delimiter);
    public:
        Search(map <string, Word> w, vector <File> f);
        void find(string key);
        
};


#endif