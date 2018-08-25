#include "CMapBox.h"
#include "CScene.h"
#include "CPlayerT.h"

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
	//�_�|���S���͔��肵�Ȃ�
	if (r->mScale.x > 0.0f && r->mScale.y > 0.0f){
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
					//���E
					if (mPosition.x - mScale.x > r->mPosition.x || mPosition.x + mScale.x < r->mPosition.x) {
						//��
						if (mPosition.x - mScale.x > r->mPosition.x) {
							r->mPosition.x = r->mPosition.x - aj.x;
						}
						//�E
						if (mPosition.x + mScale.x < r->mPosition.x) {
							r->mPosition.x = r->mPosition.x - aj.x;
						}
					}
					//�㉺
					else {
						//��
						if (mPosition.y - mScale.y > r->mPosition.y) {
							r->mPosition.y = r->mPosition.y - aj.y;
							r->mVelocityY = 0.0f;
						}
						//��
						if (mPosition.y + mScale.y < r->mPosition.y) {
							r->mPosition.y = r->mPosition.y - aj.y;
							r->mVelocityY = 0.0f;
							if (r->mTag == ECELLNUM::EPLAYER)
								CPlayerT::mpPlayer->mJumpCount = 0;
						}
					}
				}
				//���g�������Ԃ������蔻��
				else{
					if (r->mTag != EPWEAPON &&
						r->mTag != EEWEAPON){
						mVelocityY = 0.0f;
						mPosition = mPosition + aj;
					}
				}
			}

			//�v���C���[�̃��[���[
			if (r->mTag == EPWEAPON)
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