#include "CMapSwitchGround.h"

ECELLNUM CMapSwitchGround::mNumber;

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
		if (r->mTag == EPLAYER && !mCollision) {
			if (CMapSwitchGround::mNumber == ESWITCH_GROUND1)
				CMapSwitchGround::mNumber = ESWITCH_GROUND2;
			else
				CMapSwitchGround::mNumber = ESWITCH_GROUND1;
			mCollision = true;
			return true;
		}
	}
	mCollision = false;
	return false;
}