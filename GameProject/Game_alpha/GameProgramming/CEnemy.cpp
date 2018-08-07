#include "CEnemy.h"

/*
敵の索敵範囲
*/
bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
	CVector2 Search = player->mPosition - enemy->mPosition;
	if (Search.Length() < player->mSearch + enemy->mSearch){
		return true;
	}
	return false;
}


void  CEnemy::Update(){
	//プレイヤーが一定の距離まで近づい;てきたら攻撃を開始する
	if (SearchCollision(CPlayerT::mpPlayer,this)){

		//敵がヨーヨーを発射していなければ、ヨーヨーを発射して処理を行う
		if (!mpEWeapon){
			//敵のヨーヨーを敵の位置よりも少し前に呼び出す
			mpEWeapon = new CWeapon(EEWEAPON,mPosition, CVector2(10, 10), mForward, NULL);

			if (mForward)		//敵が右を向いている時には右にヨーヨーを進ませる
				mpEWeapon->mPosition.x += 10;

			else			  //敵が左を向いている時には左にヨーヨーを進ませる
				mpEWeapon->mPosition.x -= 10;
		}
		//敵のヨーヨーが発射された時の処理を行う
		else {
			if (mpEWeapon->mLife < 0)
				mpEWeapon = 0;
		}
	}
	//ヨーヨーの処理終了

	//敵の歩く、待機アニメーションを行う処理
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