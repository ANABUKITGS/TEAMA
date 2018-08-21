#include "CMapJewelry.h"
#include "CSE.h"

/*
�Ƃ肠������
*/
void CMapJewelry::Update() {
	//mRotation += 1;
	//CMapChip::Update();
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
		if (r->mTag == EPLAYER || r->mTag ==EPWEAPON) {
			//�����ɂ���
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			return true;
		}
	}
	return false;
}

/*
�Ƃ肠������
*/
void CMapMiniJewelry::Update() {
	//mRotation += 1;
	//CMapChip::Update();
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
		if (r->mTag == EPLAYER || r->mTag == EPWEAPON) {
			//�����ɂ���
			mEnabled = false;
			CSE::mSoundJewelry.Play();
			return true;
		}
	}
	return false;
}