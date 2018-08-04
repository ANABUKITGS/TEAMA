#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 3.0f

CPlayerT *CPlayerT::mpPlayer = 0;

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

//�d�͏���
void CPlayerT::Gravity(){
	//���x���ړ�
	mPosition.y -= mVelocityG;
	//���x������
	mVelocityG += 16.33 / 60;
}

//�W�����v����
void CPlayerT::Jump(){
	//���x���ړ�
	mPosition.y += mVelocityJ;
	//���x������
	mVelocityJ -= 16.33 / 60;
}

void CPlayerT::Forward(){
	if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CKey::Push('D')){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
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
			if (p->mTag != EJEWELRY) {
				mPosition = mPosition + aj;
			}
			mVelocityG = 0.0f;
			return true;
		}
	}
	return false;
}