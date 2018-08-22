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
	if (mpWeapon != 0){
		mPosition = mpWeapon->mPosition;
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