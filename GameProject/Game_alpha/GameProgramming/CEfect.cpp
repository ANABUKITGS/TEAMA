#include "CEfect.h"

void CEfect::Update(){
	mAlpha-=0.025;
	if (mAlpha < 0)
		mEnabled = false;
	CRectangle::Update();
}
void CEfect::Render(){
	mTexkira.DrawImage(EFECT_UV,mAlpha);
}

void CDamageEfect::Update(){
	
	mRotation+=mRotationAdd;
	mLife--;
	mPosition.x += mVelocityX;
	Gravity();
	if (mLife < 0)
		mEnabled = false;
	CRectangle::Update();
	
}

void CDamageEfect::Gravity(){
	//���x������
	mVelocityY -= 16.33 / 15;
	if (- 10 > mVelocityY) {
		mVelocityY = -10;
	}
	//���x���ړ�
	mPosition.y += mVelocityY;
}
void CDamageEfect::Render(){
	CRectangle::Render();
}