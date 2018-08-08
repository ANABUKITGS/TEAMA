#include "CMapBox.h"


void CMapBox::Update() {
	if (mBreak)
	Gravity();
	if (mPosition.y < -100)
	mEnabled = false;
	CMapChip::Update();
}

/*
�v���C���[�ɓ��������疳���ɂ���
*/
bool CMapBox::Collision(CRectangle *r) {
	//�v���C���[�܂��͕���ɏՓ�
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		if (r->mTag == EPLAYER || r->mTag == EENEMY1) {
			mPosition = mPosition + aj;
			return true;
		}
		if (r->mTag == EPWEAPON) {
			mBreak = true;
			return true;
		}
	}
	return false;
}

void CMapBox::Gravity(){
	//���x������
	mVelocityY -= 16.33 / 15;
	//���x���ړ�
	mPosition.y += mVelocityY;
}