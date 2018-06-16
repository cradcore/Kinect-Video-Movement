// Corey Craddock
// CS 253
// Contains the Point3D class declaration
 
#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

#include <iostream>
using std::ostream;
#include <cmath>
using std::abs;
#include <iostream>
using std::cout;
using std::endl;

#include <Error.h>

/* Real-valued points in 3 space, i.e. (x, y, z)

 * Point3D is the base class for storing points in 3 space and accessing their coordinates. The
 * PoseDisplay class will write out and display vectors of 25 Point3Ds (obviously, their order matters!).
  
 * The Point3D class as implemented here is sufficient for Programming Assignment #1. As the semester
 * progresses, however, students are encouraged to extend this class by adding new methods, new overloaded
 * operators, and new data fields as necessary. As long as the X(), Y(), Z() methods and the << operator
 * below are retained, the PoseDisplay class will work with modifications of the Pose3D class. Students
 * are also encouraged new classes, including classes that might contain Point3D fields.
 */

class Point3D {
public:
	/// Constructor
	Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

	// Getters
	inline double X() const {return x;}									// Returns the X coordinate of the point
	inline double Y() const {return y;}									// Returns the Y coordinate of the point
	inline double Z() const {return z;}									// Returns the Z coordinate of the point

	// Methods
	void subtractX(double amount) {x -= amount;}						// Subtracts amount from x value
	void subtractY(double amount) {y -= amount;}						// Subtracts amount from y value
	void subtractZ(double amount) {z -= amount;}						// Subtracts amount from z value
	void scaleXYZ(double factor) {				
//		cout << "(" << x << ", " << y << ", " << z << ")" << endl;
		x *= factor;
		y *= factor;
		z *= factor;
//		cout << "(" << x << ", " << y << ", " << z << ")" << endl;
	}

protected:
	// Variables
	double x;															// x coordinate (real value)
	double y;															// y coordinate (real value)
	double z;															// z coordinate (real value)
};

/// Overload of << operator for Point3D. Prints out as three real values, separated by spaces with a trailing space.
inline ostream& operator << (ostream& ostr, const Point3D& pt) {ostr << pt.X() << " " << pt.Y() << " " << pt.Z() << " "; return ostr;}

#endif 				// POINT3D_H_INCLUDED

