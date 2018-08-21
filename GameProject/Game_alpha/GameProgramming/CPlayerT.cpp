#include "CPlayerT.h"
#include "CMapSwitchGround.h"
#include "CScene.h"

#define PLAYER_VELOCITY_X 1.25f
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;
CMapSwitchGround*mSwitch;

int CPlayerT::player_ani;

void CPlayerT::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		if (mpWeapon == 0){
			if ((CGamePad::Push(PAD_1) || CKey::Push(VK_UP))){
				player_ani_count = 0;
				player_ani_count_flame = 0;
				player_ani = EPLAYERANI::EYOYO;
				if (mAir){
					if (mAerialAttack){
						mAerialAttack = false;
						mpWeapon = new CWeapon(EPWEAPON, mPosition, mDirection);
						if (mDirection)		//weaponの位置をプレイヤーの向いている方向へ10ずらす
							mpWeapon->mPosition.x += 10;
						else
							mpWeapon->mPosition.x -= 10;
					}
				}
				else{
					mpWeapon = new CWeapon(EPWEAPON, mPosition, mDirection);
					if (mDirection)		//weaponの位置をプレイヤーの向いている方向へ10ずらす
						mpWeapon->mPosition.x += 10;
					else
						mpWeapon->mPosition.x -= 10;
				}
			}

			if (mJumpCount < 2 && (CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE) || CKey::Once(VK_RIGHT))){
				player_ani_count = 0;
				player_ani_count_flame = 0;
			}
			if (mJumpCount < 2 && (CGamePad::Push(PAD_2) || CKey::Push(VK_SPACE) || CKey::Push(VK_RIGHT))){		//ジャンプ回数２未満かつ２キーまたは→キー入力
				mAerialAttack = true;
				//mAir = true;
				if (!mJump)
					mVelocityY = PLAYER_VELOCITY_Y;

				if (!mAir)
					player_ani = EIDOL;
				else{
					if (mpWeapon != 0 && mpWeapon->mLife > 0)
						player_ani = EJUMP;
				}
				mJump = true;
			}
			else if (mJump){
				mJumpCount++;
				mJump = false;
				mVelocityY = 0;
			}
		}
		else if (mpWeapon->mLife <= 0){		//武器の生存時間が0以下
			mpWeapon = 0;
		}
		else {								//武器の生存時間が0を超過
			player_ani = EYOYO;
			mpWeapon->Render();
		}
		if (mpWeapon == 0){
			Dash();
			Gravity();
			Forward();
			CRectangle::Update();
		}

		if (mVelocityY < -1.0f && mVelocityY > -1.1f)
			mAir = false;
		else{
			mAir = true;
			if (player_ani != EYOYO)
			player_ani = EJUMP;
		}
	}

	//落下死
	if (mPosition.y + CELLSIZE < 0.0f){
		mPosition = mReSpornPos;
		mVelocityX = mVelocityY = 0.0f;
		player_ani = EIDOL;
		mJumpCount = 0;
		if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI])
			mLife--;
	}

	//エリア外(上)
	if (mPosition.y - CELLSIZE > 720.0f){
		mVelocityY = 0.0f;
		mPosition.y = 720.0f + CELLSIZE;
	}
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

			if (!mAir)
				player_ani = ETURN;

			if (mVelocityX > 0){
				mVelocityX -= 0.25f;

				if (!mAir)
					player_ani = ERUN;
			}
			else if (mVelocityX < 0){
				mVelocityX += 0.25f;
			}
		}

		if (CGamePad::Push(PAD_LSTICKX, -0.1f)){
			float hoge = mVelocityLimit * -CGamePad::GetStick(PAD_LSTICKX);
			mDirection = false;
			if (mVelocityX < hoge && mVelocityX > -hoge){
				mVelocityX -= PLAYER_VELOCITY_X;
			}

			if (!mAir)
				player_ani = ETURN;

			if (mVelocityX > 0){
				mVelocityX -= 0.25f;
			}
			else if (mVelocityX < 0){
				mVelocityX += 0.25f;

				if (!mAir)
					player_ani = ERUN;
			}
		}
	}
	else if (CKey::Push('D') || CKey::Push('A')){
		if (CKey::Push('D')){
			mDirection = true;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX += PLAYER_VELOCITY_X;

			if (!mAir)
				player_ani = ETURN;

			if (mVelocityX > 0){
				mVelocityX -= 0.25f;

				if (!mAir)
					player_ani = ERUN;
			}
			else if (mVelocityX < 0){
				mVelocityX += 0.25f;
			}
		}

		if (CKey::Push('A')){
			mDirection = false;
			if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit)
				mVelocityX -= PLAYER_VELOCITY_X;

			if (!mAir)
				player_ani = ETURN;

			if (mVelocityX > 0){
				mVelocityX -= 0.25f;
			}
			else if (mVelocityX < 0){
				mVelocityX += 0.25f;

				if (!mAir)
					player_ani = ERUN;
			}
		}
	}
	else{
		if (mVelocityX < 0)
			mVelocityX += 0.25f;

		else if (mVelocityX > 0)
			mVelocityX -= 0.25f;

		if (!mAir)
			player_ani = EIDOL;
	}
	mPosition.x += mVelocityX;
	if (mUnrivaled){
		mDamageInterval--;
		if (mDamageInterval % 15 == 0){
			mAlpha = 0.0f;
		}
		else
			mAlpha = 1.0f;
		if (mDamageInterval <= 0){
			mDamageInterval = DAMAGE_INTERVAL;
			mUnrivaled = false;
			mAlpha = 1.0f;
		}
	}
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EENEMY1: case EEWEAPON:
				if (!mUnrivaled){
					mUnrivaled = true;
					if (mJewel > 0){
						if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI])
							mJewel--;
					}
					else{
						mLife--;
						mPosition = mReSpornPos;
					}
				}
				break;

			case EJEWELRY:
				mJewel++;
				break;

			case EJEWELRY2:
				mMiniJewel++;
				if (mMiniJewel == 10){
					mJewel++;
					mMiniJewel = 0;
				}
				break;

			case ECHECKPOINT:
				mReSpornPos = p->mPosition;
				break;

			case ESWITCH_GROUND1:
			case ESWITCH_GROUND2:
			case ENONE:
			case ECHIKUWA:
			case EBELTL:
			case EBELTR:
			case ESIGN:
			case EPWEAPON:
			case ESEARCH:
			case ESWITCH:
			case EUNDER:
				break;

			default:
			{
					   CVector2 ad;
					   if (aj.x > 0) {
						   //右空き
						   if (!(p->mColFlg & EDT_RIGHT)) {
							   mPosition.x = mPosition.x + aj.x;
						   }
					   }
					   else if (aj.x < 0) {
						   //左空き
						   if (!(p->mColFlg & EDT_LEFT)) {
							   mPosition.x = mPosition.x + aj.x;
						   }
					   }
					   if (CRectangle::Collision(p, &aj, &ad)) {
						   if (ad.y < 0) {
							   //下空き
							   if (!(p->mColFlg & EDT_BOTTOM)) {
								   mPosition.y = mPosition.y + ad.y;
								   mVelocityY = 0.0f;
							   }
						   }
						   else if (ad.y > 0) {
							   //上空き
							   if (!(p->mColFlg & EDT_TOP)) {
								   mPosition.y = mPosition.y + ad.y;
								   mJumpCount = 0;
								   mVelocityY = 0.0f;
							   }
						   }
					   }
			}
				break;


			}
			return true;
		}
	}
	return false;
}

