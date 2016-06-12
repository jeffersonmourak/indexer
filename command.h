#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>

using namespace std;

class Commands{
    private:
        char const **arguments;
        int argumentSize;
        vector<string> values;
        string argument;
        
    
    public:
        Commands(char const *argv[], int length);
        void read();
        string getArgument();
        vector<string> getValues();
};

#endif