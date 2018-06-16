// Corey Craddock
// CS 253
// Implements Distance class

#include <Distances.h>


/* Computes and returns the number of the smaller of the Video 
 * objects in the Kinect object. (V1 or V2) */
int Distances::computeSmallest(Video Vid1, Video Vid2) {

	int v1 = Vid1.getSize(),
		v2 = Vid2.getSize();
	
	// Return second Video object if it's smaller
	if(v2 < v1)
		return 2;
	// Return first Video object if it's smaller or they're equal
	else return 1;
	
}

/* Computes the distances between 2 Point3D objects. */
double Distances::computeDistanceAB(Point3D P1, Point3D P2) {
		
	// Get values to compute
	double Ax = P1.X(),
			Ay = P1.Y(),
			Az = P1.Z(),
			Bx = P2.X(),
			By = P2.Y(),
			Bz = P2.Z();
	
	// Compute distances
	double sqDifX = pow(Ax - Bx, 2),
			sqDifY = pow(Ay - By, 2),
			sqDifZ = pow(Az - Bz, 2);
	double sum = sqDifX + sqDifY + sqDifZ;
	double result = sqrt(sum);

	return result; 
}

/* Prints out D to screen. */
void Distances::printD() {
	
	// Iterate through rows
	for(unsigned int i = 0; i < D.size(); i++) {
		cout << "[";
		// Iterate through columns
		for(unsigned int j = 0; j < D[i].size(); j++) {	
			cout << D[i][j] << ", ";
		}
		cout << "]" << endl;
	}
}

/* Prints out W to screen. */
void Distances::printW() {
	
	// Iterate through rows
	for(unsigned int i = 0; i < W.size(); i++) {
		cout << "[";
		// Iterate through columns
		for(unsigned int j = 0; j < W[i].size(); j++) {	
			cout << W[i][j] << ", ";
		}
		cout << "]" << endl;
	}
}

/* Computes the Euclidian distances of the Frames of 
 * V1 & V2 and fills D with these distances. 
 * Formula: DL2(A,T)=sqrt(∑(i=1, 25)(D(A[i],T[i])^2)) */
void Distances::euclidianDistance() {
	
	// Iterate through V1's Frames
	for(int i = 0; i < N; i++) {
		
		// Iterate through V2's Frames
		for(int j = 0; j < M; j++) {
			
			double frameDist = 0;
			Frame f1 = V1.getFrame(i);
			Frame f2 = V2.getFrame(j);
			
			// Iterate through every set of Point3D coordinates in the Frame
			for(int k = 0; k < 25; k++) {
				
				// Get f1 & f2's coordinates at k, compute the distance between them, and add to total distance
				Point3D p1 = f1.getPoint3D(k);
				Point3D p2 = f2.getPoint3D(k);
				double distAB = computeDistanceAB(p1, p2);
				frameDist += (distAB * distAB);
				
			}
			
			// Take the square root
			frameDist = sqrt(frameDist);

			// Fill D with distances
			D[i][j] = frameDist;
		}
	}
	Dinit = true;
}

/* Computes the largest distances of the Frames of 
 * V1 & V2 and fills D with these distances. 
 * Formula: DLinf(A,T)=Max(1<=i<=25)(D(A[i],T[i])) */
void Distances::largestDistance() {
	
	// Iterate through V1's Frames
	for(int i = 0; i < N; i++) {
		
		// Iterate through V2's Frames
		for(int j = 0; j < M; j++) {
			
			double maxDist = 0;
			Frame f1 = V1.getFrame(i);
			Frame f2 = V2.getFrame(j);
			
			// Iterate through every se to Point3D coordinates in the Frame
			for(int k = 0; k < 25; k++) {
				
				// Get f1 & f2's coordinates at k, compute the distance between them, and update max
				Point3D p1 = f1.getPoint3D(k);
				Point3D p2 = f2.getPoint3D(k);
				double distAB = computeDistanceAB(p1, p2);
				if(distAB > maxDist)
					maxDist = distAB;
			}
			
			// Fill D with distances
			D[i][j] = maxDist;
		}
	}
	Dinit = true;
}

/* Computes the median distances of the Frames of 
 * V1 & V2 and fills D with these distances. 
 * Formula: Dmed(A,T)=Median(1<=i<=25)(D(A[i],T[i])) */
