#include <iostream>
#include "command.h"

using namespace std;

Commands::Commands(char const *argv[], int length){
    this->arguments = argv;
    this->argumentSize = length;
    this->read();
}

void Commands::read(){
    this->argument = this->arguments[1];
    for(int i = 2; i < this->argumentSize; i++){
        this->values.push_back(this->arguments[i]);
    }
}

string Commands::getArgument(){
    return this->argument;
}

vector<string> Commands::getValues(){
    return this->values;
}