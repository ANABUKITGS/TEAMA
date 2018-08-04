#include "CMapChip.h"

bool CMapChip::Collision(CRectangle *r) {
	if (mEnabled) {
		if (CRectangle::Collision(r)) {
			if (r->mTag == EPLAYER && mTag == EJEWELRY) {
				mEnabled = false;
				return true;
			}
		}
	}
	return false;
}

void CMapChip::Render() {
	if (mEnabled) {
		CRectangle::Render();
	}
}