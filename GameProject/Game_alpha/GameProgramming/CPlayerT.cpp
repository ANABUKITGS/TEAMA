#include "CPlayerT.h"
#include "CMapSwitchGround.h"
#include "CScene.h"
#include "CFade.h"
#include "CMapScroll.h"

#define PLAYER_VELOCITY_X		1.25f	//入力
#define PLAYER_VELOCITY_X_ICE	0.15f	//入力 氷足場
#define PLAYER_VELOCITY_X2		0.25f	//非入力
#define PLAYER_VELOCITY_X2_ICE	0.05f	//非入力 氷足場
#define ATTACK_TIME 30

CPlayerT *CPlayerT::mpPlayer = 0;
CMapSwitchGround *mSwitch;

int CPlayerT::player_ani;

void CPlayerT::Update(){
	if (player_ani != EPLAYERANI::EDAMAGE){
		if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
			if (mpWeapon == 0){
				if ((CGamePad::Push(PAD_1) || CKey::Push(VK_UP))){
					player_ani_count = 0;
					player_ani_count_frame = 0;
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
					player_ani_count_frame = 0;
				}
				if (mJumpCount < 2 && (CGamePad::Push(PAD_2) || CKey::Push(VK_SPACE) || CKey::Push(VK_RIGHT))){		//ジャンプ回数２未満かつ２キーまたは→キー入力
					mAerialAttack = true;
					//mAir = true;
					if (!mJump)
						mVelocityY = PLAYER_VELOCITY_Y;

					if (!mAir)
						player_ani = EPLAYERANI::EIDOL;
					else{
						if (mpWeapon != 0 && mpWeapon->mLife > 0 && !mpWeapon->mReturn)
							player_ani = EPLAYERANI::EJUMP;
					}
					mJump = true;
				}
				else if (mJump){
					mJumpCount++;
					mJump = false;
					mVelocityY = 0;
				}
			}
			else if (mpWeapon->mReturn){		//武器の生存時間が0以下
				mpWeapon = 0;
			}
			else {								//武器の生存時間が0を超過
				player_ani = EPLAYERANI::EYOYO;
				//mpWeapon->Render();	//要らないのでは?
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
				if (player_ani != EPLAYERANI::EYOYO)
					player_ani = EPLAYERANI::EJUMP;
			}
		}
	}
	if (!CGame2::mCheat[CGame2::CHEAT_NUM::EAREA] && CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		//エリア外
		if (mPosition.x + CELLSIZE < CMapScroll::mpScroll->mPosition.x - 640.0f ||	//エリア外(左)
			mPosition.y + CELLSIZE < 0.0f){	//エリア外(下)
			mPosition = mReSpornPos;
			mVelocityX = mVelocityY = 0.0f;
			player_ani = EPLAYERANI::EIDOL;
			mJumpCount = 0;
			if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI])
				mLife--;
			CMapScroll::mpScroll->Reset();
		}

		//エリア外(右)
		if (mPosition.x > CMapScroll::mpScroll->mPosition.x + 640.0f)
			mPosition.x = CMapScroll::mpScroll->mPosition.x + 640.0f;

		//エリア外(上)
		if (mPosition.y - CELLSIZE > 720.0f){
			mVelocityY = 0.0f;
			mPosition.y = 720.0f + CELLSIZE;
		}
	}
	if (mLife == 0){
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
	}
}

//前進処理
void CPlayerT::Forward(){
	if (player_ani != EPLAYERANI::EDAMAGE){
		if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CGamePad::Push(PAD_LSTICKX, -0.1f)){
			if (!CMapScroll::scroll_flg)
				CMapScroll::scroll_flg = true;

			if (CGamePad::Push(PAD_LSTICKX, 0.1f)){
				float hoge = mVelocityLimit * CGamePad::GetStick(PAD_LSTICKX);
				mDirection = true;
				if (mVelocityX < hoge && mVelocityX > -hoge){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X;
					else
						mVelocityX += PLAYER_VELOCITY_X_ICE;
				}

				if (!mAir)
					player_ani = EPLAYERANI::ETURN;

				if (mVelocityX > 0){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X2;
					else
						mVelocityX -= PLAYER_VELOCITY_X2_ICE;

					if (!mAir)
						player_ani = ERUN;
				}
				else if (mVelocityX < 0){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X2;
					else
						mVelocityX += PLAYER_VELOCITY_X2_ICE;
				}
			}

			if (CGamePad::Push(PAD_LSTICKX, -0.1f)){
				float hoge = mVelocityLimit * -CGamePad::GetStick(PAD_LSTICKX);
				mDirection = false;
				if (mVelocityX < hoge && mVelocityX > -hoge){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X;
					else
						mVelocityX -= PLAYER_VELOCITY_X_ICE;
				}

				if (!mAir)
					player_ani = EPLAYERANI::ETURN;

				if (mVelocityX > 0){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X2;
					else
						mVelocityX -= PLAYER_VELOCITY_X2_ICE;
				}
				else if (mVelocityX < 0){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X2;
					else
						mVelocityX += PLAYER_VELOCITY_X2_ICE;

					if (!mAir)
						player_ani = ERUN;
				}
			}
		}
		else if (CKey::Push('D') || CKey::Push('A')){
			if (!CMapScroll::scroll_flg)
				CMapScroll::scroll_flg = true;

			if (CKey::Push('D')){
				mDirection = true;
				if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X;
					else
						mVelocityX += PLAYER_VELOCITY_X_ICE;
				}

				if (!mAir)
					player_ani = EPLAYERANI::ETURN;

				if (mVelocityX > 0){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X2;
					else
						mVelocityX -= PLAYER_VELOCITY_X2_ICE;

					if (!mAir)
						player_ani = ERUN;
				}
				else if (mVelocityX < 0){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X2;
					else
						mVelocityX += PLAYER_VELOCITY_X2_ICE;
				}
			}

			if (CKey::Push('A')){
				mDirection = false;
				if (mVelocityX < mVelocityLimit && mVelocityX > -mVelocityLimit){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X;
					else
						mVelocityX -= PLAYER_VELOCITY_X_ICE;
				}

				if (!mAir)
					player_ani = EPLAYERANI::ETURN;

				if (mVelocityX > 0){
					if (!mIce)
						mVelocityX -= PLAYER_VELOCITY_X2;
					else
						mVelocityX -= PLAYER_VELOCITY_X2_ICE;
				}
				else if (mVelocityX < 0){
					if (!mIce)
						mVelocityX += PLAYER_VELOCITY_X2;
					else
						mVelocityX += PLAYER_VELOCITY_X2_ICE;

					if (!mAir)
						player_ani = ERUN;
				}
			}
		}
		else{
			if (mVelocityX < 0){
				if (!mIce)
					mVelocityX += PLAYER_VELOCITY_X2;
				else
					mVelocityX += PLAYER_VELOCITY_X2_ICE;
			}
			else if (mVelocityX > 0){
				if (!mIce)
					mVelocityX -= PLAYER_VELOCITY_X2;
				else
					mVelocityX -= PLAYER_VELOCITY_X2_ICE;
			}

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
	if (mVelocityX - PLAYER_VELOCITY_X2_ICE < 0.0f && mVelocityX + PLAYER_VELOCITY_X2_ICE > 0.0f)
		mVelocityX = 0.0f;
}


