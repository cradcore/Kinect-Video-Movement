// Corey Craddock
// CS 253
// Implements Frame class


#include <Frame.h>

/* Prints every Point3D object's coordinates in the Frame (There are 25) */
void Frame::printFrame() {

	// If there are not 25 Point3D objects in Frame, throw error
	if(F.size() != 25)
		Error e = "Frame does not hold 25 Point3D objects! It holds " + to_string(F.size()) + "!";

	// Iterate through vector and print Point3D coordinates
	for(unsigned int i = 0; i < F.size(); i++) {

		cout << "(" << F[i].X() << ", " << F[i].Y() << ", " <<
				F[i].Z() << ")" << endl;
		
	}
}

/* Prints the Point3D object's coordinates at a given index */
void Frame::printPoint3D(int index) {
	
	// If there are not 25 Point3D objects in Frame, throw error
	if(F.size() != 25)
		Error e = "Frame does not hold 25 Point3D objects! It holds "  + to_string(F.size()) + "!";

	// Print Point3D coordinate
	
	cout << "(" << getPoint3D(index).X() << ", " << getPoint3D(index).Y() << ", " <<
				getPoint3D(index).Z() << ")" << endl;
	
	
	
}

/* Subtracts the respective values of Point3D P (x,y,z) from every Point3D
 * object in vector F. */
void Frame::subtractAverage(Point3D P) {

	// Get averages
	double x = P.X(),
			y = P.Y(),
			z = P.Z();
	
	// Iterates through all 25 Point3D objects in F
	for(int i = 0; i < 25; i++) {
		
		// Subtract averages
		F[i].subtractX(x);
		F[i].subtractY(y);
		F[i].subtractZ(z);
		
	}
	
}

/* Finds and returns the highest absolute value from all the values in all
 * 25 Point3D objects. */
double Frame::getMaxAbsValue() {
	double max = 0.0;
	
	// Iterate through all 25 Point3D objects in vector F and update max
	for(int i = 0; i < 25; i++) {
		
		Point3D P = F[i];
		if(abs(P.X()) > max)
			max = abs(P.X());
		if(abs(P.Y()) > max)
			max = abs(P.Y());
		if(abs(P.Z()) > max)
			max = abs(P.Z());
	}

	return max;
}

/* Scales all the data in the Frame by multiplying each value in every Point3D
 * object in F by the scale factor. */
void Frame::scaleBy(double factor) {
	
	// Iterate through all 25 Point3D objects in F
	for(int i = 0; i < 25; i++) {
		
		// Scale by factor
		F[i].scaleXYZ(factor);
	}
	
}


