#include "CMapIce.h"
#include "CPlayerT.h"

void CMapIce::Update(){
	//CMapChip::Update();
}

bool CMapIce::Collision(CRectangle *r) {
	// ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	if (r->mTag == ECELLNUM::EPLAYER ||
		r->mTag == ECELLNUM::EENEMY1 ||
		r->mTag == ECELLNUM::EENEMY2 ||
		r->mTag == ECELLNUM::EENEMY3 ||
		r->mTag == ECELLNUM::EBOSS ||
		r->mTag == ECELLNUM::EBOX ||
		r->mTag == ECELLNUM::ESTEEL){

		CVector2 aj;
		if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
			//ç∂
			if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
			}
			//âE
			if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
			}
			//â∫
			if (mPosition.y > r->mPosition.y) {
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
			}
			//è„
			if (mPosition.y < r->mPosition.y) {
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
				r->mIce = true;
				if (r->mTag == ECELLNUM::EPLAYER){
					CPlayerT::mpPlayer->mJumpCount = 0;
				}
			}
			return true;
		}
	}
	return false;
}

void CMapIce::Render(){
	switch (texture_pos){
	case ETEXTURE_POSNUM::ELEFT:
		mTexMapIce.DrawImage(ICE_UV_L);
		break;

	case ETEXTURE_POSNUM::EONE:
	case ETEXTURE_POSNUM::ECENTER:
		mTexMapIce.DrawImage(ICE_UV_C);
		break;

	case ETEXTURE_POSNUM::ERIGHT:
		mTexMapIce.DrawImage(ICE_UV_R);
		break;

	default:
		break;
	}
}