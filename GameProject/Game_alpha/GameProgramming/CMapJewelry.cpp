#include "CMapJewelry.h"
#include "CSE.h"
#include "CWeapon.h"



void CMapJewelry::Update() {
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
	}
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
		if (r->mTag == EPLAYER) {
			//無効にする
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			return true;
		}
		if (r->mTag == EPWEAPON){
			mpWeapon = r;
		}
	}
	return false;
}

void CMapMiniJewelry::Update() {
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
	}
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
		if (r->mTag == EPLAYER) {
			//無効にする
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			return true;
		}
		if (r->mTag == EPWEAPON){
			mpWeapon = r;
		}
	}
	return false;
}