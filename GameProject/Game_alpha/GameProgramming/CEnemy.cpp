#include "CEnemy.h"
#include "CScene.h"

/*
�G�̍��G�͈�
*/
//bool CEnemy::SearchCollision(CCharcter*player, CCharcter*enemy){
//	CVector2 Search = player->mPosition - enemy->mPosition;
//	if (Search.Length() < player->mSearch + enemy->mSearch){
//		return true;
//	}
//	return false;
//}


void  CEnemy::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		mAttackInterval--;
		//�G�̕����A�ҋ@�A�j���[�V�������s������
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

			if (mVelocityX < 0){
				if (!mIce)
					mVelocityX += ENEMY_VELOCITY_X2;
				else
					mVelocityX += ENEMY_VELOCITY_X2_ICE;
			}
			else if (mVelocityX > 0){
				if (!mIce)
					mVelocityX -= ENEMY_VELOCITY_X2;
				else
					mVelocityX -= ENEMY_VELOCITY_X2_ICE;
			}
			mAttackInterval2 = ATTACK_INTERVAL2;
			break;

		case EENEMYANI::EYOYO:
			mAttackInterval2--;
			//�G�����[���[�𔭎˂��Ă��Ȃ���΁A���[���[�𔭎˂��ď������s��
			if (!mpEWeapon){
				if (mAttackInterval < 0){
					if (mAttackInterval2 < 0){
						mAttackInterval = ATTACK_INTERVAL;
						//�G�̃��[���[��G�̈ʒu���������O�ɌĂяo��
						mpEWeapon = new CWeapon(EEWEAPON, mPosition, mDirection);

						if (mDirection)		//�G���E�������Ă��鎞�ɂ͉E�Ƀ��[���[��i�܂���
							mpEWeapon->mPosition.x += 10;

						else				//�G�����������Ă��鎞�ɂ͍��Ƀ��[���[��i�܂���
							mpEWeapon->mPosition.x -= 10;
					}
				}
			}
			//�G�̃��[���[�����˂��ꂽ���̏������s��
			else {
				if (mpEWeapon->mLife < 0){
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
			//���[���[�̏����I��
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
		if (mVelocityX < ENEMY_VELOCITY_X2_ICE && mVelocityX > -ENEMY_VELOCITY_X2_ICE)
			mVelocityX = 0.0f;
		Gravity();
	}
	CRectangle::Update();
}
bool CEnemy::Collision(CRectangle*p){
	if (p->GetEnabled()) {
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EPWEAPON:
				if (enemy_ani != EENEMYANI::EDAMAGE && enemy_ani != EENEMYANI::EDOWN){
						enemy_ani = EENEMYANI::EDAMAGE;
						new CMapJewelry(p->mPosition);
					mVelocityX = 0.0f;
					enemy_ani_count = 0;
				}

				break;
				
			case EICE:
				mIce = true;

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
			case ESEARCH:
			case ESWITCH:
			case ESIGN:
			case EENDSIGN:
			case EBOSSROOM:
			case EJEWELRY:
			case EJEWELRY2:
			case ECHECKPOINT:
			case EPLAYER:
			case EEWEAPON:
				break;

			default:
				//�E��
				if (!(p->mColFlg & EDT_RIGHT)) {
					if (aj.x > 0) {
						mPosition.x = mPosition.x + aj.x;
						enemy_ani = EENEMYANI::EIDOL;
					}
				}
				//����
				if (!(p->mColFlg & EDT_LEFT)) {
					if (aj.x < 0) {
						mPosition.x = mPosition.x + aj.x;
						enemy_ani = EENEMYANI::EIDOL;
					}
				}
				//����
				if (!(p->mColFlg & EDT_BOTTOM)) {
					if (aj.y < 0) {
						mPosition.y = mPosition.y + aj.y;
						mVelocityY = 0.0f;
					}
				}
				//���
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
			if (!mDirection)	//������
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//������
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//������
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
		}
		break;
	case EENEMYANI::ETURN:
	case EENEMYANI::EJUMP:
	case EENEMYANI::EWALK:
		if (enemy_ani_count > 7)
			enemy_ani_count = 0;

		ENEMY_ANI_COUNT_FLAME = 4;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//������
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//������
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//������
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 128, 0, mAlpha);
			else				//�E����
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 128, 0, mAlpha);
		}
		break;

	case EENEMYANI::EYOYO:
		if (mpEWeapon != NULL){
			if (mDirection)
				//���[���[�̕R
				mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_R, 1.0f);

			else
				//���[���[�̕R
				mpEWeapon->mTexYoyo.DrawImage(ESTRING_UV_L, 1.0f);
		}
		if (mpEWeapon){
			if (enemy_ani_count > 1)
				enemy_ani_count = 1;

			ENEMY_ANI_COUNT_FLAME = 12;

			if (mTag == ECELLNUM::EENEMY1){
				if (!mDirection)	//������
					mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//�E����
					mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY2){
				if (!mDirection)	//������
					mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//�E����
					mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY3){
				if (!mDirection)	//������
					mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 256, 128, mAlpha);
				else				//�E����
					mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 256, 128, mAlpha);
			}
		}
		else{
			if (enemy_ani_count > 0)
				enemy_ani_count = 0;

			ENEMY_ANI_COUNT_FLAME = 0;

			if (mTag == ECELLNUM::EENEMY1){
				if (!mDirection)	//������
					mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//�E����
					mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY2){
				if (!mDirection)	//������
					mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//�E����
					mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}

			if (mTag == ECELLNUM::EENEMY3){
				if (!mDirection)	//������
					mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 2 * 128, (2 + 1) * 128, 128, 0, mAlpha);
				else				//�E����
					mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (2 + 1) * 128, 2 * 128, 128, 0, mAlpha);
			}
		}
		break;

	case EENEMYANI::EDAMAGE:

		ENEMY_ANI_COUNT_FLAME = 6;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//������
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//�E����
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//������
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//�E����
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//������
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 384, 256, mAlpha);
			else				//�E����
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 384, 256, mAlpha);
		}

		if (enemy_ani_count > 1)
			enemy_ani = EENEMYANI::EDOWN;

		break;

	case EENEMYANI::EDOWN:
		if (enemy_ani_count > 0)
			enemy_ani_count = 0;

		ENEMY_ANI_COUNT_FLAME = 0;

		if (mTag == ECELLNUM::EENEMY1){
			if (!mDirection)	//������
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 128, 512, 384, mAlpha);
			else				//�E����
				mTexEnemy01.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (0 + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY2){
			if (!mDirection)	//������
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 512, 384, mAlpha);
			else				//�E����
				mTexEnemy02.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
		}

		if (mTag == ECELLNUM::EENEMY3){
			if (!mDirection)	//������
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, enemy_ani_count * 128, (enemy_ani_count + 1) * 128, 512, 384, mAlpha);
			else				//�E����
				mTexEnemy03.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, (enemy_ani_count + 1) * 128, enemy_ani_count * 128, 512, 384, mAlpha);
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