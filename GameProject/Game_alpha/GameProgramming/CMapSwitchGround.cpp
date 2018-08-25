#include "CMapSwitchGround.h"
#include "CPlayerT.h"

ECELLNUM CMapSwitchGround::mNumber;

void CMapSwitchGround::Update() {
	CMapChip::Update();
}


bool CMapSwitchGround::Collision(CRectangle *r) {
	CVector2 aj;
	if (mNumber == mTag){
		// ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
		if (r->mTag == ECELLNUM::EPLAYER ||
			r->mTag == ECELLNUM::EENEMY1 ||
			r->mTag == ECELLNUM::EENEMY2 ||
			r->mTag == ECELLNUM::EENEMY3 |
			r->mTag == ECELLNUM::EBOSS){
			if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
				//ç∂âE
				if (mPosition.x - mScale.x > r->mPosition.x || mPosition.x + mScale.x < r->mPosition.x) {
					//ç∂
					if (mPosition.x - mScale.x > r->mPosition.x) {
						r->mPosition.x = r->mPosition.x - aj.x;
					}
					//âE
					if (mPosition.x + mScale.x < r->mPosition.x) {
						r->mPosition.x = r->mPosition.x - aj.x;
					}
				}
				//è„â∫
				else {
					//â∫
					if (mPosition.y - mScale.y > r->mPosition.y) {
						r->mPosition.y = r->mPosition.y - aj.y;
						r->mVelocityY = 0.0f;
					}
					//è„
					if (mPosition.y + mScale.y < r->mPosition.y) {
						r->mPosition.y = r->mPosition.y - aj.y;
						r->mVelocityY = 0.0f;
						if (r->mTag == ECELLNUM::EPLAYER)
							CPlayerT::mpPlayer->mJumpCount = 0;
					}
				}
				return true;
			}
		}
	}
	return false;
}

void CMapSwitchGround::Render(){
	if (mTag == ECELLNUM::ESWITCH_GROUND1){
		if (mNumber == mTag){
			if (mAlpha1 < 1.0f)
				mAlpha1 += 0.05f;
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV1, mAlpha1);
		}
		else{
			if (mAlpha1 > 0.5f)
				mAlpha1 -= 0.05f;
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV1, mAlpha1);
		}
	}

	if (mTag == ECELLNUM::ESWITCH_GROUND2){
		if (mNumber == mTag){
			if (mAlpha2 < 1.0f)
				mAlpha2 += 0.05f;
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV2, mAlpha2);
		}
		else{
			if (mAlpha2 > 0.5f)
				mAlpha2 -= 0.05f;
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV2, mAlpha2);
		}
	}
}

void CMapSwitch::Update() {
	mCollisionInterval--;
	CMapChip::Update();
}

bool CMapSwitch::Collision(CRectangle *r) {
	// ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	if (CRectangle::Collision(r)) {
		//ïêäÌÇ…è’ìÀ
		if (r->mTag == ECELLNUM::EPWEAPON && mCollisionInterval < 0) {
			if (CMapSwitchGround::mNumber == ECELLNUM::ESWITCH_GROUND1)
				CMapSwitchGround::mNumber = ECELLNUM::ESWITCH_GROUND2;
				else
					CMapSwitchGround::mNumber = ECELLNUM::ESWITCH_GROUND1;
				mCollisionInterval = SWITCH_INTERVAL;
				switch_ani_count_frame = 0;
		}
		return true;
	}
	return false;
}

void CMapSwitch::Render(){
	switch (CMapSwitchGround::mNumber){
	case ECELLNUM::ESWITCH_GROUND2:
		if (switch_ani_count > 2)
			switch_ani_count = 2;

		mTexSwitch.DrawImage(SWITCH_POS, SWITCH_UV, 1.0f);
		break;

	case ECELLNUM::ESWITCH_GROUND1:
		if (switch_ani_count <= 0)
			switch_ani_count = 0;

		mTexSwitch.DrawImage(SWITCH_POS, SWITCH_UV, 1.0f);
		break;

	default:
		break;
	}

	switch_ani_count_frame++;
	if (switch_ani_count_frame > SWITCH_ANI_COUNT_FRAME){
		if (CMapSwitchGround::mNumber == ECELLNUM::ESWITCH_GROUND2 && switch_ani_count < 2)
			switch_ani_count++;

		else if (CMapSwitchGround::mNumber == ECELLNUM::ESWITCH_GROUND1 && switch_ani_count > 0)
			switch_ani_count--;

		switch_ani_count_frame = 0;
	}
}