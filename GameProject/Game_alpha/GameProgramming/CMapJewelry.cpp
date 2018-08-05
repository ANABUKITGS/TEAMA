#include "CJewelry.h"

/*
とりあえず回す
*/
void CJewelry::Update() {
	mRotation += 1;
	CMapChip::Update();
}

/*
プレイヤーに当たったら無効にする
*/
bool CJewelry::Collision(CRectangle *r) {
	// 当たっているか
	if (CRectangle::Collision(r)) {
		//プレイヤーに衝突
		if (r->mTag == EPLAYER) {
			//無効にする
			mEnabled = false;
			return true;
		}
	}
	return false;
}