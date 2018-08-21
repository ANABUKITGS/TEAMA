#include "CMapSign.h"

void CMapSign::Update() {
	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// “–‚½‚Á‚Ä‚¢‚é‚©
	if (CRectangle::Collision(r)) {
		if (r->mTag == EPLAYER)
			mTextbox = true;
			return true;
	}
	mTextbox = false;
	return false;
}

void CMapSign::Render(){
	mRender = false;
	if (!mTextbox)
		mTexSignhoge.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);
}