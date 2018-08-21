#include "CWeapon.h"
#include "CPlayerT.h"



void CWeapon::Update(){
	mRotation+=10;			//毎フレーム10ずつ回転させる
	mLife--;
	if (mLife > 0){
		if (mLife > 20){	//生存時間が20を超過
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

	}
	else{					//生存時間が0以下
		mEnabled = false;
		if (CPlayerT::mpPlayer->mAir)
			CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EJUMP;
		else
			CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
		CPlayerT::mpPlayer->player_ani_count = 0;
		CPlayerT::mpPlayer->player_ani_count_flame = 0;
	}
	CRectangle::Update();

}
void CWeapon::Render(){
	CRectangle::Render();
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		if (mTag == EPWEAPON &&  !mJewel_flg && !mMiniJewel_flg && 
			(p->mTag == EENEMY1 || p->mTag == EENEMY2 || p->mTag == EENEMY3 || p->mTag == EJEWELRY)){
			mJewel_flg = true;
		}
		if (mTag == EPWEAPON && !mJewel_flg && !mMiniJewel_flg && p->mTag == EJEWELRY2){
			mMiniJewel_flg = true;
		}
		return true;
	}
	return false;
}