#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 3.0f
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;

int CPlayerT::player_ani;

void CPlayerT::Update(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL) || CKey::Push(VK_SHIFT))
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
	if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CGamePad::Push(PAD_LSTICKX, -0.1f)){
		if (CGamePad::Push(PAD_LSTICKX, 0.1f)){
			float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
			mDirection = true;
			if (mVelocityX < hoge && mVelocityX > -hoge){
				mVelocityX += PLAYER_VELOCITY_X;
			}
			player_ani = ERUN;
		}
		else {
			if (mVelocityX < 0)
				mVelocityX += (PLAYER_VELOCITY_X / 2);
			else if (mVelocityX>0)
				mVelocityX -= (PLAYER_VELOCITY_X / 2);
		}

		if (CGamePad::Push(PAD_LSTICKX, -0.1f)){
			float hoge = mVelocityLimit * -CGamePad::GetStick(PAD_LSTICKX);
			mDirection = false;
			if (mVelocityX < hoge && mVelocityX > -hoge){
				mVelocityX -= PLAYER_VELOCITY_X;
			}
			player_ani = ERUN;
		}
		else {
			if (mVelocityX < 0)
				mVelocityX += (PLAYER_VELOCITY_X / 2);
			else if (mVelocityX>0)
				mVelocityX -= (PLAYER_VELOCITY_X / 2);
		}
	}
	else if (CKey::Push('D') || CKey::Push('A')){
		if (CKey::Push('D')){
			mDirection = true;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX += PLAYER_VELOCITY_X;
			//player_ani = ERUN;
		}
		else{
			if (mVelocityX < 0)
				mVelocityX += (PLAYER_VELOCITY_X / 2);
			else if (mVelocityX>0)
				mVelocityX -= (PLAYER_VELOCITY_X / 2);
		}

		if (CKey::Push('A')){
			mDirection = false;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX -= PLAYER_VELOCITY_X;
			//player_ani = ERUN;
		}
		else{
			if (mVelocityX < 0)
				mVelocityX += (PLAYER_VELOCITY_X / 2);
			else if (mVelocityX>0)
				mVelocityX -= (PLAYER_VELOCITY_X / 2);
		}
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += ( PLAYER_VELOCITY_X / 2);
		else if (mVelocityX>0)
			mVelocityX -= ( PLAYER_VELOCITY_X / 2);
			player_ani = EIDOL;
	}
	mPosition.x += mVelocityX;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			if (p->mTag != EJEWELRY ) {
				mPosition = mPosition + aj;
			}
			mJumpCount = 0;
			mVelocityG = 0.0f;
			return true;
		}
	}
	return false;
}

void CPlayerT::Render(){
	switch (player_ani){
	default:
		break;

	case EPLAYERANI::EIDOL:
		if (player_ani_count > 7)
			player_ani_count = 0;

		PLAYER_ANI_COUNT_FLAME = 8;

		if (!mDirection)	//左向き
			mTexPlayer.DrawImage(CGame2::mRectPlayer->mPosition.x - CELLSIZE, CGame2::mRectPlayer->mPosition.x + CELLSIZE, CGame2::mRectPlayer->mPosition.y - CELLSIZE, CGame2::mRectPlayer->mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 128, 0, 1.0f);
		else				//右向き
			mTexPlayer.DrawImage(CGame2::mRectPlayer->mPosition.x - CELLSIZE, CGame2::mRectPlayer->mPosition.x + CELLSIZE, CGame2::mRectPlayer->mPosition.y - CELLSIZE, CGame2::mRectPlayer->mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 128, 0, 1.0f);
		break;

	case EPLAYERANI::ERUN:
		if (player_ani_count > 2)
			player_ani_count = 0;

		if (!mDirection){	//左向き
			PLAYER_ANI_COUNT_FLAME = 3 + (5 / -CGamePad::GetStick(PAD_LSTICKX));
			mTexPlayer.DrawImage(CGame2::mRectPlayer->mPosition.x - CELLSIZE, CGame2::mRectPlayer->mPosition.x + CELLSIZE, CGame2::mRectPlayer->mPosition.y - CELLSIZE, CGame2::mRectPlayer->mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 256, 128, 1.0f);
		}

		else{				//右向き
			PLAYER_ANI_COUNT_FLAME = 3 + (5 / CGamePad::GetStick(PAD_LSTICKX));
			mTexPlayer.DrawImage(CGame2::mRectPlayer->mPosition.x - CELLSIZE, CGame2::mRectPlayer->mPosition.x + CELLSIZE, CGame2::mRectPlayer->mPosition.y - CELLSIZE, CGame2::mRectPlayer->mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 256, 128, 1.0f);
		}
		break;

	case EPLAYERANI::ETURN:

		break;

	case EPLAYERANI::EJUMP:

		break;

	case EPLAYERANI::EDAMAGE:

		break;

	case EPLAYERANI::EYOHYOH:

		break;

	case EPLAYERANI::EDOWN:

		break;
	}

	player_ani_count_flame++;
	if (player_ani_count_flame > PLAYER_ANI_COUNT_FLAME){
		player_ani_count++;
		player_ani_count_flame = 0;
	}
}