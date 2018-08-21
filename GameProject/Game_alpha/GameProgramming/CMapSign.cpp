#include "CMapSign.h"

void CMapSign::Update() {
	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// “–‚½‚Á‚Ä‚¢‚é‚©
	if (r->mTag == EPLAYER){
		if (CRectangle::Collision(r)){
			CText::ds = 0;
			mView = true;
			return true;
		}
		mView = false;
	}
	return false;
}

void CMapSign::Render(){
	if (!mView)
		mTexSignhoge.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);
}

void CMapTextView::Update(){

}

void CMapTextView::Render(){
	mTexTextView.DrawImage(TEXTVIEW_UV, 1.0f);
	CText::DrawStringW(DRAWSTRING_UV);
}