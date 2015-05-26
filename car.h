#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <vector>
#include "coord.h"
#include "rect.h"

// TODO: Is it ok to have this in a .h file?
using namespace std;  // namespace of vector

// how to use typedef of enum
// http://stackoverflow.com/questions/20426716/
// how-to-use-typedef-and-typedef-enum-in-c
typedef enum Direction
{
	NORTH, 
	EAST, 
	SOUTH, 
	WEST
} Direction;

class Car{
	public:
		// Constructor
		Car(char* map, char* route);
		// Destructor
		~Car();

		// Methods
		void drive();
		// 'fb' stands for forward/backward, 1/0 respectively.
		void updatePosition(int fb, int amt); 
		void isCrossingBoundary(coord cPos, coord nPos);

	private:
		char* mMapFile; // filename holding rectangles
		char* mRouteFile; // filename holding car instructions
		vector<Rect> mRectangles; // vector of Rectangle objects
		vector<string> mInstructions; // vector of instructions
		coord mCurPos;  // current position
		Direction mCurDirection; // car currently facing this direction
};

#endif // CAR_H