bool CPlayerT::Collision(CRectangle *p) {
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EEWEAPON:
				if (!mUnrivaled){
					mUnrivaled = true;
					player_ani = EPLAYERANI::EDAMAGE;
					player_ani_count = 0;
					player_ani_count_frame = 0;
					if (mJewel > 0){
						if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI])
							mJewel--;
					}
					else{
						if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI]){
							mLife--;
							mPosition = mReSpornPos;
							CMapScroll::mpScroll->Reset();
						}
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

			case EICE:
				mIce = true;
				break;

			case ESWITCH_GROUND1:
			case ESWITCH_GROUND2:
			case ECHIKUWA:
			case EBELTL:
			case EBELTR:
			case EUNDER:
				mIce = false;
				break;

			case EENEMY1:
			case EENEMY2:
			case EENEMY3:
			case EBOSS:
			case ENONE:
			case EPWEAPON:
			case ESEARCH:
			case ESWITCH:
			case ESIGN:
			case EENDSIGN:
			case EBOSSROOM:
				break;

			default:
			{
						CVector2 ad;
						if (aj.x > 0) {
							//右空き
							if (!(p->mColFlg & EDT_RIGHT)) {
								mPosition.x = mPosition.x + aj.x;
								mVelocityX = 0.0f;
							}
						}
						else if (aj.x < 0) {
							//左空き
							if (!(p->mColFlg & EDT_LEFT)) {
								mPosition.x = mPosition.x + aj.x;
								mVelocityX = 0.0f;
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
				mIce = false;
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

		PLAYER_ANI_COUNT_FRAME = 8;

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
					PLAYER_ANI_COUNT_FRAME = 3 + (5 / -CGamePad::GetStick(PAD_LSTICKX));

				else
					PLAYER_ANI_COUNT_FRAME = (3 + (5 / -CGamePad::GetStick(PAD_LSTICKX))) / 2;
			}
			else{
				if (!mDash)
					PLAYER_ANI_COUNT_FRAME = 8;
				else
					PLAYER_ANI_COUNT_FRAME = 4;
			}

			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 256, 128, mAlpha);
		}

		else{				//右向き
			if (CGamePad::Push(PAD_LSTICKX, 0.1f) || CGamePad::Push(PAD_LSTICKX, -0.1f)){
				if (!mDash)
					PLAYER_ANI_COUNT_FRAME = 3 + (5 / CGamePad::GetStick(PAD_LSTICKX));

				else
					PLAYER_ANI_COUNT_FRAME = (3 + (5 / CGamePad::GetStick(PAD_LSTICKX))) / 2;
			}
			else{
				if (!mDash)
					PLAYER_ANI_COUNT_FRAME = 8;
				else
					PLAYER_ANI_COUNT_FRAME = 4;
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

			PLAYER_ANI_COUNT_FRAME = 10;

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
		if (player_ani_count > 1)
			player_ani_count = 1;

		PLAYER_ANI_COUNT_FRAME = 4;

		if (!mDirection)	//左向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, player_ani_count * 128, (player_ani_count + 1) * 128, 640, 512, mAlpha);
		else				//右向き
			mTexPlayer.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (player_ani_count + 1) * 128, player_ani_count * 128, 640, 512, mAlpha);
		break;

	case EPLAYERANI::EYOYO:
		if (player_ani_count > 1)
			player_ani_count = 1;

		PLAYER_ANI_COUNT_FRAME = 6;

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

	player_ani_count_frame++;
	if (player_ani_count_frame > PLAYER_ANI_COUNT_FRAME){
		player_ani_count++;
		player_ani_count_frame = 0;
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