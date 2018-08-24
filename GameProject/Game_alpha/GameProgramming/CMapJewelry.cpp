#include "CMapJewelry.h"
#include "CSE.h"
#include "CWeapon.h"
#include "CEfect.h"



void CMapJewelry::Update() {
	mIntervalEfe--;
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
	}
	else if (mIntervalEfe<0){
		mIntervalEfe = EFECT_INTERVAL;
		new CEfect(mPosition);
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
	mIntervalEfe--;
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
	}
	 else if (mIntervalEfe<0){
		mIntervalEfe = EFECT_INTERVAL;
		new CEfect(mPosition);
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