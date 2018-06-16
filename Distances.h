// Corey Craddock
// CS 253
// Header file for Distances class

#ifndef DISTANCES_H_INCLUDED
#define DISTANCES_H_INCLUDED

#include <fstream>
using std::ofstream;
#include <cmath>
#include <algorithm>
using std::sort;

#include <Video.h>

class Distances {
public:
	// Constructor
	Distances(Video Vid1, Video Vid2){

		// Make V1 the smaller Video object
		int s = computeSmallest(Vid1, Vid2);
		if(s == 1) {
			V1 = Vid1;
			V2 = Vid2;
		}
		else {
			V2 = Vid1;
			V1 = Vid2;
		}

		// Set variables
		N = V1.getSize();
		M = V2.getSize();

		// Resize D to be an N x M array
		D.resize(N);
		for(int i = 0; i < N; i++)
			D[i].resize(M);
	}

	// Methods
	void printD();													// Prints the contents of D
	void printW();													// Prints the contents of W
	void computeDistances(string type);								// Computes the <type> distances of V1 & V2 and fills D with them
	double DTW();													// Fills W with the DTW'd distances of D and returns best distance

	// Getters
	vector<vector<double>> getD() {return D;}						// D getter
	vector<vector<double>> getW() {return W;}						// W getter
	vector<int> getMap() {return Map;}								// Map getter

private:
	// Variables
	int N;															// Number of frames in V1
	int M;															// Number of frames in V2
	Video V1;														// Smaller Video object (Action video)
	Video V2;														// Bigger Video object (Target video)
	vector<vector<double>> D;										// Holds the array of distances between V1 and V2
	vector<vector<double>> W;										// Holds the array of modified distances between V1 and V2
	bool Dinit;														// Whether D has been initialized or not
	vector<int> Map;												// Holds the mappings between V1 and V2

	// Methods
	int computeSmallest(Video Vid1, Video Vid2);					// Computes the smaller of the two Video objects
	double computeDistanceAB(Point3D P1, Point3D P2);				// Computes distances between two points
	void euclidianDistance();										// Calculates and returns the Euclidian distance of V1 & V2
	void largestDistance();										// Calculates and returns the largest distance of V1 & V2
	void medianDistance();										// Calculates and returns the median distance of V1 & V2
	void averageDistance();										// Calculates and returns the average distance of V1 & V2

};



#endif	// DISTANCES_H_INCLUDED
