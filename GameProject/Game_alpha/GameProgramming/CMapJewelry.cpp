#include "CMapJewelry.h"
#include "CSE.h"
#include "CWeapon.h"
#include "CEfect.h"

CSDiamond *CSDiamond::mpSDiamond = NULL;
bool CSDiamond::mGetFlg = false;

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

void CSDiamond::Update(){
	CRectangle::Update();
	mIntervalEfe--;
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
	}
	else if (mIntervalEfe<0){
		mIntervalEfe = EFECT_INTERVAL;
		new CEfect(mPosition);
	}

	if (mPosition.y <= 144.0f){
		mVelocityY = 0.0f;
		mPosition.y = 144.0f;
	}
	else{
		if (mpWeapon == NULL)
			Gravity();
	}
}

bool CSDiamond::Collision(CRectangle *r){
	// 当たっているか
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		//プレイヤーまたは武器に衝突
		switch (r->mTag) {
		case ECELLNUM::EPLAYER:
			//無効にする
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			mGetFlg = true;
			return true;
			break;

		case ECELLNUM::EPWEAPON:
			mpWeapon = r;
			break;

		default:
			break;
		}
	}
	return false;
}

void CSDiamond::Render(){
	mTexSDiamond.DrawImage(SDIAMOND_UV, 1.0f);
}

void CSDiamond::Gravity(){
	//速度を加速
	mVelocityY -= 16.33 / 15;
	//速度分移動
	mPosition.y += mVelocityY;
}