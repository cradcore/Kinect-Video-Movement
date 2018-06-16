// Corey Craddock
// CS 253
// Implements the Kinect class

#include <Kinect.h>


/** Checks if an individual element is of valid syntax. If it is, the function
 * does nothing, else, the function throws an error. */
void Kinect::checkElement(string elem) {
	
	bool dot = false,
		dash1 = false,
		dash2 = false,
		e = false;

	// If elem contains nothing, don't incrmeent elemNum
	if(elem.size() == 0)
		elemNum--;
	
	// Iterates through element character by character and throws error if the character is not valid
	for(unsigned int i = 0; i < elem.size(); i++) {

		// If the last element has a newline character, ignore
		if(elem[i] == '\r' || elem[i] == '\n') {
			if(elem == "\r" || elem == "\n")
				elemNum--;
			break;
		}

		// If elemenet contains a non-digit, (except for a space, tab, dot, dash, or e) throw error
		if(!isdigit(elem[i]) && elem[i] != ' ' && elem[i] != '\t' && elem[i] != '.' && elem[i] != '-' && elem[i] != 'e')
			Error e("\"" + elem + "\" contains an invalid character! (" + elem[i] + ")", lineInd, elemNum);

		// If elem equals a tab, don't incrment elemNum and break
		if(elem == "\t") {
			elemNum--;
			break;
		}
		
		// If element contains more than one dot, throw error
		if(elem[i] == '.' && dot)
			Error e("\"" + elem + "\" contains multiple dots!", lineInd + 1, elemNum);
		
		// If element contains more than two dashes, throw error
		if(elem[i] == '-' && (dash1 && dash2))
			Error e("\"" + elem + "\" contains more than two dashes!", lineInd + 1, elemNum);

		// If element contains more than one e, throw error
		if(elem[i] == 'e' && e)
			Error e("\"" + elem + "\" contains multiple e's!", lineInd + 1, elemNum);

		// If element contains a dot, doash, or e, update it's repsective boolean value(s)
		if(elem[i] == '.')
			dot = true;
		if(elem[i] == '-') {
			if(!dash1)
				dash1 = true;
			else dash2 = true;
		}
		if(elem[i] == 'e')
			e = true;

	}
}

/* Reads file and returns true only if it is a readable file and has
 * valid syntax. (75 doubles per row, separated by whitespace) If the
 * syntax if valid, it puts every set of coordinates into a Point3D
 * object, and every line into a Frame object. */
void Kinect::readFile(string fileName, int vidIndex) {

	// Determine which Video object to use
	Video *V;
	if(vidIndex == -1)
		V = &target;
	else V = &actions[vidIndex];

	bool blankLine = false;
	string line = "";

	// Create ifstream from the input file
	ifstream file(fileName);
	
	// Return error if file not valid
	if(file.fail())
		Error e("File " + fileName + " failed to open!", lineInd, elemNum);
	
	// Iterate through each line of the input file
	while(getline(file, line)) {
		stringstream ss(line);
		string elem;
		lineInd++;
		
		// If there is a blank line, but it is not at the end of a file, return error
		if(blankLine)
			Error e("Line is blank!", lineInd, elemNum);
		
		// Delemit line into individual elements and iterate through them
		while(getline(ss, elem, ' ')) {
			elemNum++;
			
			// Check if element is valid
			checkElement(elem);
		}

		// If line is not 75 elements (unless it is the last line, in which case it must have 0), throw error
		if(elemNum != 75) {
			if(!blankLine && elemNum == 0) {
				blankLine = true;
				lineInd--;
				continue;
			}
			else Error e("Line is not 75 elements!", lineInd + 1, elemNum);
		}

		// If there are no errors, get Frame, and add to Video
		Frame f = lineToFrame(line);
		(*V).addFrame(f);
		elemNum = 0;
	}
	
	// If file is empty, throw error
	if(lineInd == -1)
		Error e("File " + fileName + " is empty!", lineInd, elemNum);
		
	// Cleanup
	file.close();
}

