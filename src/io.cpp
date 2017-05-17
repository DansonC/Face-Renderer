// io.cpp

#include "../include/io.hpp"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void input(string filename) {
	string line;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			double num = atof(line.c_str());
			num++;
			cout << num << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file"; 
}