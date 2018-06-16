// Corey Craddock
// CS 253
// Header file for the Kinect object

#ifndef KINECT_H_INCLUDE
#define KINECT_H_INCLUDE

#include <iostream>
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::istringstream;
using std::stringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
using std::getline;
using std::to_string;
#include <vector>
using std::vector;
#include <sstream>
#include <stdlib.h>
#include <ios>
#include <cmath>
using std::abs;

#include <Video.h>
#include <Distances.h>
#include <PoseDisplay.h>

class Kinect {

public:
	/// Constructor doxygen comment
	Kinect(int numActions) { 
		lineInd = -1;
		elemNum = 0;
		actions.resize(numActions, Video());						// Resize and initialize every Video in actions
		distances.resize(numActions, 0);							// Resize and initialize every double in distances
	}

	// Getters
	Video getVideo(int index) {return actions[index];}				// Action Video getter
	vector<Video> getActions() {return actions;}					// Vector of Action Videos getter
	vector<double> getDistances() {return distances;}				// Vector of distances getter

	// Methods
	void checkElement(string elem);									// Verifies syntax of element, if incorrect, throws error
	void readFile(string fileName, int vidIndex);					// Reads input file, checks syntaxs, and puts into Video object
	void printCoord(int coordIndex, int vidIndex);					// Prints the coordinates of a Frame at index, or all Frames (index = -1)
	void normalizeVideo(int index);									// Normalizes the Video oject 
	Frame lineToFrame(string line);									// Converts a line of 75 doubles to a Frame variable
	int computeDistances(string distType);							// Computes and fills distances and returns shortest one

private:
	// Varibables
	vector<double> distances;										// Holds distances between the i'th Video in actions and target
	vector<Video> actions;											// Vector of Action Videos
	Video target;													// Target Video
	int lineInd;													// Holds the index of the line being read (starting at 0)
	int elemNum;													// Holds the element number in a line
};


#endif				// KINECT_H_INCLUDE
