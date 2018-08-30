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
	//mLife--;
	mPosition.x += mVelocityX;
	Gravity();
	//if (mLife < 0)
	if (mPosition.y <= -10.0f)
		mEnabled = false;
	CRectangle::Update();
	
}

void CDamageEfect::Gravity(){
	//速度を加速
	mVelocityY -= 16.33 / 15;
	if (- 10 > mVelocityY) {
		mVelocityY = -10;
	}
	//速度分移動
	mPosition.y += mVelocityY;
}
void CDamageEfect::Render(){
	CRectangle::Render();
}