#include "CMapSign.h"
#include "CFade.h"
#include "CBossLifeBar.h"
#include "CBossGimmick.h"
#include "CBGM.h"

CMapEndSign *CMapEndSign::mpEndSign = 0;
CMapBossRoomSign *CMapBossRoomSign::mpBossRoomSign = 0;
bool CMapSign::mView = false;
bool CMapSign::mCol = false;
CMapTextView *CMapTextView::mpTextView = 0;
CMapTextView::SMapSign CMapTextView::mSignText[MAX_SIGN];
wchar_t CMapTextView::view_text_buf[MAX_PATH];
CMsgButton *CMsgButton::mpMsgButton = NULL;

//チュートリアル 看板
void CMapSign::Update() {
	if (mPosition.x > 0 * CELLSIZE)
		mSignTag = (mPosition.x / (10 * CELLSIZE));

	else
		mSignTag = NULL;

	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// 当たっているか
	if (mPosition.x <= CPlayerT::mpPlayer->mPosition.x + CELLSIZE * 2 && mPosition.x >= CPlayerT::mpPlayer->mPosition.x - CELLSIZE * 2){
		if (r->mTag == EPLAYER){
			if (CRectangle::Collision(r)){
				if (CMsgButton::mpMsgButton == NULL)
					CMsgButton::mpMsgButton = new CMsgButton(CPlayerT::mpPlayer->mPosition);
				mCol = true;
				if (!mOnceCol){
					mView = true;
				}

				if (mView)
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;

				CMapScroll::sign_scroll = true;
				CMapScroll::add_scroll = 0.0f;
				if (CMapTextView::mpTextView != NULL)
					CMapTextView::mpTextView->SignTag(mSignTag);

				if (CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE) || CKey::Once(VK_UP) || CKey::Once(VK_RETURN)){
					CSE::mSoundContinue.Play();
					if (!mView)
						mView = true;
					else{
						mView = false;
						mOnceCol = true;
					}
				}
				return true;
			}
			mCol = false;
			mView = false;
			CMapScroll::sign_scroll = false;
		}
	}
	return false;
}

void CMapSign::Render(){
	mTexSign.DrawImage(SIGN_UV, 1.0f);
}

//
void CMapTextView::Update(){
	if ((!CMapSign::mView && mpTextView != NULL) || CFade::mMapfile != CFade::EGAMEMAP_NUM::ETUTORIAL)
		mEnabled = false;
}

void CMapTextView::Render(){
	mTexTextView.DrawImageSetColor(TEXTVIEW_UV, BLACK, 0.5f);
	CText::DrawStringW(view_text_buf, CMapScroll::mpScroll->mPosition.x - 256, CMapScroll::mpScroll->mPosition.y + 128 - 32, 32, 1.0f, 2);
}

void CMapTextView::SignTag(int msign_tag){
	if (msign_tag < MAX_SIGN && msign_tag >= 0)
		wcscpy(view_text_buf, mSignText[msign_tag].text_buf);
	else
		swprintf(view_text_buf, L"(null)");
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

					CPlayerT::mpPlayer->mMaxJewel = CPlayerT::mpPlayer->mJewel;
					CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;

					//HPバー 生成
					if (CBossLifeBar::mpBossLifeBar == NULL)
						CBossLifeBar::mpBossLifeBar = new CBossLifeBar();
					if (CBossLifeBar::mpBossLifeBar != NULL)
						CBossLifeBar::mpBossLifeBar->mScale.x = 0.0f;

					//落下ギミック 生成
					if (CBossGimmick::mpBossGimmick == NULL)
						CBossGimmick::mpBossGimmick = new CBossGimmick();
					CBGM::AllStop();
					CBGM::mSoundBoss.Repeat();
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

void CMsgButton::Update(){
	mPosition = CVector2(CPlayerT::mpPlayer->mPosition.x + 32, CPlayerT::mpPlayer->mPosition.y + 96);

	if (!CMapSign::mCol){
		if (mAlpha > 0.0f)
			mAlpha -= 0.1f;

		else if (mAlpha <= 0.0f){
			mAlpha = 0.0f;
			mEnabled = false;
			return;
		}
	}
	else{
		if (mAlpha < 1.0f)
			mAlpha += 0.1f;

		else if (mAlpha >= 1.0f)
			mAlpha = 1.0f;
	}
}

void CMsgButton::Render(){
	mTexButton.DrawImage(MSGBUTTON_UV, mAlpha);
}