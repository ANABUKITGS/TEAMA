#include "CMapCheckPoint.h"
#include "CSE.h"

void CMapCheckPoint::Update() {
	CMapChip::Update();
}

void CMapCheckPoint::Render(){
	if (!mCheck)
		mTexCheckPoint.DrawImage(CHECKPOINT_POS, CHECKPOINT_UV1, 1.0f);
	else {
		if (check_ani_count > 6)
			check_ani_count = 6;

		mTexCheckPoint.DrawImage(CHECKPOINT_POS, CHECKPOINT_UV2, 1.0f);

		check_ani_count_flame++;
		if (check_ani_count_flame > CHECK_ANI_COUNT_FLAME){
			check_ani_count++;
			check_ani_count_flame = 0;
		}
	}
}

bool CMapCheckPoint::Collision(CRectangle *r) {
	if (CRectangle::Collision(r) && !mCheck){
		if (r->mTag == ECELLNUM::EPLAYER){
			mCheck = true;			
		}
		return true;
	}
	return false;
}