#include "CMapSwitchGround.h"

ECELLNUM CMapSwitchGround::mNumber;

void CMapSwitchGround::Update() {
	CMapChip::Update();
}


//bool CMapSwitchGround::Collision(CRectangle *r) {
//	// “–‚½‚Á‚Ä‚¢‚é‚©
//	if (CRectangle::Collision(r)) {
//		//ƒvƒŒƒCƒ„[‚Ü‚½‚Í•Ší‚ÉÕ“Ë
//		if (r->mTag == EPLAYER || r->mTag == EPWEAPON) {
//			//–³Œø‚É‚·‚é
//			mEnabled = false;
//			return true;
//		}
//	}
//	return false;
//}


void CMapSwitch::Update() {
	CMapChip::Update();
}

bool CMapSwitch::Collision(CRectangle *r) {
	// “–‚½‚Á‚Ä‚¢‚é‚©
	if (CRectangle::Collision(r)) {
		//•Ší‚ÉÕ“Ë
		if (r->mTag == EPLAYER && !mCollision) {
			if (CMapSwitchGround::mNumber == ESWITCH_GROUND1)
				CMapSwitchGround::mNumber = ESWITCH_GROUND2;
			else
				CMapSwitchGround::mNumber = ESWITCH_GROUND1;
			mCollision = true;
			return true;
		}
	}
	mCollision = false;
	return false;
}