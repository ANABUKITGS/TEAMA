#include "CMapSign.h"

CMapEndSign::ETUTORIAL_END_NUM CMapEndSign::tutorial_end = ETUTORIAL_END_NUM::EFALSE;

//チュートリアル 看板
void CMapSign::Update() {
	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// 当たっているか
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
	if (mView)
		mTexSign.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 1.0f);

	else
		mTexSign.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64, 0, 0.5f);
}

//
void CMapTextView::Update(){

}

void CMapTextView::Render(){
	mTexTextView.DrawImage(TEXTVIEW_UV, 1.0f);
	CText::DrawStringW(DRAWSTRING_UV);
}

//チュートリアル 終了 看板
void CMapEndSign::Update() {
	CMapChip::Update();
}

bool CMapEndSign::Collision(CRectangle *r) {
	if (tutorial_end == ETUTORIAL_END_NUM::EFALSE){
		// 当たっているか
		if (r->mTag == EPLAYER){
			if (CRectangle::Collision(r)){
				tutorial_end = ETUTORIAL_END_NUM::EFADEOUT;
				return true;
			}
		}
	}
	return false;
}

void CMapEndSign::Render(){
	mTexEndSign.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0, 1.0f);
}

//ボスの部屋 看板
void CMapBossRoomSign::Update() {
	CMapChip::Update();
}

bool CMapBossRoomSign::Collision(CRectangle *r) {
	// 当たっているか
	if (r->mTag == EPLAYER){
		if (CRectangle::Collision(r)){
			return true;
		}
	}
	return false;
}

void CMapBossRoomSign::Render(){
	mTexBossRoomSign.DrawImage(mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0, 1.0f);
}