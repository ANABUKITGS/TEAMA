#include "CMapJewelry.h"

/*
�Ƃ肠������
*/
void CMapJewelry::Update() {
	mRotation += 1;
	CMapChip::Update();
}

/*
�v���C���[�ɓ��������疳���ɂ���
*/
bool CMapJewelry::Collision(CRectangle *r) {
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