#include "CWeapon.h"
#include "CPlayerT.h"
#include "CEnemy.h"
void CWeapon::Update(){
	mRotation+=10;			//–ˆƒtƒŒ[ƒ€10‚¸‚Â‰ñ“]‚³‚¹‚é
	mLife--;
	if (mLife > 0){
		if (mLife > 20){	//¶‘¶ŽžŠÔ‚ª20‚ð’´‰ß
			if (mDirection)	//‰EŒü‚«
				mVelocity = WEAPOM_VELOCITY;
			else			//¶Œü‚«
				mVelocity = -WEAPOM_VELOCITY;
		}
		else{				//¶‘¶ŽžŠÔ‚ª15ˆÈ‰º
			if (mDirection)	//‰EŒü‚«
				mVelocity = -WEAPOM_VELOCITY;
			else			//¶Œü‚«
				mVelocity = WEAPOM_VELOCITY;
		}
		mPosition.x += mVelocity;


	}
	else{					//¶‘¶ŽžŠÔ‚ª0ˆÈ‰º
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
	if (mTag == ECELLNUM::EPWEAPON){
		if (mDirection)
			mTexYoyo.DrawImage(PSTRING_UV_R, 1.0f);

		else
			mTexYoyo.DrawImage(PSTRING_UV_L, 1.0f);
	}

	/*------ “G‚Ìƒˆ[ƒˆ[‚Ì•R‚Í CEnemy::Render()‚É‚ ‚é ------*/

	CRectangle::Render();
}

bool CWeapon::Collision(CRectangle *p){
	if (CRectangle::Collision(p)){
		/*if (mTag == EPWEAPON &&  !mJewel_flg && !mMiniJewel_flg && 
			(p->mTag == EENEMY1 || p->mTag == EENEMY2 || p->mTag == EENEMY3 || p->mTag == EJEWELRY)){
			mJewel_flg = true;
		}
		if (mTag == EPWEAPON && !mJewel_flg && !mMiniJewel_flg && p->mTag == EJEWELRY2){
			mMiniJewel_flg = true;
		}*/
		return true;
	}
	return false;
}