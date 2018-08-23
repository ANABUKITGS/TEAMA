#include "CMapBelt.h"
#include "CMapBox.h"
#include "CMapSteel.h"

void CMapBelt::Update() {
	CMapChip::Update();
}

bool CMapBelt::Collision(CRectangle *r) {
	// ìñÇΩÇ¡ÇƒÇ¢ÇÈÇ©
	if (r->mTag == ECELLNUM::EPLAYER ||
		r->mTag == ECELLNUM::EENEMY1 ||
		r->mTag == ECELLNUM::EENEMY2 ||
		r->mTag == ECELLNUM::EENEMY3 |
		r->mTag == ECELLNUM::EBOSS ||
		r->mTag == ECELLNUM::EBOX ||
		r->mTag == ECELLNUM::ESTEEL){

		CVector2 aj;
		if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
			//ç∂
			if (texture_pos == 1 && mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
				return true;
			}
			//âE
			if (texture_pos == 3 && mPosition.x + CELLSIZE /2 < r->mPosition.x) {
				r->mPosition.x = r->mPosition.x - aj.x;
				return true;
			}
			//â∫
			if (mPosition.y > r->mPosition.y) {
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
			}
			//è„
			if (mPosition.y < r->mPosition.y) {
				if (mDirection == ECELLNUM::EBELTL)
					r->mPosition.x -= BELT_SPEED;

				else if (mDirection == ECELLNUM::EBELTR)
					r->mPosition.x += BELT_SPEED;
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
				if (r->mTag == ECELLNUM::EPLAYER)
					CPlayerT::mpPlayer->mJumpCount = 0;
			}
			return true;
		}
	}
	return false;
}

void CMapBelt::Render(){
	switch (texture_pos){
	case ETEXTURE_POSNUM::ELEFT:
		mTexBelt.DrawImage(BELT_UV1L);
		break;

	case ETEXTURE_POSNUM::ECENTER:
		mTexBelt.DrawImage(BELT_UV2);
		break;

	case ETEXTURE_POSNUM::ERIGHT:
		mTexBelt.DrawImage(BELT_UV1R);
		break;

	case ETEXTURE_POSNUM::EONE:
		mTexBelt.DrawImage(BELT_UV3);
		break;

	default:
		break;
	}
}

void CMapBeltSign::Update(){
	CRectangle::Update();
	switch (mDirection){
	case ECELLNUM::EBELTL:
		mRotation += BELT_SPEED;
		break;

	case ECELLNUM::EBELTR:
		mRotation -= BELT_SPEED;
		break;

	default:
		break;
	}
}

void CMapBeltSign::Render(){
	CRectangle::Render();
}