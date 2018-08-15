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
			if (lostcount == CHIKUWA_FALLING_TIME + 1)
				mSoundChikuwa.Play();
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
	if (r->mTag == ECELLNUM::EPLAYER ||
		r->mTag == ECELLNUM::EENEMY1 ||
		r->mTag == ECELLNUM::EENEMY2 ||
		r->mTag == ECELLNUM::EENEMY3 ||
		r->mTag == ECELLNUM::EBOSS){
		if (collision_flg &&
			(r->mTag == ECELLNUM::EENEMY1 ||
			r->mTag == ECELLNUM::EENEMY2 ||
			r->mTag == ECELLNUM::EENEMY3 ||
			r->mTag == ECELLNUM::EBOSS))
			return false;

		CVector2 aj;
		if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
			//ç∂
			if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
				return true;
			}
			//âE
			if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
				return true;
			}
			//â∫
			if (mPosition.y > r->mPosition.y) {
				r->mPosition.y =r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
			}
			//è„
			if (mPosition.y < r->mPosition.y) {
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = r->mVelocityY - aj.y;
				if (r->mTag == ECELLNUM::EPLAYER){
					collision_flg = true;
					CPlayerT::mpPlayer->mJumpCount = 0;
				}
			}
		}
	}
	return false;
}

void CMapChikuwa::Render(){
	//mTexChikuwa.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);
}