#include "CCharcter.h"
#include "CGame2.h"

extern CGame mGame;

#define PLAYER_VELOCITY_X 5.0f
#define PLAYER_VELOCITY_Y 5.0f
#define JUMP_TIME_LIMIT 15
#define VELOCITYX_LIMIT 5.0f
#define VELOCITYY_LIMIT -30.0f

//wchar_t jumptime_buf[256];

void CCharcter::Update(){
	CRectangle::Update();

	Forward();
	Scroll();

	//swprintf(jumptime_buf, L"mVelocityX\n%4.2f\nmVelocityY\n%4.2f\nmPosition.x\n%4.2f\nmPosition.y\n%4.2f", mVelocityX, mVelocityY, mPosition.x, mPosition.y);
}

void CCharcter::Render(){
	CRectangle::Render(WHITE, 1.0f);
	//CText::DrawStringW(jumptime_buf, 0, 0, 32, 1.0f, 0);
}

//�d�͏���
void CCharcter::Gravity(){
	//���x������
	mVelocityY -= 16.33/15;
	if (VELOCITYY_LIMIT > mVelocityY) {
		mVelocityY = VELOCITYY_LIMIT;
	}
	//���x���ړ�
	mPosition.y += mVelocityY;
}


//�O�i����
void CCharcter::Forward(){
	if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CKey::Push('D')){
		float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
		if (mVelocityX < hoge && mVelocityX > -hoge){
			mVelocityX += 0.5f;
			mGame.mapsctoll_flag = true;
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

void CCharcter::Scroll(){
	if (mGame.mapsctoll_flag){
		//�X�N���[��
		mPosition.x -= 2;
	}
	//��ʐ���
	if (mPosition.x >= 608.0f)
		mPosition.x = 608.0f;

	if (mPosition.x <= -672.0f)
		mPosition.x = -672.0f;
}