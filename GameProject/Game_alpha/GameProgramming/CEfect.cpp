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
	//‘¬“x‚ð‰Á‘¬
	mVelocityY -= 16.33 / 15;
	if (- 10 > mVelocityY) {
		mVelocityY = -10;
	}
	//‘¬“x•ªˆÚ“®
	mPosition.y += mVelocityY;
}
void CDamageEfect::Render(){
	CRectangle::Render();
}

void CBossEfect::Update(){
	ani_count--;
	if (ani_count < 0){
		if (ani_num != 9)
			ani_num++;
		else
			ani_num = 0;
		ani_count = 5;
	}
	mPosition = mpRect->mPosition;
	CRectangle::Update();
}

void CBossEfect::Render(){
	mTexture.DrawImage(BOSSEFECT_UV, 1.0f);
}