/* Parses a line into individual sets of coordinates and puts each
 * pair of three coordinates into a Point3D object vector. Once the
 * vector is 25 long, a Frame object is made and returned. */
Frame Kinect::lineToFrame(string line) {
	
	double x,
			y,	
			z;
	int i = 0;
	vector<Point3D> frame(25);
	stringstream ss(line);
	string elem;
	
	// Delimit line into individual elements
	while(getline(ss, elem, ' ')) {
		
		// If elem is a newline character, break
		if(elem == "\r" || elem == "\n")
			break;

		// Place each set of three coordinates into x, y, and z variables
		const char *tempElem = elem.c_str();

		// If elem is empty or a tab, keep getting next until not empty (x)
		while(elem.size() == 0 || elem == "\t")
			getline(ss, elem, ' ');

		x = atof(tempElem);
		getline(ss, elem, ' ');

		// If elem is empty or a tab, keep getting next until not empty (y)
		while(elem.size() == 0 || elem == "\t")
			getline(ss, elem, ' ');

		y = atof(tempElem);
		getline(ss, elem, ' ');

		// If elem is empty or a tab, keep getting next until not empty (z)
		while(elem.size() == 0 || elem == "\t")
			getline(ss, elem, ' ');

		z = atof(tempElem);
		
		// Create Point3D object from coordinates
		Point3D p(x, y, z);
		
		// Add Point3D object to Point3D vector
		frame[i] = p;
		i++;
		
	}

	// If Frame does not have 25 Point3D objects, throw error
	if(i != 25)
		Error e("Line does not have 25 sets of coordinates, so cannot create Frame object!", lineInd, elemNum);

	// Create and return Frame object
	Frame F(frame);

	return F;
}

/* Prints all the coordinates either for a certain frame in the video V 
 * (at ind) or, if ind = -1, then prints all coordinates for all Frames. */
void Kinect::printCoord(int coordIndex, int vidIndex) {

	// Determine which Video object to use
	Video *V;
	if(vidIndex == -1)
		V = &target;
	else V = &actions[vidIndex];

	int s = (*V).getSize();
	
	// Print single Frame's coordinates
	if(coordIndex >= 0 && coordIndex < s) {
		cout << endl << endl << "Frame number: " << coordIndex + 1 << endl;
		Frame F = (*V).getFrame(coordIndex);
		F.printFrame();
	}	
	
	// Print every Frame's coordinates
	else {

		for(int i = 0; i < s ; i++) {
			cout << endl << endl << "Frame number: " << i+ 1 << endl;
			Frame F = (*V).getFrame(i);
			F.printFrame();
		}	
	}

}

/* Normalizes the Video object */
void Kinect::normalizeVideo(int index) {

	// Determine which Video object to use
	Video *V;
	if(index == -1)
		V = &target;
	else V = &actions[index];

	// Normalize
	(*V).normalize();
}

/* Computes the distance from Target Video and every Action 
 * Video in actions and fills the corrensponding index in 
 * distances with the <distType> distance between actions[i]
 * and target. Returns the index of the shortest distance. */
int Kinect::computeDistances(string distType) {

	// Compute distance for 1st Action Video
	double shortestDistance;
	int shortestIndex = 0;
	Distances tempDist(target, actions[0]);
	tempDist.computeDistances(distType);
	shortestDistance = tempDist.DTW();
	distances[0] = shortestDistance;
	
	// Compute distances for remaining Action Videos
	for(unsigned int i = 1; i < actions.size(); i++) {
		Distances Dist(target, actions[i]);
		Dist.computeDistances(distType);
		double distance = Dist.DTW();
		distances[i] = distance;
			
		// If any distance is the shortest, update shortestDistance
		if(distance < shortestDistance) {
			shortestDistance = distance;
			shortestIndex = i;
		}
	}
	
	return shortestIndex;
		
}










