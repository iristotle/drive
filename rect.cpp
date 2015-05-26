#include "rect.h"

Rect::Rect(int x, int y, int w, int l)
	:mWidth(w),
	 mLength(l)	
{
	struct coord p;
	p.x = x;
	p.y = y;
	mPos = p;
}

Rect::~Rect()
{
}

bool
Rect::isInside(coord pt){
	if ((mPos.x <= pt.x) && 
	   (pt.x <= mPos.x + mWidth) &&
	   (mPos.y <= pt.y) &&
	   (pt.y <= mPos.y+mLength)) {
		// pt is inside the rectangle
		// including the borders.
		return true;
	} else {
		// pt is outside the rectangle
		return false;
	}
}