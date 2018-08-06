#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 3.0f
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;

void CPlayerT::Update(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;

	
	if (mWeapon == 0){
		if (CGamePad::Push(PAD_1)){
			mWeapon = new CWeapon(mPosition, CVector2(10, 10),mDirection, NULL);
			if (mDirection)
				mWeapon->mPosition.x += 10;
			else
				mWeapon->mPosition.x -= 10;
		}
		if (CGamePad::Push(PAD_2) || CKey::Push(VK_SPACE)){
			if (mJumpTime < JUMP_TIME_LIMIT){
				mJumpTime++;
				Jump();
			}
		}
		else{
			mJumpTime = 0;
			mVelocityJ = PLAYER_VELOCITY_Y;

		}
		
	}
	else if (mWeapon->mLife < 0){
		mWeapon = 0;
	}
	else{
		mWeapon->Render();
	}
	if (mWeapon == 0){
		Gravity();
		Forward();
	}
	CRectangle::Update();
	
}

//重力処理
void CPlayerT::Gravity(){
	//速度分移動
	mPosition.y -= mVelocityG;
	//速度を加速
	mVelocityG += 16.33 / 60;
}

//ジャンプ処理
void CPlayerT::Jump(){
	//速度分移動
	mPosition.y += mVelocityJ;
	//速度を加速
	mVelocityJ -= 16.33 / 60;
}

void CPlayerT::Forward(){
	if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CKey::Push('D')){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
		mDirection= true;
		if (mVelocityX < hoge && mVelocityX > -hoge){
			mVelocityX += PLAYER_VELOCITY_X;
		}
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += (PLAYER_VELOCITY_X / 2);
		else if (mVelocityX>0)
			mVelocityX -= (PLAYER_VELOCITY_X / 2);
	}
	if (CGamePad::Push(PAD_LSTICKX, -0.1f) || CKey::Push('A')){
		mDirection = false;
		float hoge = mVelocityLimit * -CGamePad::GetStick(PAD_LSTICKX);
		if (mVelocityX < hoge && mVelocityX > -hoge)
			mVelocityX -= PLAYER_VELOCITY_X;
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += ( PLAYER_VELOCITY_X / 2);
		else if (mVelocityX>0)
			mVelocityX -= ( PLAYER_VELOCITY_X / 2);
	}
	mPosition.x += mVelocityX;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			if (p->mTag != EJEWELRY ) {
				mPosition = mPosition + aj;
			}
			mVelocityG = 0.0f;
			return true;
		}
	}
	return false;
}

