#include "car.h"
#include <fstream>
#include <sstream>

// Constructor
Car::Car(char* map, char* route)
	: mMapFile(map),
	  mRouteFile(route),
	  mCurDirection(Direction::EAST)
{
	using namespace std;

	// Initialize car position
	mCurPos.x = 0;
	mCurPos.y = 0;

	// Read the file containing rectangle coordinates.
	// Parse the file to populate a vector of Rectangle objects.
	ifstream rectfile(mMapFile);
	while(rectfile.good()){
		string line;
		getline(rectfile, line);
		int x, y, w, l;
		stringstream ss(line);
		ss >> x >> y >> w >> l;
		Rect r = Rect(x,y,w,l);
		mRectangles.push_back(r);
	}
	// Debug check the size of the Rectangle vector.
	printf("Size of mRectangles vector: %zd\n", mRectangles.size());
}

// Destructor
Car::~Car()
{
}

void 
Car::drive()
{
	// Output message to announce the car has started driving.
	cout << "Start driving car" << endl;

	// Read the file containing driving instructions.
	ifstream drivefile(mRouteFile);
	while(drivefile.good()){
		string line;
		getline(drivefile, line);
		char op;
		int val;
		stringstream ss(line);
		ss >> op >> val;
		switch(op)
	      {
	         case 'R':
	         	printf("Car turned right.\n");
	         	// Rotate the car 90 deg clockwise.
	         	mCurDirection = (Direction)((mCurDirection+1) % 4);
	            break;
	         case 'L':
	         	printf("Car turned left.\n");
	         	// Rotate the car 90 deg counter clockwise.
	         	mCurDirection = (Direction)((mCurDirection-1) % 4);
	            break;
	         case 'B':
	         	printf("Car moved backward %d spaces\n",val);
	         	// Move the car backward val number of spaces.
	         	updatePosition(0,val);
	         	break;
	         case 'F':
	         	printf("Car moved forward %d spaces\n",val);
	         	// Move the car forward val number of spaces.
	         	updatePosition(1,val);
	         	break;
	         default:
	         	printf("Error. Unrecognized car instruction %c\n",op);
	            exit(1);
	      }

	    // After executing a single instruction from the driving
	    // instructions file:

	    // Output the direction the car is facing.
	    const char* direction_txt[] = {"North", "East", "South", "West"};
	    printf("Car is facing: %s\n",direction_txt[mCurDirection]);
	    // Output the 2D position of the car.
	    printf("Car position, x:%d y:%d\n",mCurPos.x,mCurPos.y);
	}
}

void
Car::updatePosition(int fb, int amt)
{
	coord newPos;
	switch(mCurDirection)
    {
      	 // TODO: Account for bounds of world.
      	 // eg if the car "drives off the page", where should
      	 /// it go?  Wrap-around?
		case Direction::NORTH:
			// +y
			newPos.y= fb? mCurPos.y+1 : mCurPos.y-1;
			break;
		case Direction::EAST:
			// +x
		 	newPos.x= fb? mCurPos.x+1 : mCurPos.x-1;
			break;
		case Direction::SOUTH:
			// -y
		 	newPos.y= fb? mCurPos.y-=1 : mCurPos.y+1;
			break;
		case Direction::WEST:
			// -x
		 	newPos.x= fb? mCurPos.x-=1 : mCurPos.x+1;
			break;
		default:
			printf("Error. Direction variable invalid.\n");
			exit(1);
    }

    // Check if the car has crossed a rectangle boundary.
    isCrossingBoundary(mCurPos,newPos);

    // Update the car's position to the new position.
    mCurPos = newPos;
}

void
Car::isCrossingBoundary(coord cPos, coord nPos)
{
	bool inRectBefore;
	bool inRectNow;

	// Check every rectangle in the world for whether
	// the car's current and new position are inside/outside
	// the rectangle.
	for (std::vector<Rect>::iterator r = mRectangles.begin();
			r != mRectangles.end(); ++r) {

		inRectBefore = r->isInside(cPos);
		inRectNow = r->isInside(nPos);
		
		if (!inRectBefore && inRectNow)
		{
			printf("Entered rect\n");
		} 
		else if (inRectBefore && !inRectNow)
		{
			printf("Exited rect\n");
		} 
		else 
		{
			printf("Did not enter or exit.\n");
		}
	}

}