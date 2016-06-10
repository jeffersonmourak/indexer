#include <cstdlib>
#include <iostream>
#include <map>
#include "file.h"
#include "termcolor.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
	string parameter, value;
	map <string, Word> data;

	//parameter = argv[1];
	//value = argv[2];
	

	/*switch(parameter){
		case "-i": 
			if(value)
	}*/

	//mapFile("files/file-test-1.txt");
	data = mapFile("files/temer.txt");

	return 0;
}
