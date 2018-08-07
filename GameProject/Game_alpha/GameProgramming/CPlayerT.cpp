#include "CPlayerT.h"

#define PLAYER_VELOCITY_X 1.25f
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;
wchar_t jumptime_buf[256];

int CPlayerT::player_ani;

void CPlayerT::Update(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL) || CKey::Push(VK_SHIFT) || CKey::Push(VK_DOWN))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;

	
	if (mpWeapon == 0){
		if ((CGamePad::Push(PAD_1) || CKey::Push(VK_UP))){
			mpWeapon = new CWeapon(EPWEAPON,mPosition, CVector2(10, 10), mDirection, NULL);
			if (mDirection)		//weaponの位置をプレイヤーの向いている方向へ10ずらす
				mpWeapon->mPosition.x += 10;
			else
				mpWeapon->mPosition.x -= 10;
		}

		if (mJumpCount < 2 && CGamePad::Push(PAD_2) || CKey::Push(VK_RIGHT) ){		//ジャンプ回数２未満かつ２キーまたは→キー入力　
			if (!mJump)
				mVelocityY = PLAYER_VELOCITY_Y;
			mJump = true;
			
		}
		else if (mJump){
			mJumpCount++;
			mJump = false;
		}
		
	}
	else if (mpWeapon->mLife <= 0){		//武器の生存時間が0以下
		mpWeapon = 0;
	}
	else{								//武器の生存時間が0を超過
		mpWeapon->Render();
	}
	if (mpWeapon == 0){
		Dash();
		Gravity();
		Forward();
		CRectangle::Update();
	}
	
	swprintf(jumptime_buf, L"mVelocityX\n%4.2f\nmVelocityY\n%4.2f\nmPosition.x\n%4.2f\nmPosition.y\n%4.2f", mVelocityX, mVelocityY, mPosition.x, mPosition.y);
	CText::DrawStringW(jumptime_buf, 0, 0, 32, 1.0f, 0);
	
}

//前進処理
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

		else if (CGamePad::Push(PAD_LSTICKX, -0.1f)){
			float hoge = mVelocityLimit * -CGamePad::GetStick(PAD_LSTICKX);
			mDirection = false;
			if (mVelocityX < hoge && mVelocityX > -hoge){
				mVelocityX -= PLAYER_VELOCITY_X;
			}
			player_ani = ERUN;
		}
	}
	else if (CKey::Push('D') || CKey::Push('A')){
		if (CKey::Push('D')){
			mDirection = true;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX += PLAYER_VELOCITY_X;
			player_ani = ERUN;
		}

		if (CKey::Push('A')){
			mDirection = false;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX -= PLAYER_VELOCITY_X;
			player_ani = ERUN;
		}
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += 0.25f;
		else if (mVelocityX>0)
			mVelocityX -= 0.25f;
			player_ani = EIDOL;
	}
	mPosition.x += mVelocityX;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			if (p->mTag != EJEWELRY && p->mTag != EPWEAPON) {
				mPosition = mPosition + aj;
			}
			mJumpCount = 0;
			mVelocityY = 0.0f;
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
		if (CGamePad::Push(PAD_3) || CKey::Push(VK_DOWN)) {
			PLAYER_ANI_COUNT_FLAME = 3;
		}
		else {
			PLAYER_ANI_COUNT_FLAME = 6;
		}

		if (!mDirection){	//左向き
//			PLAYER_ANI_COUNT_FLAME = 3 + (5 / -CGamePad::GetStick(PAD_LSTICKX));
			mTexPlayer.DrawImage(CGame2::mRectPlayer->mPosition.x - CELLSIZE, CGame2::mRectPlayer->mPosition.x + CELLSIZE, CGame2::mRectPlayer->mPosition.y - CELLSIZE, CGame2::mRectPlayer->mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 256, 128, 1.0f);
		}

		else{				//右向き
//			PLAYER_ANI_COUNT_FLAME = 3 + (5 / CGamePad::GetStick(PAD_LSTICKX));
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

void CPlayerT::Dash(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL) || CKey::Push(VK_SHIFT))
		mVelocityLimit = VELOCITYX_LIMIT * 2;
	else
		mVelocityLimit = VELOCITYX_LIMIT;
}