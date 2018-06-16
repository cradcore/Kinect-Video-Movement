// Corey Craddock
// CS 253
// Header class for handling errors

#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <iostream>
using std::cerr;
using std::endl;
#include <string>
using std::string;

class Error {

public:
	// Constructor
	Error(string message = "", int lineInd = -1, int elemNum = -1) : message(message), lineInd(lineInd), elemNum(elemNum) {
		if(lineInd == -1 && elemNum == -1) {
			cerr << "Error! " << message << endl;
		}
		else {
			cerr << "Error! " << message << endl
				<< "Line number: " << lineInd + 1 << endl
				<< "Element number: " << elemNum << endl;
		}

		exit(-1);
	}

private:
	// Variables
	string message;
	int lineInd;
	int elemNum;

};

#endif		// ERROR_H_INCLUDED
