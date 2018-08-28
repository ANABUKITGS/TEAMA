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
�v���C���[�ɓ��������疳���ɂ���
*/
bool CMapJewelry::Collision(CRectangle *r) {
	// �������Ă��邩
	if (CRectangle::Collision(r)) {
		//�v���C���[�܂��͕���ɏՓ�
		if (r->mTag == EPLAYER) {
			//�����ɂ���
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
�v���C���[�ɓ��������疳���ɂ���
*/
bool CMapMiniJewelry::Collision(CRectangle *r) {
	// �������Ă��邩
	if (CRectangle::Collision(r)) {
		//�v���C���[�܂��͕���ɏՓ�
		if (r->mTag == EPLAYER) {
			//�����ɂ���
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
	// �������Ă��邩
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		//�v���C���[�܂��͕���ɏՓ�
		switch (r->mTag) {
		case ECELLNUM::EPLAYER:
			//�����ɂ���
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
	//���x������
	mVelocityY -= 16.33 / 15;
	//���x���ړ�
	mPosition.y += mVelocityY;
}