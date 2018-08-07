#include "CMapJewelry.h"

/*
とりあえず回す
*/
void CMapJewelry::Update() {
	mRotation += 1;
	CMapChip::Update();
}

/*
プレイヤーに当たったら無効にする
*/
bool CMapJewelry::Collision(CRectangle *r) {
	// 当たっているか
	if (CRectangle::Collision(r)) {
		//プレイヤーまたは武器に衝突
		if (r->mTag == EPLAYER || r->mTag ==EPWEAPON) {
			//無効にする
			mEnabled = false;
			return true;
		}
	}
	return false;
}