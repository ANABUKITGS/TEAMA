#include "CMapCheckPoint.h"
#include "CSE.h"

void CMapCheckPoint::Update() {
	CMapChip::Update();
}

void CMapCheckPoint::Render(){
	if (mCheck == ECHECKPOINT_NUM::EENEMY){
		if (check_ani_count > 1)
			check_ani_count = 0;
	}

	else if (mCheck == ECHECKPOINT_NUM::ECHANGE){
		if (check_ani_count > 7){
			check_ani_count = 5;
			mCheck = ECHECKPOINT_NUM::EPLAYER;
		}
	}

	else if (mCheck == ECHECKPOINT_NUM::EPLAYER){
		if (check_ani_count > 7)
			check_ani_count = 5;
	}

	mTexCheckPoint.DrawImage(CHECKPOINT_POS, CHECKPOINT_UV, 1.0f);
	check_ani_count_flame++;
	if (check_ani_count_flame > CHECK_ANI_COUNT_FLAME){
		check_ani_count++;
		check_ani_count_flame = 0;
	}
}

bool CMapCheckPoint::Collision(CRectangle *r) {
	if (CRectangle::Collision(r) && mCheck == ECHECKPOINT_NUM::EENEMY){
		if (r->mTag == ECELLNUM::EPLAYER){
			mCheck = ECHECKPOINT_NUM::ECHANGE;
			check_ani_count = 0;
		return true;
		}
	}
	return false;
}