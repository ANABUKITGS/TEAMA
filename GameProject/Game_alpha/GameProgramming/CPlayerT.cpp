#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 2.5f
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;
wchar_t jumptime_buf[256];

void CPlayerT::Update(){
	if (mWeapon == 0){
		if (CGamePad::Push(PAD_1) || CKey::Push(VK_UP) && mAttack){
			mWeapon = new CWeapon(mPosition, CVector2(10, 10), mDirection, NULL);
			if (mDirection)		//weaponの位置をプレイヤーの向いている方向へ10ずらす
				mWeapon->mPosition.x += 10;
			else
				mWeapon->mPosition.x -= 10;
		}

		if (mJumpCount < 2 && CGamePad::Push(PAD_2) || CKey::Push(VK_RIGHT) ){
			if (!mJump)
				mVelocityY = PLAYER_VELOCITY_Y;
				mJump = true;
				
				/*Jump();*/
			
		}
		else if (mJump){
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
		Dash();
		Gravity();
		Forward();
	}
	CRectangle::Update();
	swprintf(jumptime_buf, L"mVelocityX\n%4.2f\nmVelocityY\n%4.2f\nmPosition.x\n%4.2f\nmPosition.y\n%4.2f", mVelocityX, mVelocityY, mPosition.x, mPosition.y);
	CText::DrawStringW(jumptime_buf, 0, 0, 32, 1.0f, 0);
	
}

void CPlayerT::Forward(){
	if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CKey::Push('D')){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
		mDirection= true;
		if (mVelocityX < hoge && mVelocityX > -hoge){
			mVelocityX += PLAYER_VELOCITY_X;
		}
	}
	else if (CGamePad::Push(PAD_LSTICKX, -0.1f) || CKey::Push('A')){
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
			if (p->mTag != EJEWELRY && p->mTag != EWEAPON) {
				mPosition = mPosition + aj;
			}
			mJumpCount = 0;
			mVelocityY = 0.0f;
			return true;
		}
	}
	return false;
}

void CPlayerT::Dash(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;
}
