#include "CEnemy.h"


#define MONITOR_TIME 180
#define WALK_TIME 180
#define ENEMY_VELOCITY 1.5f

void CEnemy::Init(){
	mForward = true;
	mAnimationTag = EWALK;
	SetVertex(-32.0,32.0f,-32.0f,32.0f);
	mVelocity = ENEMY_VELOCITY;
	mMonitorTime = MONITOR_TIME;
	mWalkTime = WALK_TIME;
}

void  CEnemy::Update(){
	switch (mAnimationTag){
	case EWALK:
		mWalkTime--;
		if (mForward)
			mPosition.x += mVelocity;
		else
			mPosition.x -= mVelocity;
		if (mWalkTime < 0)
			mAnimationTag = EMONITOR;
		break;
	case EMONITOR:
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
	default:
		break;
	}
	CRectangle::Update();
	CRectangle::Render();
}