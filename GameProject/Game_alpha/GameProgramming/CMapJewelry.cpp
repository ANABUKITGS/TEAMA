#include "CMapJewelry.h"
#include "CSE.h"

/*
とりあえず回す
*/
void CMapJewelry::Update() {
	//mRotation += 1;
	//CMapChip::Update();
}

void CMapJewelry::Render(){
	mTexJewel.DrawImage(JEWELRY_UV, 1.0f);
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
			CSE::mSoundJewelry.Play();
			return true;
		}
	}
	return false;
}

/*
とりあえず回す
*/
void CMapMiniJewelry::Update() {
	//mRotation += 1;
	//CMapChip::Update();
}

void CMapMiniJewelry::Render(){
	mTexJewel.DrawImage(JEWELRY2_UV, 1.0f);
}

/*
プレイヤーに当たったら無効にする
*/
bool CMapMiniJewelry::Collision(CRectangle *r) {
	// 当たっているか
	if (CRectangle::Collision(r)) {
		//プレイヤーまたは武器に衝突
		if (r->mTag == EPLAYER || r->mTag == EPWEAPON) {
			//無効にする
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			return true;
		}
	}
	return false;
}