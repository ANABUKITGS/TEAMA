#include "CMapSwitchGround.h"

int CMapSwitchGround::mNumber;

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
		if (r->mTag == EPWEAPON && !mCollision) {
			if (CMapSwitchGround::mNumber == 0)
				CMapSwitchGround::mNumber = 1;
			else
				CMapSwitchGround::mNumber = 0;
			return true;
			mCollision = true;
		}
	}
	mCollision = false;
	return false;
}