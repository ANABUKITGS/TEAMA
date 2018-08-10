#include "CMapSwitchGround.h"

int CMapSwitchGround::mNumber;

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
		if (r->mTag == EPWEAPON && !mCollision) {
			if (CMapSwitchGround::mNumber == 0)
				CMapSwitchGround::mNumber = 1;
			else
				CMapSwitchGround::mNumber = 0;
			return true;
			mCollision = true;
		}
	}
	mCollision = false;
	return false;
}