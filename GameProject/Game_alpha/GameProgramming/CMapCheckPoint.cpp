#include "CMapCheckPoint.h"
#include "CSE.h"

void CMapCheckPoint::Update() {
	CMapChip::Update();
}

bool CMapCheckPoint::Collision(CRectangle *r) {
	if (CRectangle::Collision(r)){
		if (r->mTag == ECELLNUM::EPLAYER){
			mUv[0] = 0;
			mUv[1] = 64;
			mUv[2] = 256;
			mUv[3] = 128;
			
		}
		return true;
	}
	return false;
}