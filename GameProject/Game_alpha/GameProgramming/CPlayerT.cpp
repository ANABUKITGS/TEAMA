#include "CPlayerT.h"



void CPlayerT::Update(){

	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;

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
//	if (mPosition.y > 0)
		Gravity();
//	else
//		mVelocityG = 0;
	Forward();
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
		if (mVelocityX < hoge && mVelocityX > -hoge){
			mVelocityX += 0.5f;
		}
	}
	else if (CGamePad::Push(PAD_LSTICKX, -0.1f) || CKey::Push('A')){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
		if (mVelocityX < hoge && mVelocityX > -hoge)
			mVelocityX -= 0.5f;
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += 0.25f;
		else if (mVelocityX>0)
			mVelocityX -= 0.25f;
	}
	mPosition.x += mVelocityX;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (CRectangle::Collision(p, &mPosition)) {
		mVelocityG = 0.0f;
		return true;
	}
	return false;
}