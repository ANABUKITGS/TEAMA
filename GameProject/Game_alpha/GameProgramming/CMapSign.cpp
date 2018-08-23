#include "CMapSign.h"
#include "CMapBackImage.h"

CMapEndSign *CMapEndSign::mpEndSign = 0;
CMapBossRoomSign *CMapBossRoomSign::mpBossRoomSign = 0;

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
		mTexSign.DrawImage(SIGN_UV, 1.0f);

	else
		mTexSign.DrawImage(SIGN_UV, 0.5f);
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
	if (CMapBackImage::mFade == CMapBackImage::EFADE_NUM::EFALSE && CMapBackImage::mMapfile == CMapBackImage::EGAMEMAP_NUM::ETUTORIAL){
		// 当たっているか
		if (r->mTag == EPLAYER){
			if (CRectangle::Collision(r)){
				CMapBackImage::mMapfile = CMapBackImage::EGAMEMAP_NUM::EMAIN;
				CMapBackImage::mFade = CMapBackImage::EFADE_NUM::EFADEOUT;
				return true;
			}
		}
	}
	return false;
}

void CMapEndSign::Render(){
	mTexEndSign.DrawImage(SIGN_UV, 1.0f);
}

//ボスの部屋 看板
void CMapBossRoomSign::Update() {
	CMapChip::Update();
}

bool CMapBossRoomSign::Collision(CRectangle *r) {
	// 当たっているか
	if (r->mTag == EPLAYER){
		if (mColFlg){
			CVector2 aj;
			if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
				//左
				if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
				//右
				if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
			}
		}
		else{
			if (CRectangle::Collision(r) && r->mPosition.x > mPosition.x){
				mColFlg = true;
				return true;
			}
		}
	}
	return false;
}

void CMapBossRoomSign::Render(){
	mTexBossRoomSign.DrawImage(SIGN_UV, 1.0f);
}