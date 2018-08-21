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
				//ç∂
				if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
				//âE
				if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
				//â∫
				if (mPosition.y > r->mPosition.y) {
					r->mPosition.y = r->mPosition.y - aj.y;
					r->mVelocityY = 0.0f;
				}
				//è„
				if (mPosition.y < r->mPosition.y) {
					r->mPosition.y = r->mPosition.y - aj.y;
					r->mVelocityY = 0.0f;
					if (r->mTag == ECELLNUM::EPLAYER)
						CPlayerT::mpPlayer->mJumpCount = 0;
				}
				return true;
			}
		}
	}
	return false;
}

void CMapSwitchGround::Render(){
	if (mTag == ESWITCH_GROUND1){
		if (mNumber == mTag)
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV1, 1.0f);

		else
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV1, 0.5f);
	}

	if (mTag == ESWITCH_GROUND2){
		if (mNumber == mTag)
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV2, 1.0f);

		else
			mTexSwitchGround.DrawImage(SWITCH_GROUND_POS, SWITCH_GROUND_UV2, 0.5f);
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
		if (r->mTag == EPWEAPON && mCollisionInterval < 0) {
				if (CMapSwitchGround::mNumber == ESWITCH_GROUND1)
					CMapSwitchGround::mNumber = ESWITCH_GROUND2;
				else
					CMapSwitchGround::mNumber = ESWITCH_GROUND1;
				mCollisionInterval = SWITCH_INTERVAL;
		}
		return true;
	}
	return false;
}