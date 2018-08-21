#include "CMapBox.h"
#include "CScene.h"

void CMapBox::Update() {
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		if (mBreak)
		Gravity();
		if (mPosition.y < -100)
			mEnabled = false;
	}
	CMapChip::Update();
}

/*
�v���C���[�ɓ��������疳���ɂ���
*/
bool CMapBox::Collision(CRectangle *r) {
	//�v���C���[�܂��͕���ɏՓ�
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		//�ݒu���
		if (!mBreak){
			//�����������l�������Ԃ������蔻��
			if (r->mTag == EPLAYER ||
				r->mTag == EENEMY1 ||
				r->mTag == EENEMY2 ||
				r->mTag == EENEMY3 ||
				r->mTag == EBOSS) {
				r->mPosition = r->mPosition - aj;
				return true;
			}
			//���g�������Ԃ������蔻��
			else{
				if (r->mTag != EPWEAPON &&
					r->mTag != EEWEAPON){
					mVelocityY = 0.0f;
					mPosition = mPosition + aj;
					return true;
				}
			}
		}
		//�������
		else if (mBreak &&
			r->mTag == EPLAYER ||
			r->mTag == EENEMY1 ||
			r->mTag == EENEMY2 ||
			r->mTag == EENEMY3 ||
			r->mTag == EBOSS) {

			return true;
		}

		//�v���C���[�̃��[���[
		if (r->mTag == EPWEAPON) {
			mBreak = true;
			return true;
		}
	}
	return false;
}

void CMapBox::Render(){
	mTexBox.DrawImage(BOX_UV, 1.0f);
}

void CMapBox::Gravity(){
	//���x������
	mVelocityY -= 16.33 / 15;
	//���x���ړ�
	mPosition.y += mVelocityY;
}