void Distances::medianDistance() {
	
	// Iterate through V1's Frames
	for(int i = 0; i < N; i++) {
		
		// Iterate through V2's Frames
		for(int j = 0; j < M; j++) {
			
			Frame f1 = V1.getFrame(i);
			Frame f2 = V2.getFrame(j);
			vector<double> d(25);
			
			// Iterate through every set of Point3D coordinates in the Frame
			for(int k = 0; k < 25; k++) {
				
				// Get f1 and f2's Point3D coordinates, compute the distance between them, and add to distance vector
				Point3D p1 = f1.getPoint3D(k);
				Point3D p2 = f2.getPoint3D(k);
				double distAB = computeDistanceAB(p1, p2);
				d[k] = distAB;
				
			}
			// Sort distance vector
			sort(d.begin(), d.end());

			// Get median value and add it to D
			D[i][j] = d[12];
		}
	}
	Dinit = true;	
}

/* Computes the average distances of the Frames of 
 * V1 & V2 and fills D with these distances. 
 * Formula: Davg(A,T)=(1/25)(∑(i=1, 25)(D(A[i],T[i]))) */
void Distances::averageDistance() {
	
	// Iterate through V1's Frames
	for(int i = 0; i < N; i++) {
		
		// Iterate through V2's Frames
		for(int j = 0; j < M; j++) {
			
			double frameDist = 0;
			Frame f1 = V1.getFrame(i);
			Frame f2 = V2.getFrame(j);
			
			// Iterate through every set of Point3D coordinates in the Frame
			for(int k = 0; k < 25; k++) {
				
				// Get f1 & f2's coordinates at k, compute the distance between them, and add to total distance
				Point3D p1 = f1.getPoint3D(k);
				Point3D p2 = f2.getPoint3D(k);
				double distAB = computeDistanceAB(p1, p2);
				frameDist += distAB;
			}
			
			// Divide sum of distances by 25
			frameDist /= 25;

			// Fill D with distances
			D[i][j] = frameDist;
		}
	}
	Dinit = true;
}

/* Computes the <type> distances between V1 & V2 and
 * fills D with these distances(). */
void Distances::computeDistances(string type) {

	// If type doesn't equal a valid distance type, throw error
	if(!(type == "L2" || type == "Linf" || type == "avg" || type == "med")) 
		Error e("In Kinect::writeToConsole, type must be a valid distance name!");

	// Find what type of distance to use and fill D
	if(type == "L2")
		euclidianDistance();
	else if(type == "Linf")
		largestDistance();
	else if(type == "med")
		medianDistance();
	else if(type == "avg")
		averageDistance();	
}

/* Fills W with the Dynamically Time Warped (DTW) distances of D
 * and returns the total distance of the best possible mapping 
 * between the action and target Videos (the smallest value in 
 * the last row of W.) */
double Distances::DTW() {
	
	// If D is uninitialized, throw error
	if(!Dinit || N == 0 || M == 0)
		Error e("In DTW(), D is not inititalized!");

	// Set up Map and W
	Map.resize(N);
	W.resize(N);
	for(int i = 0; i < N; i++)
		W[i].resize(M);
	for(int i = 0; i < M; i++)
		W[0][i] = D[0][i];
	
	// Variables that hold the miniumun of W[i - 1][j] and it's index
	double min = D[0][0];
	int minInd = 0;


	// Iterate through all the rows (i) of W starting at 1
	for(unsigned int i = 1; i < W.size(); i++) {
		
		// Iterate through all columns (j) of W
		for(unsigned int j = 0; j < W[i].size(); j++) {
			
			// Updates min and minInd if they need to be: Min(W[i - 1][k]), k <= j
			if(W[i - 1][j] < min) {
				min = W[i - 1][j];
				minInd = j;
			}
			
			// Update W[i][j]
			W[i][j] = D[i][j] + min;
		}
		// Reset min for the next row
		min = W[i][0];
		
		// Add minInd to Map
		Map[i] = minInd;
	}
	
	// Print to console
	for(unsigned int j = 0; j < W[N - 1].size(); j++) {
		if( W[N - 1][j] < min)
			min = W[N - 1][j];
	}
	return min;
}


