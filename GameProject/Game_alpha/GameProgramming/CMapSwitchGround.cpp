#include "CMapSwitchGround.h"

ECELLNUM CMapSwitchGround::mNumber;

void CMapSwitchGround::Update() {
	CMapChip::Update();
}


//bool CMapSwitchGround::Collision(CRectangle *r) {
//	// 当たっているか
//	if (CRectangle::Collision(r)) {
//		//プレイヤーまたは武器に衝突
//		if (r->mTag == EPLAYER || r->mTag == EPWEAPON) {
//			//無効にする
//			mEnabled = false;
//			return true;
//		}
//	}
//	return false;
//}


void CMapSwitch::Update() {
	CMapChip::Update();
}

bool CMapSwitch::Collision(CRectangle *r) {
	// 当たっているか
	if (CRectangle::Collision(r)) {
		//武器に衝突
		if (r->mTag == EPLAYER && !mCollision) {
			if (CMapSwitchGround::mNumber == ESWITCH_GROUND1)
				CMapSwitchGround::mNumber = ESWITCH_GROUND2;
			else
				CMapSwitchGround::mNumber = ESWITCH_GROUND1;
			mCollision = true;
			return true;
		}
	}
	mCollision = false;
	return false;
}