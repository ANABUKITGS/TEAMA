#include "CMapBox.h"
#include "CScene.h"
#include "CEfect.h"
#include "CPlayerT.h"
#include "CBoss.h"

void CMapBox::Update() {
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		if (mBreak)
		Gravity();
		if (mPosition.y < -10000.0f){
			if (!mBossGimmick)
				mPosition = mDefaultPos;
			else
				mEnabled = false;
			mVelocityY = 0.0f;
			mBreak = false;
			mAlpha = 1.0f;
		}
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
			if (!mBreak && mAlpha >= 1.0f){
				//�����������l�������Ԃ������蔻��
				if (r->mTag == EPLAYER ||
					r->mTag == EENEMY1 ||
					r->mTag == EENEMY2 ||
					r->mTag == EENEMY3) {
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
							if (r->mTag == ECELLNUM::EPLAYER && (CBoss::mpBoss == NULL || (CBoss::mpBoss != NULL && CBoss::mpBoss->mBossLife > 0)))
								CPlayerT::mpPlayer->mJumpCount = 0;
						}
					}
				}
				//���g�������Ԃ������蔻��
				else{
					//if (r->mTag != EPWEAPON &&
					//	r->mTag != EEWEAPON &&
					//	r->mTag != EBOSS){
					//	mVelocityY = 0.0f;
					//	mPosition = mPosition + aj;
					//}
				}
				//�v���C���[�̃��[���[
				if (r->mTag == EPWEAPON)
					mBreak = true;
			}
			
			else if (mBreak && mAlpha >= 1.0f){
				if (r->mTag == EENEMY1 ||
					r->mTag == EENEMY2 ||
					r->mTag == EENEMY3){
					new CBoxEfect(mPosition);
					//mEnabled = false;
					mAlpha = 0.0f;
				}
				if (r->mTag == EBOSS && CBoss::mpBoss != NULL &&
					CBoss::mpBoss->mAttackBehavior != CBoss::AttackBehavior::EJUMP &&
					CBoss::mpBoss->mAttackBehavior != CBoss::AttackBehavior::EDOWN &&
					CBoss::mpBoss->mAlpha >= 1.0f){
					new CBoxEfect(mPosition);
					//mEnabled = false;
					mAlpha = 0.0f;
				}
				else if (r->mTag == EPLAYER && mPosition.y > CPlayerT::mpPlayer->mPosition.y + CPlayerT::mpPlayer->mScale.y){
					new CBoxEfect(mPosition);
					//mEnabled = false;
					mAlpha = 0.0f;
				}
			}
			return true;
		}
	}
	return false;
}

void CMapBox::Render(){
	mTexBox.DrawImage(BOX_UV, mAlpha);
}

void CMapBox::Gravity(){
	//���x������
	mVelocityY -= 16.33 / 15;
	//���x���ړ�
	mPosition.y += mVelocityY;
}