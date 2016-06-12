#include <cstdlib>
#include <iostream>
#include <map>
#include "file.h"
#include "command.h"
#include "termcolor.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
	string parameter, value;
	map <string, Word> data;
	
	Commands commands(argv, argc);
	Indexer application;
	
	parameter = commands.getArgument();
	
	if(parameter == "-i"){
		application.indexFiles(commands.getValues());
	}
	else if(parameter == "-r"){
		application.unIndexFiles(commands.getValues());
	}
	
	//data = application.mapFile("files/file-test-1.txt");
	//data = application.mapFile("files/temer.txt");
	
	return 0;
}
