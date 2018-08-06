#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 3.0f
#define ATTACK_TIME 30

#define GRAVITY (16.33 / 60)

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
		if (mJumpCount<2 && CGamePad::Push(PAD_2) || CKey::Push(VK_SPACE) ){
			if (mJumpTime < JUMP_TIME_LIMIT){
				mJump = true;
				mJumpTime++;
				Jump();
			}
		}
		else if (mJump){
			mJumpTime = 0;
			mVelocityJ = PLAYER_VELOCITY_Y;
			mJumpCount++;
			mJump = false;
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
		else if (mVelocityX > 0)
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
		else if (mVelocityX > 0)
			mVelocityX -= ( PLAYER_VELOCITY_X / 2);
	}
	mPosition.x += mVelocityX;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		switch (p->mTag) {
		case EJEWELRY:
			if (CRectangle::Collision(p)) {

				return true;
			}
			break;

		default:
			if (CRectangle::Collision(p, &aj)) {
				if (abs(aj.y) > abs(aj.x)) {
					mVelocityG = 0.0f;
					mPosition.y = mPosition.y + aj.y;
				}
				else {
					mPosition.x = mPosition.x + aj.x;
				}
				CRectangle::Update();
				return true;
			}
			break;
		}
	}
	return false;
}

