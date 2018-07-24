#include "2DLib.h"

void AddY(CRectangle*rect, float i){
	rect->mBottom += i;
	rect->mTop += i;
}
void AddX(CRectangle*rect, float i){
	rect->mLeft += i;
	rect->mRight += i;
}

bool Collision(CRectangle*prect1, CRectangle*prect2){
	if (prect2->mEnabled == false)
		return false;
	else if (prect1->mLeft >= prect2->mRight ||
		prect1->mRight <= prect2->mLeft ||
		prect1->mBottom >= prect2->mTop ||
		prect1->mTop <= prect2->mBottom)
		return false;
	return true;
}