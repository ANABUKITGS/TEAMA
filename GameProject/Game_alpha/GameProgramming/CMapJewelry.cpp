#include "CJewelry.h"

/*
�Ƃ肠������
*/
void CJewelry::Update() {
	mRotation += 1;
	CMapChip::Update();
}

/*
�v���C���[�ɓ��������疳���ɂ���
*/
bool CJewelry::Collision(CRectangle *r) {
	// �������Ă��邩
	if (CRectangle::Collision(r)) {
		//�v���C���[�ɏՓ�
		if (r->mTag == EPLAYER) {
			//�����ɂ���
			mEnabled = false;
			return true;
		}
	}
	return false;
}