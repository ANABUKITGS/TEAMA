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
		//new CEfect(mPosition);
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
	if (mpWeapon == NULL && mPosition.y > 160.0f)
		Gravity();
	else
		mPosition.y = 160.0f;
}

bool CSDiamond::Collision(CRectangle *r){
	// 当たっているか
	CVector2 aj;
	if (CRectangle::Collision(r, &aj) && r->GetEnabled()) {
		//プレイヤーまたは武器に衝突
		switch (r->mTag) {
		case ECELLNUM::EPLAYER:
			//無効にする
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			mGetFlg = true;
			break;

		case ECELLNUM::EPWEAPON:
			mpWeapon = r;
			break;

		//case ECELLNUM::ENONE:
		//case ECELLNUM::ESIGN:
		//case ECELLNUM::EEWEAPON:
		//case ECELLNUM::ESEARCH:
		//case ECELLNUM::ESWITCH:
		//case ECELLNUM::EBOX:
		//case ECELLNUM::ESTEEL:
		//	
		//case ECELLNUM::EENEMY1:
		//case ECELLNUM::EENEMY2:
		//case ECELLNUM::EENEMY3:
		//case ECELLNUM::EBOSS:
		//case ECELLNUM::EJEWELRY:
		//case ECELLNUM::EJEWELRY2:
		//case ECELLNUM::ESDIAMOND:
		//	break;

		default:
		//	mPosition.y = mPosition.y + aj.y;
		//	mVelocityY = 0.0f;
			return false;
			break;
			return true;
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