void CPlayerT::Render(){
	mRender = false;
	switch (player_ani){
	case EPLAYERANI::EIDOL:
		if (player_ani_count > 7)
			player_ani_count = 0;

		PLAYER_ANI_COUNT_FLAME = 8;

		if (!mDirection)	//左向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 128, 0, mAlpha);
		else				//右向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 128, 0, mAlpha);
		break;

	case EPLAYERANI::ERUN:
		if (player_ani_count > 5)
			player_ani_count = 0;

		if (!mDirection){	//左向き
			if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CGamePad::Push(PAD_LSTICKX, -0.1f)){
				if (!mDash)
					PLAYER_ANI_COUNT_FLAME = 3 + (5 / -CGamePad::GetStick(PAD_LSTICKX));

				else
					PLAYER_ANI_COUNT_FLAME = (3 + (5 / -CGamePad::GetStick(PAD_LSTICKX))) / 2;
			}
			else{
				if (!mDash)
					PLAYER_ANI_COUNT_FLAME = 8;
				else
					PLAYER_ANI_COUNT_FLAME = 4;
			}

			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 256, 128, mAlpha);
		}

		else{				//右向き
			if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CGamePad::Push(PAD_LSTICKX, -0.1f)){
				if (!mDash)
					PLAYER_ANI_COUNT_FLAME = 3 + (5 / CGamePad::GetStick(PAD_LSTICKX));

				else
					PLAYER_ANI_COUNT_FLAME = (3 + (5 / CGamePad::GetStick(PAD_LSTICKX))) / 2;
			}
			else{
				if (!mDash)
					PLAYER_ANI_COUNT_FLAME = 8;
				else
					PLAYER_ANI_COUNT_FLAME = 4;
			}

			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 256, 128, mAlpha);
		}
		break;

	case EPLAYERANI::ETURN:
		if (player_ani_count > 0)
			player_ani_count = 0;

		if (mDirection)	//右向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 128, 384, 256, mAlpha);

		else			//左向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 128, 0, 384, 256, 1.0f);
		break;

	case EPLAYERANI::EJUMP:

		if (mVelocityY > 0.0f){
			if (player_ani_count > 1)
				player_ani_count = 0;

			PLAYER_ANI_COUNT_FLAME = 10;

			if (!mDirection)	//左向き
				mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 512, 384, mAlpha);
			else				//右向き
				mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 512, 384, mAlpha);
		}

		else if (mVelocityY <= 0.0f){
			if (player_ani_count > 0)
				player_ani_count = 0;

			if (!mDirection)	//左向き
				mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 256, 384, 512, 384, mAlpha);
			else				//右向き
				mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 384, 256, 512, 384, mAlpha);
		}
		break;

	case EPLAYERANI::EDAMAGE:

		break;

	case EPLAYERANI::EYOYO:
		if (player_ani_count > 1)
			player_ani_count = 1;

		PLAYER_ANI_COUNT_FLAME = 6;

		if (!mDirection)	//左向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 768, 640, mAlpha);
		else				//右向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 768, 640, mAlpha);
		break;

	case EPLAYERANI::EDOWN:

		break;

	default:
		break;
	}

	player_ani_count_flame++;
	if (player_ani_count_flame > PLAYER_ANI_COUNT_FLAME){
		player_ani_count++;
		player_ani_count_flame = 0;
	}
}

void CPlayerT::Dash(){
	if (CGamePad::Push(PAD_3) || CKey::Push(VK_CONTROL) || CKey::Push(VK_SHIFT) || CKey::Push(VK_DOWN)){
		mVelocityLimit = VELOCITYX_LIMIT * 2;
		mDash = true;
	}
	else{
		mVelocityLimit = VELOCITYX_LIMIT;
		mDash = false;
	}
}