#include "CWeapon.h"
#include "CPlayerT.h"
#include "CEnemy.h"
#include "CBoss.h"
void CWeapon::Update(){
	mRotation += 10;			//毎フレーム10ずつ回転させる
	mLife--;
	if (mLife > 0){	//生存時間が20を超過
		if (mDirection)	//右向き
			mVelocity = WEAPOM_VELOCITY;
		else			//左向き
			mVelocity = -WEAPOM_VELOCITY;
	}
	else{				//生存時間が15以下
		if (mDirection)	//右向き
			mVelocity = -WEAPOM_VELOCITY;
		else			//左向き
			mVelocity = WEAPOM_VELOCITY;
	}
	mPosition.x += mVelocity;
	if (mDirection){
		if (mPosition.x < mPosInit.x){
			mReturn = true;
			mEnabled = false;
			if (CPlayerT::player_ani != CPlayerT::EPLAYERANI::EDOWN){
				if (CPlayerT::mpPlayer->mAir)
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
				else
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
				CPlayerT::mpPlayer->player_ani_count = 0;
				CPlayerT::mpPlayer->player_ani_count_frame = 0;
			}
		}
	}
	else{
		if (mPosition.x > mPosInit.x){
			mReturn = true;
			mEnabled = false;
			if (CPlayerT::player_ani != CPlayerT::EPLAYERANI::EDOWN){
				if (CPlayerT::mpPlayer->mAir)
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
				else
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
				CPlayerT::mpPlayer->player_ani_count = 0;
				CPlayerT::mpPlayer->player_ani_count_frame = 0;
			}
		}
	}

	CRectangle::Update();

}
void CWeapon::Render(){
	if (mTag == ECELLNUM::EPWEAPON){
		if (mDirection)
			mTexYoyo.DrawImage(PSTRING_UV_R, 1.0f);

		else
			mTexYoyo.DrawImage(PSTRING_UV_L, 1.0f);
	}

	/*------ 敵のヨーヨーの紐は CEnemy::Render()にある ------*/

	CRectangle::Render();
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		switch (mTag){
		case EPWEAPON:
			switch (p->mTag){
			case EENEMY1:
			case EENEMY2:
			case EENEMY3:
				if (p->mAlpha < 1)
					break;
			case EBOSS:
				if (CBoss::mpBoss != NULL && CBoss::mpBoss->mAttackBehavior != CBoss::AttackBehavior::EDOWN)
					mLife = 0;
				break;

			case EJEWELRY:
			case EJEWELRY2:
			case EBOX:
			case ESTEEL:
			case ESWITCH:
			mLife = 0;
				break;

			default:
				break;
			}
			break;
		case EEWEAPON:
		case EBWEAPON:
			if (p->mTag == EBOX || p->mTag == ESTEEL || p->mTag == EPLAYER)
				mLife = 0;
			break;

		default:
			break;
		}
		
		return true;
	}
	return false;
}