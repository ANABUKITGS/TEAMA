#include "CEnemy.h"
#include "CScene.h"
#include "CBoss.h"
#include "CMapBox.h"
#include "CMapSteel.h"
#include "CMapSign.h"

/*
敵の索敵範囲
*/
//bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
//	CVector2 Search = player->mPosition - enemy->mPosition;
//	if (Search.Length() < player->mSearch + enemy->mSearch){
//		return true;
//	}
//	return false;
//}


void  CEnemy::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER && !CMapSign::mCol){
		mAttackInterval--;
		//敵の歩く、待機アニメーションを行う処理
		switch (enemy_ani){
		case EENEMYANI::EWALK:
			mWalkTime--;
			if (mpSearch->mDiscovery){
				enemy_ani = EYOYO;
				enemy_ani_count = 0;
			}

			if (mVelocityX < ENEMY_VELOCITY_X_LIMIT && mVelocityX > -ENEMY_VELOCITY_X_LIMIT){
				if (mDirection){
					if (!mIce)
						mVelocityX += ENEMY_VELOCITY_X;
					else
						mVelocityX += ENEMY_VELOCITY_X_ICE;
				}
				else{
					if (!mIce)
						mVelocityX -= ENEMY_VELOCITY_X;
					else
						mVelocityX -= ENEMY_VELOCITY_X_ICE;
				}
			}
			if (mDirection){
				mPosition.x += mVelocityX;
				mpSearch->mPosition = CVector2(mPosition.x + 100, mPosition.y);
			}
			else{
				mPosition.x += mVelocityX;
				mpSearch->mPosition = CVector2(mPosition.x - 100, mPosition.y);
			}
			if (mWalkTime < 0){
				enemy_ani = EENEMYANI::EIDOL;
				enemy_ani_count = 0;
			}
			mAttackInterval2 = ATTACK_INTERVAL2;
			break;

		case EENEMYANI::EIDOL:
			mMonitorTime--;
			if (mpSearch->mDiscovery){
				enemy_ani = EENEMYANI::EYOYO;
				enemy_ani_count = 0;
			}

			if (mMonitorTime < 0){
				mMonitorTime = MONITOR_TIME;
				enemy_ani = EENEMYANI::EWALK;
				enemy_ani_count = 0;
				mWalkTime = WALK_TIME;
				if (mDirection)
					mDirection = false;
				else
					mDirection = true;
			}

			if (mVelocityX < 0.0f){
				if (!mIce)
					mVelocityX += ENEMY_VELOCITY_X2;
				else
					mVelocityX += ENEMY_VELOCITY_X2_ICE;
			}
			else if (mVelocityX > 0.0f){
				if (!mIce)
					mVelocityX -= ENEMY_VELOCITY_X2;
				else
					mVelocityX -= ENEMY_VELOCITY_X2_ICE;
			}
			if (mDirection){
				mPosition.x += mVelocityX;
				mpSearch->mPosition = CVector2(mPosition.x + 100, mPosition.y);
			}
			else{
				mPosition.x += mVelocityX;
				mpSearch->mPosition = CVector2(mPosition.x - 100, mPosition.y);
			}
			mAttackInterval2 = ATTACK_INTERVAL2;
			break;

		case EENEMYANI::EYOYO:
			mAttackInterval2--;
			//敵がヨーヨーを発射していなければ、ヨーヨーを発射して処理を行う
			if (!mpEWeapon){
				if (mAttackInterval < 0){
					if (mAttackInterval2 < 0){
						mAttackInterval = ATTACK_INTERVAL;
						//敵のヨーヨーを敵の位置よりも少し前に呼び出す
						if (mDirection){
							CSE::mSoundYoyo.Play();
							mpEWeapon = new CWeapon(this, EEWEAPON, mPosition + CVector2(56.0f, 13.0f), mDirection);
						}
						else{
							CSE::mSoundYoyo.Play();
							mpEWeapon = new CWeapon(this, EEWEAPON, mPosition + CVector2(-56.0f, 13.0f), mDirection);
						}
					}
				}
			}
			//敵のヨーヨーが発射された時の処理を行う
			else {
				if (mpEWeapon->mLife <= -1){
					mpEWeapon = 0;
					if (mAttackInterval < 0){
						enemy_ani_count = 0;
						enemy_ani = EENEMYANI::EWALK;
					}
					else{
						enemy_ani_count = 0;
						enemy_ani = EENEMYANI::EWALK;
					}
				}
			}
			//ヨーヨーの処理終了
			break;

		case EENEMYANI::EDOWN:
		case EENEMYANI::EDAMAGE:
			mDownTime--;
			//if (mDownTime % 10 == 0)
			//	mAlpha = 0.0f;
			//else
			//	mAlpha = 1.0f;

			if (mDownTime < 0){
				mEnabled = false;
				mpSearch = false;
			}
			mAlpha -= 0.01f;
			break;

		default:
			break;
		}
		if (mVelocityX - ENEMY_VELOCITY_X2_ICE < 0.0f && mVelocityX + ENEMY_VELOCITY_X2_ICE > 0.0f)
			mVelocityX = 0.0f;
		Gravity();

		if ((mAlpha < 1.0f && enemy_ani != EENEMYANI::EDOWN) ||
			(CBoss::mpBoss != NULL && enemy_ani != EENEMYANI::EDOWN && CBoss::mpBoss->mAttackBehavior == CBoss::AttackBehavior::EDOWN)){
			enemy_ani = EENEMYANI::EDAMAGE;
		}
	}
	CRectangle::Update();
}
bool CEnemy::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case ECELLNUM::EPWEAPON:
				if (enemy_ani != EENEMYANI::EDAMAGE && enemy_ani != EENEMYANI::EDOWN){
					CSE::mSoundDamage.Play();
						enemy_ani = EENEMYANI::EDAMAGE;
						new CMapJewelry(p->mPosition);
					mVelocityX = 0.0f;
					enemy_ani_count = 0;
				}

				break;
				
			case ECELLNUM::EICE:
				mIce = true;

			case ECELLNUM::ESWITCH_GROUND1:
			case ECELLNUM::ESWITCH_GROUND2:
			case ECELLNUM::ECHIKUWA:
			case ECELLNUM::EBELTL:
			case ECELLNUM::EBELTR:
			case ECELLNUM::EUNDER:
				mIce = false;
				break;

			case ECELLNUM::EBOX:
			case ECELLNUM::ESTEEL:
				mIce = false;
				if (p->mBreak && p->mAlpha >= 1.0f){
					CSE::mSoundDamage.Play();
					if (p->mTag == ECELLNUM::ESTEEL)
						CSE::mSoundSteel.Play();
					enemy_ani = EENEMYANI::EDAMAGE;
				}
				break;

			case ECELLNUM::EENEMY1:
			case ECELLNUM::EENEMY2:
			case ECELLNUM::EENEMY3:
			case ECELLNUM::EBOSS:
			case ECELLNUM::ENONE:
			case ECELLNUM::ESEARCH:
			case ECELLNUM::ESWITCH:
			case ECELLNUM::ESIGN:
			case ECELLNUM::EENDSIGN:
			case ECELLNUM::EBOSSROOM:
			case ECELLNUM::EJEWELRY:
			case ECELLNUM::EJEWELRY2:
			case ECELLNUM::ECHECKPOINT:
			case ECELLNUM::EPLAYER:
			case ECELLNUM::EEWEAPON:
			case ECELLNUM::EBWEAPON:
			case ECELLNUM::ESDIAMOND:
				break;

			default:
				//右空き
				if (!(p->mColFlg & EDT_RIGHT)) {
					if (aj.x > 0) {
						mPosition.x = mPosition.x + aj.x;
						enemy_ani = EENEMYANI::EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
					}
				}
				//左空き
				if (!(p->mColFlg & EDT_LEFT)) {
					if (aj.x < 0) {
						mPosition.x = mPosition.x + aj.x;
						enemy_ani = EENEMYANI::EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
					}
				}
				//下空き
				if (!(p->mColFlg & EDT_BOTTOM)) {
					if (aj.y < 0) {
						mPosition.y = mPosition.y + aj.y;
						mVelocityY = 0.0f;
					}
				}
				//上空き
				if (!(p->mColFlg & EDT_TOP)) {
					if (aj.y > 0) {
						mPosition.y = mPosition.y + aj.y;
						mVelocityY = 0.0f;
					}
				}
				break;
			}
			return true;
		}
	}
	return false;
}

