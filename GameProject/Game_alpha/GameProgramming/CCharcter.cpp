#include "CCharcter.h"
#include "CGame2.h"

extern CGame mGame;

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
	Scroll();

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

	swprintf(jumptime_buf, L"mVelocityX\n%4.2f\nmVelocityG\n%4.2f\nmVelocityJ\n%4.2f\nmPosition.x\n%4.2f\nmPosition.y\n%4.2f", mVelocityX, mVelocityG, mVelocityJ, mPosition.x, mPosition.y);
}

void CCharcter::Render(){
	CRectangle::Render(WHITE, 1.0f);
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
	if (CGamePad::Push(PAD_LSTICKX, 0.1f)){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
		if (mVelocityX < hoge && mVelocityX > -hoge){
			mVelocityX += 0.5f;
			mGame.mapsctoll_flag = true;
		}
	}
	else if (CGamePad::Push(PAD_LSTICKX, -0.1f)){
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

void CCharcter::Scroll(){
	if (mGame.mapsctoll_flag){
		//スクロール
		mPosition.x -= SCROLL_SPEED;
	}
	//画面制限
	if (mPosition.x >= 608.0f)
		mPosition.x = 608.0f;

	if (mPosition.x <= -672.0f)
		mPosition.x = -672.0f;
}