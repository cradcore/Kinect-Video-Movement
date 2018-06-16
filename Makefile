PA7: main.o Kinect.o Video.o Frame.o PoseDisplay.o  Distances.o
	g++ -Wall -std=c++11 -I. -lX11 -g main.o Kinect.o Video.o Frame.o PoseDisplay.o Distances.o -o PA7
main.o: main.cpp Kinect.h
	g++ -Wall -std=c++11 -I. -c -lX11 -g main.cpp
Kinect.o: Kinect.cpp Kinect.h Video.h Distances.h PoseDisplay.h
	g++ -Wall -std=c++11 -I. -c -lX11 -g Kinect.cpp
Video.o: Video.cpp Video.h Frame.h
	g++ -Wall -std=c++11 -I. -c -lX11 -g Video.cpp
Frame.o: Frame.cpp Frame.h Point3D.h
	g++ -Wall -std=c++11 -I. -c -lX11 -g Frame.cpp
PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h Point3D.h Error.h
	g++ -Wall -std=c++11 -I. -c -lX11 -g PoseDisplay.cpp
Distances.o: Distances.cpp Distances.h Video.h 
	g++ -Wall -std=c++11 -I. -c -lX11 -g Distances.cpp
clean:
	rm *.o PA7
	make
clear:
	rm *.o *.tar PA7
clearAll:
	rm *.cpp *.h *.o *.tar PA7 Makefile
tar:
	tar -cvf PA7.tar *.cpp *.h Makefile
untar:
	tar -C ~/Downloads/Testing/PA7 -xvf PA7.tar
