#include "CMapSign.h"
#include "CFade.h"
#include "CBossLifeBar.h"

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
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE && CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
		// 当たっているか
		if (r->mTag == EPLAYER){
			if (CRectangle::Collision(r)){
				CFade::mMapfile = CFade::EGAMEMAP_NUM::EMAIN;
				CFade::mFade = CFade::EFADE_NUM::EFADEOUT;
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
	if (mColFlg){
		if (mTexPosY > -128)
			mTexPosY -= 8;

		if (mTexPosY <= -128)
			mTexPosY = -128;
	}
	else{
		mTexPosY = 0;
	}
	mScale.x = CELLSIZE / 2;
	CMapChip::Update();
}

bool CMapBossRoomSign::Collision(CRectangle *r) {
	// 当たっているか
	if (r->mTag == EPLAYER ||
		r->mTag == EENEMY1 ||
		r->mTag == EENEMY2 ||
		r->mTag == EENEMY3 ||
		r->mTag == EBOSS){
		if (mColFlg){
			CVector2 aj;
			if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
				//左
				if (mPosition.x - CELLSIZE / 2 >= r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					r->mVelocityX = 0.0f;
					return true;
				}
				//右
				if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					r->mVelocityX = 0.0f;
					return true;
				}
			}
		}
		else{
			if (r->mTag == EPLAYER && CRectangle::Collision(r) && r->mPosition.x > mPosition.x){
				CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL] = false;
				CMapScroll::scroll_stop = false;
				if (mPosition.x + CELLSIZE / 2 < r->mPosition.x && !mColFlg){
					mColFlg = true;
					CMapBossRoomSign::mpBossRoomSign->mScale.x = 0.0f;
					if (CBossLifeBar::mpBossLifeBar == NULL)
						CBossLifeBar::mpBossLifeBar = new CBossLifeBar();
					CPlayerT::mpPlayer->mMaxJewel = CPlayerT::mpPlayer->mJewel;
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
					return true;
				}
			}
		}
	}
	return false;
}

void CMapBossRoomSign::Render(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER)
		mTexBossRoomSign.DrawImage(BOSSROOM_SIGN_UV, 1.0f);

	else
		mTexBossRoomSign.DrawImage(BOSSROOM_SIGN_UV2, 0.5f);
}