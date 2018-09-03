#include "CMapSign.h"
#include "CFade.h"
#include "CBossLifeBar.h"

CMapEndSign *CMapEndSign::mpEndSign = 0;
CMapBossRoomSign *CMapBossRoomSign::mpBossRoomSign = 0;
CMapSign::SMapSign CMapSign::mSignText[5];
bool CMapSign::mView = false;
CMapTextView *CMapTextView::mpTextView = 0;

//チュートリアル 看板
void CMapSign::Update() {
	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// 当たっているか
	if (r->mTag == EPLAYER){
		if (CRectangle::Collision(r)){
			mView = true;
			CMapScroll::scroll_flg = false;
			return true;
		}
		mView = false;
	}
	return false;
}

void CMapSign::Render(){
	mTexSign.DrawImage(SIGN_UV, 1.0f);
}

//
void CMapTextView::Update(){
	if (!CMapSign::mView && mpTextView != NULL)
		mEnabled = false;
}

void CMapTextView::Render(){
	mTexTextView.DrawImageSetColor(TEXTVIEW_UV, BLACK, 0.5f);
	CText::DrawStringW(L"[プレイヤーの そうさせつめい]\nＰ いどう\n１ ヨーヨー なげ\n２ ジャンプ\n３ ダッシュ\n９ チュートリアルを スキップ\n０ タイトルに もどる", CMapScroll::mpScroll->mPosition.x - 256, CMapScroll::mpScroll->mPosition.y + 128 - 32, 32, 1.0f, 2);
}

//チュートリアル 終了 看板
void CMapEndSign::Update() {
	CMapChip::Update();
}

bool CMapEndSign::Collision(CRectangle *r) {
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE && CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
		// 当たっているか
		if (r->mTag == ECELLNUM::EPLAYER){
			if (CRectangle::Collision(r)){
				CFade::mMapfile = CFade::EGAMEMAP_NUM::EMAIN;
				CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EGAME);
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
					if (CBossLifeBar::mpBossLifeBar == NULL)
						CBossLifeBar::mpBossLifeBar = new CBossLifeBar();

					if (CBossLifeBar::mpBossLifeBar != NULL)
						CBossLifeBar::mpBossLifeBar->mScale.x = 0.0f;
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