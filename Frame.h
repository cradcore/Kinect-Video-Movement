// Corey Craddock
// CS 253
// Header file for Frame object

#ifndef FRAME_H_INCLUDE
#define FRAME_H_INCLUDE

#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::to_string;

#include <Point3D.h>


class Frame {

public:
	// Constructor
	Frame(vector<Point3D> frame): F(frame) {	}

	// Getters
	Point3D getPoint3D(int index) {return F[index];}				// Point3D getter for specific index
	vector<Point3D> getVector() {return F;}							// Getter for the vector of Point3D objects
	
	// Methods
	void printFrame();													// Prints every Point3D coordinate in the Frame
	void printPoint3D(int index);									// Prints the Point3D coordinate at a specific index
	void subtractAverage(Point3D P);								// Subtracts the (x,y,z) points in P from every Point3D in F
	double getMaxAbsValue();										// Returns the maximum absolute value of all values in all Point3Ds
	void scaleBy(double factor);									// Multiplies all values in Point3Ds in F by factor

private:
	// Variables
	vector<Point3D> F;												// Vector holding the 25 Point3D objects that make up 1 Frame
	
};

#endif				// FRAME_H_INCLUDE
