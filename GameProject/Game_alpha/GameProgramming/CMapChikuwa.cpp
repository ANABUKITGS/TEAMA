#include "CMapChikuwa.h"

void CMapChikuwa::Update() {
	CMapChip::Update();
}

bool CMapChikuwa::Collision(CRectangle *r) {
	if (collision_flg){
		lostcount++;
		if (lostcount > CHIKUWA_FALLING_TIME && lostcount < CHIKUWA_LOST_TIME){
			mFalling += FALLING_SPEED;
			mPosition.y -= mFalling;
		}

		else if (lostcount > CHIKUWA_LOST_TIME){
			collision_flg = false;
			mPosition.y = setpos.y;
			mFalling = 0;
			lostcount = 0;
			return false;
		}
	}

	// ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	CVector2 aj;
	if (CRectangle::Collision(r) && CRectangle::Collision(CPlayerT::mpPlayer, &aj)) {
		//ç∂
		if (mPosition.x - CELLSIZE / 2 > CPlayerT::mpPlayer->mPosition.x) {
			CPlayerT::mpPlayer->mPosition.x = CPlayerT::mpPlayer->mPosition.x - aj.x;
			return true;
		}
		//âE
		if (mPosition.x + CELLSIZE / 2 < CPlayerT::mpPlayer->mPosition.x) {
			CPlayerT::mpPlayer->mPosition.x = CPlayerT::mpPlayer->mPosition.x - aj.x;
			return true;
		}
		//â∫
		if (mPosition.y > CPlayerT::mpPlayer->mPosition.y) {
			CPlayerT::mpPlayer->mPosition.y = CPlayerT::mpPlayer->mPosition.y - aj.y;
			CPlayerT::mpPlayer->mVelocityY = 0.0f;
		}
		//è„
		if (mPosition.y < CPlayerT::mpPlayer->mPosition.y) {
			collision_flg = true;
			CPlayerT::mpPlayer->mPosition.y = CPlayerT::mpPlayer->mPosition.y - aj.y;
			CPlayerT::mpPlayer->mJumpCount = 0;
			CPlayerT::mpPlayer->mVelocityY = 0.0f;
		}
	}
	return false;
}

void CMapChikuwa::Render(){
	//mTexChikuwa.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);
}