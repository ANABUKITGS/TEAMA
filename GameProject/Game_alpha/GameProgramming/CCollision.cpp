#include "CCollision.h"

bool CCollision::Collision(CRectangle *rect1, CRectangle *rect2){
	if (rect1->mLeft >= rect2->mRight ||
		rect1->mRight <= rect2->mLeft ||
		rect1->mBottom >= rect2->mTop ||
		rect1->mTop <= rect2->mBottom)
		return false;
	if (rect2->mLeft > rect1->mLeft)
		return true;
	if (rect2->mRight < rect1->mRight)
		return true;
	if (rect2->mBottom > rect1->mBottom)
		return true;
	if (rect2->mTop < rect1->mTop)
		return true;

	return false;
}