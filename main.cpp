// Corey Craddock
// CS 253
// Main method for Kinect assignments

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <fstream>
using std::ifstream;

#include <Kinect.h>

int main(int argc, char *argv[]) {

	// Verify correct number of arguments were passed, otherwise throw error
	if(argc < 4) {
		string s = argv[0];
		Error e("File " + s + " must have at least three arguments!");
	}
	
	// Create Kinect object
	Kinect k(argc - 3);
	
	// Read and normalize Target Video
	k.readFile(argv[1], -1);
	k.normalizeVideo(-1);
	
	// Read and normalize Action Video(s)
	for(int i = 2; i < argc - 1; i++) {
		k.readFile(argv[i], i - 2);
		k.normalizeVideo(i - 2);
	}
	
	// Write name of shortest distance to console
	int shortInd = k.computeDistances(argv[argc - 1]);
	cout << argv[shortInd + 2] << endl;
	
	return 0;
}
