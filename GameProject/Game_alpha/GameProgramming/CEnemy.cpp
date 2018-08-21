#include "CEnemy.h"
#include "CScene.h"

/*
�G�̍��G�͈�
*/
//bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
//	CVector2 Search = player->mPosition - enemy->mPosition;
//	if (Search.Length() < player->mSearch + enemy->mSearch){
//		return true;
//	}
//	return false;
//}


void  CEnemy::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		mAttackInterval--;
		//�G�̕����A�ҋ@�A�j���[�V�������s������
		switch (mAnimationTag){
		case EWALK:
			mWalkTime--;
			if (mpSearch->mDiscovery)
				mAnimationTag = EATTACK;

			if (mDirection){
				mPosition.x += mVelocity;
				mpSearch->mPosition = CVector2(mPosition.x + 100, mPosition.y);
			}
			else{
				mPosition.x -= mVelocity;
				mpSearch->mPosition = CVector2(mPosition.x - 100, mPosition.y);
			}
			if (mWalkTime < 0)
				mAnimationTag = EIDOL;
			break;

		case EIDOL:
			mMonitorTime--;
			if (mpSearch->mDiscovery)
				mAnimationTag = EATTACK;

			if (mMonitorTime < 0){
				mMonitorTime = MONITOR_TIME;
				mAnimationTag = EWALK;
				mWalkTime = WALK_TIME;
				if (mDirection)
					mDirection = false;
				else
					mDirection = true;
			}
			break;

		case EATTACK:
			//�G�����[���[�𔭎˂��Ă��Ȃ���΁A���[���[�𔭎˂��ď������s��
			if (!mpEWeapon){
				if (mAttackInterval < 0){
					mAttackInterval = ATTACK_INTERVAL;
					//�G�̃��[���[��G�̈ʒu���������O�ɌĂяo��
					mpEWeapon = new CWeapon(EEWEAPON, mPosition, mDirection);

					if (mDirection)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
						mpEWeapon->mPosition.x += 10;

					else				//�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
						mpEWeapon->mPosition.x -= 10;
				}
			}
			//�G�̃��[���[�����˂��ꂽ���̏������s��
			else {
				if (mpEWeapon->mLife < 0){
					mpEWeapon = 0;
					mAnimationTag = EWALK;
				}

			}
			//���[���[�̏����I��
			break;

		case EDOWN:
			mDownTime--;
			if (mDownTime % 10 == 0)
				mRender = false;
			else
				mRender = true;

			if (mDownTime < 0){
				mEnabled = false;
				mpSearch = false;
			}
			mAlpha -= 0.01f;
			break;

		default:
			break;
		}
		Gravity();
	}
	CRectangle::Update();
}
bool CEnemy::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EPWEAPON:
				mAnimationTag = EDOWN;
				mVelocityY = 0.0f;
				break;

			case EENEMY1:
			case EENEMY2:
			case EENEMY3:
				mVelocityY = 0.0f;
				mPosition.x = mPosition.x + aj.x;
				break;

			case ESWITCH_GROUND1:
			case ESWITCH_GROUND2:
			case ENONE:
			case ECHIKUWA:
			case EJEWELRY:
			case EJEWELRY2:
			case EBELTL:
			case EBELTR:
			case ESIGN:
			case ECHECKPOINT:
			case ESEARCH:
			case ESWITCH:
			case EUNDER:
			case EPLAYER:
			case EBOSS:
			case EEWEAPON:
				break;

			default:
				//�E��
				if (!(p->mColFlg & EDT_RIGHT)) {
					if (aj.x > 0) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				//����
				if (!(p->mColFlg & EDT_LEFT)) {
					if (aj.x < 0) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				//����
				if (!(p->mColFlg & EDT_BOTTOM)) {
					if (aj.y < 0) {
						mPosition.y = mPosition.y + aj.y;
						mVelocityY = 0.0f;
					}
				}
				//���
				if (!(p->mColFlg & EDT_TOP)) {
					if (aj.y > 0) {
						mPosition.y = mPosition.y + aj.y;
						mVelocityY = 0.0f;
					}
				}
				break;
			}
			return true;
		}
	}
	return false;
}

void CEnemy::Render(){
	switch (mAnimationTag){
	case EATTACK:
		if (mpEWeapon != NULL){
			if (mDirection)
				//���[���[�̕R
				mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_R, 1.0f);

			else
				//���[���[�̕R
				mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_L, 1.0f);
		}
		break;

	default:
		break;
	}
	CRectangle::Render();
}

void CSearch::Update(){
	CRectangle::Update();
}

bool CSearch::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (p->mTag == EPLAYER) {
			if (CRectangle::Collision(p)){
				mDiscovery = true;
			}
			else{
				mDiscovery = false;
			}
			return true;
		}
	}
	return false;
}

void CSearch::Render(){
	if (mRender){
		CRectangle::Render(WHITE, 0.0f);
	}
}