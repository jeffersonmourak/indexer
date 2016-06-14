#include <cstdlib>
#include <iostream>
#include <map>
#include "file.h"
#include "command.h"
#include "search.h"
#include "termcolor.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
	string parameter, value;
	
	Commands commands(argv, argc);
	Indexer application;
	Search search(application.getWords(), application.getFiles());
	
	
	parameter = commands.getArgument();
	
	if(parameter == "-i"){
		application.indexFiles(commands.getValues());
	}
	else if(parameter == "-r"){
		application.unIndexFiles(commands.getValues());
	}
	else if(parameter == "-li"){
		application.listFiles();
	}
	else if(parameter == "-lt"){
		application.listDec();
	}
	else if(parameter == "-la"){
		application.listAlpha();
	}
	else if(parameter == "-bAND"){
		search.find(commands.getValues()[0]);
	}
	
	
	return 0;
}
