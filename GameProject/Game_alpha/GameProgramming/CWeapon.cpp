#include "CWeapon.h"
#include "CPlayerT.h"
void CWeapon::Update(){
	mRotation+=5;
	mLife--;
	if (mLife > 0){
		if (mLife > 15){
			if (mDirection)
				mVelocity = WEAPOM_VELOCITY;
			else
				mVelocity = -WEAPOM_VELOCITY;
		}
		else{
			if (mDirection)
				mVelocity = -WEAPOM_VELOCITY;
			else
				mVelocity = WEAPOM_VELOCITY;
		}
		mPosition.x += mVelocity;
		

	}
	else
		mEnabled = false;
	
	CRectangle::Update();

}
void CWeapon::Render(){
	CRectangle::Render();
}