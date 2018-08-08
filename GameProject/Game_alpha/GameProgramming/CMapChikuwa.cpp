#include "CMapChikuwa.h"

void CMapChikuwa::Update() {
	CMapChip::Update();
}

bool CMapChikuwa::Collision(CRectangle *r) {
	CVector2 aj;

	if (collision_flg){
		lostcount++;
		if (lostcount > CHIKUWA_LOSTTIME){
			mEnabled = false;
			collision_flg = false;
			return false;
		}
	}

	// “–‚½‚Á‚Ä‚¢‚é‚©
	if (CRectangle::Collision(r) && CRectangle::Collision(this, &aj)) {
		if (r->mTag == EPLAYER){
			collision_flg = true;
			//CPlayerT::mpPlayer->mPosition = CPlayerT::mpPlayer->mPosition - aj;
			CPlayerT::mpPlayer->mJumpCount = 0;
			CPlayerT::mpPlayer->mVelocityY = 0.0f;
			return true;
		}
	}
	return false;
}

void CMapChikuwa::Render(){
	mTexChikuwa.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);
}