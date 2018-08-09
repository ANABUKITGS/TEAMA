#include "CMapBelt.h"

void CMapBelt::Update() {
	CMapChip::Update();
}

bool CMapBelt::Collision(CRectangle *r) {
	//if (collision_flg){
	//	lostcount++;
	//	if (lostcount > CHIKUWA_FALLING_TIME && lostcount < CHIKUWA_LOST_TIME){
	//		mFalling += FALLING_SPEED;
	//		mPosition.y -= mFalling;
	//	}

	//	else if (lostcount > CHIKUWA_LOST_TIME){
	//		collision_flg = false;
	//		mPosition.y = setpos.y;
	//		mFalling = 0;
	//		lostcount = 0;
	//		return false;
	//	}
	//}

	// “–‚½‚Á‚Ä‚¢‚é‚©
	CVector2 aj;
	if (CRectangle::Collision(r) && CRectangle::Collision(CPlayerT::mpPlayer, &aj)) {
		if (r->mTag == EPLAYER){
			if (mDirection == ECELLNUM::EBELTL)
				CPlayerT::mpPlayer->mPosition.x -= BELT_SPEED;
			else if (mDirection == ECELLNUM::EBELTR)
				CPlayerT::mpPlayer->mPosition.x += BELT_SPEED;
			CPlayerT::mpPlayer->mPosition = CPlayerT::mpPlayer->mPosition - aj;
			CPlayerT::mpPlayer->mJumpCount = 0;
			CPlayerT::mpPlayer->mVelocityY = 0.0f;
			return true;
		}
	}
	return false;
}

void CMapBelt::Render(){
	mRender = false;
	switch (texture_pos){
	case 1:
		mTexBelt.DrawImage(BELT_UV1L);
		break;

	case 2:
		mTexBelt.DrawImage(BELT_UV2);
		break;

	case 3:
		mTexBelt.DrawImage(BELT_UV1R);
		break;

	default:
		break;
	}
}