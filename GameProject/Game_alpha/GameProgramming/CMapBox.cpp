#include "CMapBox.h"


void CMapBox::Update() {
	if (mBreak)
	Gravity();
	if (mPosition.y < -100)
	mEnabled = false;
	CMapChip::Update();
}

/*
プレイヤーに当たったら無効にする
*/
bool CMapBox::Collision(CRectangle *r) {
	//プレイヤーまたは武器に衝突
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		if (r->mTag == EPLAYER || r->mTag == EENEMY1) {
			mPosition = mPosition + aj;
			return true;
		}
		if (r->mTag == EPWEAPON) {
			mBreak = true;
			return true;
		}
	}
	return false;
}

void CMapBox::Gravity(){
	//速度を加速
	mVelocityY -= 16.33 / 15;
	//速度分移動
	mPosition.y += mVelocityY;
}