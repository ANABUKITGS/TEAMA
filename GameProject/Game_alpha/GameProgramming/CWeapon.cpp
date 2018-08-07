#include "CWeapon.h"
#include "CPlayerT.h"
void CWeapon::Update(){
	mRotation+=5;			//毎フレーム5ずつ回転させる
	mLife--;
	if (mLife > 0){
		if (mLife > 15){	//生存時間が15以上
			if (mDirection)	//右向き
				mVelocity = WEAPOM_VELOCITY;
			else            //左向き
				mVelocity = -WEAPOM_VELOCITY;
		}
		else{				//生存時間が15以下
			if (mDirection)	//右向き
				mVelocity = -WEAPOM_VELOCITY;
			else            //左向き
				mVelocity = WEAPOM_VELOCITY;
		}
		mPosition.x += mVelocity;
		

	}
	else                    //生存時間が0以下
		mEnabled = false;	
	
	CRectangle::Update();

}
void CWeapon::Render(){
	CRectangle::Render();
}