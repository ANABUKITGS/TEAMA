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