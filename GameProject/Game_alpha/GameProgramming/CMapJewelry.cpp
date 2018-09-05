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
		//new CEfect(mPosition);
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
	if (mpWeapon == NULL && mPosition.y > 160.0f)
		Gravity();
	else
		mPosition.y = 160.0f;
}

bool CSDiamond::Collision(CRectangle *r){
	// �������Ă��邩
	CVector2 aj;
	if (CRectangle::Collision(r, &aj) && r->GetEnabled()) {
		//�v���C���[�܂��͕���ɏՓ�
		switch (r->mTag) {
		case ECELLNUM::EPLAYER:
			//�����ɂ���
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
	//���x������
	mVelocityY -= 16.33 / 15;
	//���x���ړ�
	mPosition.y += mVelocityY;
}