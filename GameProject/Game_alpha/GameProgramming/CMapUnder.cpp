#include "CMapUnder.h"
#include "CPlayerT.h"

void CMapUnder::Update(){
	//�e�̍X�V�������Ă�
	CMapChip::Update();
}

bool CMapUnder::Collision(CRectangle*r){
	// �������Ă��邩
	if (CRectangle::Collision(r)) {
		//�v���C���[�ɏՓ�
		if (r->mTag == EPLAYER) {
			//�v���C���[���W�����v���̎��͔��肵�Ȃ�
			if ((-r->mScale.y/2)>mScale.y){
				return true;
			}
			return true;
		}
	}
	return false;
}