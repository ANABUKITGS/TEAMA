#include "CEnemy.h"

/*
敵の索敵範囲
*/
//bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
//	CVector2 Search = player->mPosition - enemy->mPosition;
//	if (Search.Length() < player->mSearch + enemy->mSearch){
//		return true;
//	}
//	return false;
//}


void  CEnemy::Update(){
	mAttackInterval--;
	//敵の歩く、待機アニメーションを行う処理
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
		//敵がヨーヨーを発射していなければ、ヨーヨーを発射して処理を行う
		if (!mpEWeapon){
			if (mAttackInterval < 0){
				mAttackInterval = ATTACK_INTERVAL;
				//敵のヨーヨーを敵の位置よりも少し前に呼び出す
				mpEWeapon = new CWeapon(EEWEAPON, mPosition, CVector2(10, 10), mDirection, NULL);

				if (mDirection)		//敵が右を向いている時には右にヨーヨーを進ませる
					mpEWeapon->mPosition.x += 10;

				else				//敵が左を向いている時には左にヨーヨーを進ませる
					mpEWeapon->mPosition.x -= 10;
			}
		}
		//敵のヨーヨーが発射された時の処理を行う
		else {
			if (mpEWeapon->mLife < 0){
				mpEWeapon = 0;
				mAnimationTag = EWALK;
			}

		}
		//ヨーヨーの処理終了
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
	CRectangle::Update();
}
bool CEnemy::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			if (p->mTag != ECELLNUM::EEWEAPON &&
				p->mTag != ECELLNUM::EPLAYER &&
				p->mTag != ECELLNUM::ESEARCH &&
				p->mTag != ECELLNUM::EBELTL &&
				p->mTag != ECELLNUM::EBELTR &&
				p->mTag != ECELLNUM::ECHIKUWA){
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