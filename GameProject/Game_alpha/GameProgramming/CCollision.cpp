#include "CCollision.h"

bool CCollision::Collision(CRectangle &rect1, CRectangle &rect2){
	if (rect1.mLeft < rect2.mRight &&
		rect1.mRight > rect2.mLeft &&
		rect1.mBottom < rect2.mTop &&
		rect1.mTop > rect2.mBottom)
		return true;
	return false;
}