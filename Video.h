// Corey Craddock
// CS 253
// Header file for video object

#ifndef VIDEO_H_INCLUDE
#define VIDEO_H_INCLUDE

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::to_string;
#include <vector>
using std::vector;

#include <Frame.h>

class Video {

public:
	// Constructor
	Video() {size = 0;}

	// Getters
	int getSize() {return size;}							// Size getter
	Frame getFrame(int index);								// Frame getter

	// Methods
	void normalize();										// Normalizes coordinates in video
	void addFrame(Frame F);									// Adds one Frame object onto the end of the vector Vid
	void printVideoCoords();								// Prints all the coordinates in the Video object
	bool allZeroes();										// Returns true if the Video object only contains zeroes

private:
	// Methods
	void translate();										// Used in normalize(), translates every frame
	Point3D computeBaseAverage();							// Used in translate(), computes the average of every base coordinate (1st set)
	void scaleData();										// Used in normalize(), scales the data to fit between -1 < x < 1

	// Variables
	vector<Frame> Vid;										// Vector holding all the Frame objects that make a Video
	int size;												// Number of frames in the Video object
};

#endif				// VIDEO_H_INCLUDE
