#include "CMapSwitchGround.h"

int CMapSwitchGround::mNumber;

void CMapSwitchGround::Update() {
	CMapChip::Update();
}


//bool CMapSwitchGround::Collision(CRectangle *r) {
//	// �������Ă��邩
//	if (CRectangle::Collision(r)) {
//		//�v���C���[�܂��͕���ɏՓ�
//		if (r->mTag == EPLAYER || r->mTag == EPWEAPON) {
//			//�����ɂ���
//			mEnabled = false;
//			return true;
//		}
//	}
//	return false;
//}


void CMapSwitch::Update() {
	CMapChip::Update();
}

bool CMapSwitch::Collision(CRectangle *r) {
	// �������Ă��邩
	if (CRectangle::Collision(r)) {
		//����ɏՓ�
		if (r->mTag == EPWEAPON && !mCollision) {
			if (CMapSwitchGround::mNumber == 0)
				CMapSwitchGround::mNumber = 1;
			else
				CMapSwitchGround::mNumber = 0;
			return true;
			mCollision = true;
		}
	}
	mCollision = false;
	return false;
}