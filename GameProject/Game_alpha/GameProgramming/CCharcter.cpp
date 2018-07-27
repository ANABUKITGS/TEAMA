#include "CCharcter.h"
#include "CGamePad.h"
#include "CText.h"

#define PLAYER_VELOCITY_X 5.0f
#define PLAYER_VELOCITY_Y 15.0f
#define JUMP_TIME_LIMIT 15
#define VELOCITYX_LIMIT 5.0f

wchar_t jumptime_buf[256];

void CCharcter::Init(){
	SetVertex(-32.0f, 32.0f, -64.0f, 64.0f);
	mVelocityG = 0;
	mJumpTime = 0;
	mVelocityX = 0;
	mVelocityJ = PLAYER_VELOCITY_Y;
}
void CCharcter::Update(){
	CRectangle::Update();
	if (CGamePad::Push(PAD_3))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;

	if (CGamePad::Push(PAD_2)){
		if (mJumpTime < JUMP_TIME_LIMIT){
			mJumpTime++;
			Jump();
		}
	}
	else{
		mJumpTime = 0;
		mVelocityJ = PLAYER_VELOCITY_Y;
		
	}
	if (mPosition.y > 0)
		Gravity();
	else
		mVelocityG = 0;
	Forward();
	Render();

	swprintf(jumptime_buf, L"mVelocityX\n%4.2f\nmVelocityG\n%4.2f\nmVelocityJ\n%4.2f", mVelocityX, mVelocityG, mVelocityJ);
	CText::DrawStringW(jumptime_buf, 0, 0, 32, 1.0f, 0);
}
//重力処理
void CCharcter::Gravity(){
	//速度分移動
	mPosition.y -= mVelocityG;
	//速度を加速
	mVelocityG += 16.33/60;
}

//ジャンプ処理
void CCharcter::Jump(){
	//速度分移動
	mPosition.y += mVelocityJ;
	//速度を加速
	mVelocityJ -= 16.33 / 60;
}

void CCharcter::Forward(){
	if (CGamePad::Push(PAD_LSTICKX, 0.5f) && mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
		mVelocityX += 0.5f;
	else if (CGamePad::Push(PAD_LSTICKX, -0.5f) && mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
		mVelocityX -= 0.5f;
	else{
		if (mVelocityX < 0)
			mVelocityX += 0.25f;
		else if (mVelocityX>0)
			mVelocityX -= 0.25f;
	}
	mPosition.x += mVelocityX;
}