void CEnemy::Render(){
	switch (enemy_ani){
	case EENEMYANI::EIDOL:
		if (enemy_ani_count > 0)
			enemy_ani_count = 0;

		ENEMY_ANI_COUNT_FLAME = 0;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//左向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//左向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//左向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}
		break;
	case EENEMYANI::ETURN:
	case EENEMYANI::EJUMP:
	case EENEMYANI::EWALK:
		if (enemy_ani_count > 7)
			enemy_ani_count = 0;

		ENEMY_ANI_COUNT_FLAME = 4;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//左向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//左向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//左向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//右向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}
		break;

	case EENEMYANI::EYOYO:
		if (mpEWeapon != NULL){
			//if (mDirection)
			//	//ヨーヨーの紐
			//	mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_R, 1.0f);

			//else
			//	//ヨーヨーの紐
			//	mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_L, 1.0f);

			if (enemy_ani_count > 1)
				enemy_ani_count = 1;

			ENEMY_ANI_COUNT_FLAME = 12;

			if (mTag == ECELLNUM::EENEMY1){
				if (!mDirection)	//左向き
					mTexEnemy01.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//右向き
					mTexEnemy01.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY2){
				if (!mDirection)	//左向き
					mTexEnemy02.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//右向き
					mTexEnemy02.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY3){
				if (!mDirection)	//左向き
					mTexEnemy03.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//右向き
					mTexEnemy03.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}
		}
		else {
			if (enemy_ani_count > 0)
				enemy_ani_count = 0;

			ENEMY_ANI_COUNT_FLAME = 0;

			if (mTag == ECELLNUM::EENEMY1){
				if (!mDirection)	//左向き
					mTexEnemy01.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//右向き
					mTexEnemy01.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY2){
				if (!mDirection)	//左向き
					mTexEnemy02.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//右向き
					mTexEnemy02.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY3){
				if (!mDirection)	//左向き
					mTexEnemy03.DrawImage(ENEMY_TEX_POS, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//右向き
					mTexEnemy03.DrawImage(ENEMY_TEX_POS, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}
		}
		break;

	case EENEMYANI::EDAMAGE:

		ENEMY_ANI_COUNT_FLAME = 6;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//左向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//右向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//左向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//右向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//左向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//右向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (enemy_ani_count > 1)
			enemy_ani = EENEMYANI::EDOWN;

		break;

	case EENEMYANI::EDOWN:
		if (enemy_ani_count > 0)
			enemy_ani_count = 0;

		ENEMY_ANI_COUNT_FLAME = 0;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//左向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, 0, 128, 512, 384, mAlpha);
			else				//右向き
				mTexEnemy01.DrawImage(ENEMY_TEX_POS, (0 + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//左向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 512, 384, mAlpha);
			else				//右向き
				mTexEnemy02.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//左向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 512, 384, mAlpha);
			else				//右向き
				mTexEnemy03.DrawImage(ENEMY_TEX_POS, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
		}
		break;

	default:
		break;
	}

	enemy_ani_count_flame++;
	if (enemy_ani_count_flame > ENEMY_ANI_COUNT_FLAME){
		enemy_ani_count++;
		enemy_ani_count_flame = 0;
	}
	CRectangle::Render();
}

void CSearch::Update(){
	CRectangle::Update();
}

bool CSearch::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (p->mTag == EPLAYER) {
			if (CRectangle::Collision(p)){
				mDiscovery = true;
			}
			else{
				mDiscovery = false;
			}
			return true;
		}
	}
	return false;
}

void CSearch::Render(){
	if (mRender){
		CRectangle::Render(WHITE, 0.0f);
	}
}