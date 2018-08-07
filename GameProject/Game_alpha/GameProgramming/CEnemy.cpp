#include "CEnemy.h"

/*
�G�̍��G�͈�
*/
bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
	CVector2 Search = player->mPosition - enemy->mPosition;
	if (Search.Length() < player->mSearch + enemy->mSearch){
		return true;
	}
	return false;
}


void  CEnemy::Update(){
	//�v���C���[�����̋����܂ŋ߂Â�;�Ă�����U�����J�n����
	if (SearchCollision(CPlayerT::mpPlayer,this)){

		//�G�����[���[�𔭎˂��Ă��Ȃ���΁A���[���[�𔭎˂��ď������s��
		if (!mpEWeapon){
			//�G�̃��[���[��G�̈ʒu���������O�ɌĂяo��
			mpEWeapon = new CWeapon(EEWEAPON,mPosition, CVector2(10, 10), mForward, NULL);

			if (mForward)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
				mpEWeapon->mPosition.x += 10;

			else			  //�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
				mpEWeapon->mPosition.x -= 10;
		}
		//�G�̃��[���[�����˂��ꂽ���̏������s��
		else {
			if (mpEWeapon->mLife < 0)
				mpEWeapon = 0;
		}
	}
	//���[���[�̏����I��

	//�G�̕����A�ҋ@�A�j���[�V�������s������
	switch (mAnimationTag){
	case EWALK:
		mWalkTime--;
		if (mForward)
			mPosition.x += mVelocity;
		else
			mPosition.x -= mVelocity;
		if (mWalkTime < 0)
			mAnimationTag = EIDOL;
		break;
	case EIDOL:
		mMonitorTime--;
		if (mMonitorTime < 0){
			mMonitorTime = MONITOR_TIME;
			mAnimationTag = EWALK;
			mWalkTime = WALK_TIME;
			if (mForward)
				mForward = false;
			else
				mForward = true;
		}
		break;
	case EDOWN:
		mDownTime--;
		if (mDownTime < 0){
			mEnabled = false;
		}
		mAlpha -= 0.01f;
		break;
	default:
		break;
	}
	Gravity();
	CRectangle::Update();
}
bool CEnemy::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			if (p->mTag != EEWEAPON&&p->mTag!=EPLAYER) {
				mPosition = mPosition + aj;
			}
			if (p->mTag == EPWEAPON)
				mAnimationTag = EDOWN;
			mVelocityY = 0.0f;
			return true;
		}
	}
	return false;
}

void CEnemy::Render(){
	CRectangle::Render();
}