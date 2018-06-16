// Corey Craddock
// CS 253
// Implements Video class

#include <Video.h>


/* Frame getter. */
Frame Video::getFrame(int index) {

	// Check if Frame exists
	if(index < 0 && index >= size)
		Error e("Cannot get Frame at index " + to_string(index) + "!");
	
	// Else return Frame at index
	return Vid[index];
	
}

/* Normalizes each pose so that each Frame is centered and no matter 
 * how big the coordinates are in the input file, it will scale them 
 * down to fit -1 <= x <= 1 a */
void Video::normalize() {

	// If Video contains only 0's, don't normalize
	if(allZeroes())
		return;
	
	// Step 1: Translate poses
	translate();
	
	// Step 2: Scale the data
	scaleData();
	
}

/* Translates poses so that the average coordinate of the base of the
 * spine (1st Point3D coordinate in every frame) is (0,0,0). It does 
 * this by 1) Computing the average (x,y,z) of all of the first points
 * of the frames and then 2) subtracting this number from every point
 * in every pose. */
void Video::translate() {
	
	// Computes the average (x,y,z) of the first Point3D object in every frame
	Point3D average = computeBaseAverage();

	// Iterates through every Frame in Video V
	for(int i = 0; i < size; i++) {
		
		// Subtracts the average from every point in every pose
		Vid[i].subtractAverage(average);
	}
}

/* Computes and returns the average coordinate of the base of the spine for 
 * all frames in the Video. */
Point3D Video::computeBaseAverage() {
	double 	xAv = 0,
			yAv = 0,
			zAv = 0;
	
	// Iterate through Frames (in Vid), only reading the 1st Point3D coordinate
	for(int i = 0; i < size; i++) {
		xAv += Vid[i].getPoint3D(0).X();
		yAv += Vid[i].getPoint3D(0).Y();
		zAv += Vid[i].getPoint3D(0).Z();
	}

	// Compute average by dividing sums by number of lines
	xAv /= size;
	yAv /= size;
	zAv /= size;

	// Create and return Point3D object
	Point3D P(xAv, yAv, zAv);

	return P;
}

/* Scales the data so that it is not too big or too small (-1 <= x <= 1).
 * It does this by 1) Computing the max of the absolute values of all the
 * coordinates and then 2) multiplying every coordinate by a scale of 1.0
 * divided by the maximum number computed in step 1. */
void Video::scaleData() {
	double maxVal = 0;
	
	// Get the maximum absolute value of all the coordinates
	for(int i = 0; i < size; i++) {
		Frame F = getFrame(i);
		double maxFrameVal = F.getMaxAbsValue();

		if(maxFrameVal > maxVal)
			maxVal = maxFrameVal;
	}

	
	// Scale data by this value to fit -1 <= x <= 1
	double scale = 1.0 / maxVal;

	// Iterate through every Frame in the Video
	for(int i = 0; i < size; i++) {

		// Scale data in Frame
		Vid[i].scaleBy(scale);
		
	}
}

/* Adds a Frame to the Video object by adding it to the Frame vector vid. */
void Video::addFrame(Frame F) {

	// Increment size
	size++;
	
	// Resize Vid to fit one more Frame and add Frame F to end
	Vid.push_back(F);
	
}

/* Prints all the coordinates in the Video object. */
void Video::printVideoCoords() {
	
	// Iterates through every Frame in vector Vid and prints it
	for(unsigned int i = 0; i < Vid.size(); i++) {
		cout << "Frame " << i + 1 << ": " << endl << endl;
		Vid[i].printFrame();
	}
}

/* Returns true if the Video object contains all zeroes. */
bool Video::allZeroes() {
	
	for(int i = 0; i < size; i++) {
		Frame F = getFrame(i);
		for(unsigned int j = 0; j < F.getVector().size(); j++) {
			Point3D P = F.getPoint3D(j);
			if(P.X() != 0 || P.Y() != 0 || P.Z() != 0)
				return false;
		}
	}
	return true;
}










