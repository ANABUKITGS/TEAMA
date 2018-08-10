#include "CMapBelt.h"

void CMapBelt::Update() {
	CMapChip::Update();
}

bool CMapBelt::Collision(CRectangle *r) {
	// �������Ă��邩
	CVector2 aj;
	if (CRectangle::Collision(r) && CRectangle::Collision(CPlayerT::mpPlayer, &aj)) {
		if (r->mTag == EPLAYER){
			//��
			if (texture_pos == 1 && mPosition.x - CELLSIZE / 2 > CPlayerT::mpPlayer->mPosition.x) {
				CPlayerT::mpPlayer->mPosition.x = CPlayerT::mpPlayer->mPosition.x - aj.x;
				return true;
			}
			//�E
			if (texture_pos == 3 && mPosition.x + CELLSIZE / 2 < CPlayerT::mpPlayer->mPosition.x) {
				CPlayerT::mpPlayer->mPosition.x = CPlayerT::mpPlayer->mPosition.x - aj.x;
				return true;
			}
			//��
			if (mPosition.y > CPlayerT::mpPlayer->mPosition.y) {
				CPlayerT::mpPlayer->mPosition.y = CPlayerT::mpPlayer->mPosition.y - aj.y;
				CPlayerT::mpPlayer->mVelocityY = 0.0f;
			}
			//��
			if (mPosition.y < CPlayerT::mpPlayer->mPosition.y) {
				if (mDirection == ECELLNUM::EBELTL)
					CPlayerT::mpPlayer->mPosition.x -= BELT_SPEED;

				else if (mDirection == ECELLNUM::EBELTR)
					CPlayerT::mpPlayer->mPosition.x += BELT_SPEED;
				CPlayerT::mpPlayer->mPosition.y = CPlayerT::mpPlayer->mPosition.y - aj.y;
				CPlayerT::mpPlayer->mJumpCount = 0;
				CPlayerT::mpPlayer->mVelocityY = 0.0f;
			}
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