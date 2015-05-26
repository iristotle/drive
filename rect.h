#ifndef RECT_H
#define RECT_H

#include "coord.h"

class Rect{
	public:
		Rect(int x, int y, int w, int l);
		~Rect();

		bool isInside(coord pt);
	private:
		// Upper left corner of rectangle.
		coord mPos;
		int mWidth;
		int mLength;
};

#endif