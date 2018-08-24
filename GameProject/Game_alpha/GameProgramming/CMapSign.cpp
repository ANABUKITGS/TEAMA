#include "CMapSign.h"
#include "CFade.h"
#include "CBossLifeBar.h"

CMapEndSign *CMapEndSign::mpEndSign = 0;
CMapBossRoomSign *CMapBossRoomSign::mpBossRoomSign = 0;

//�`���[�g���A�� �Ŕ�
void CMapSign::Update() {
	CMapChip::Update();
}

bool CMapSign::Collision(CRectangle *r) {
	// �������Ă��邩
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

//�`���[�g���A�� �I�� �Ŕ�
void CMapEndSign::Update() {
	CMapChip::Update();
}

bool CMapEndSign::Collision(CRectangle *r) {
	if (CFade::mFade == CFade::EFADE_NUM::EFALSE && CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
		// �������Ă��邩
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

//�{�X�̕��� �Ŕ�
void CMapBossRoomSign::Update() {
	CMapChip::Update();
}

bool CMapBossRoomSign::Collision(CRectangle *r) {
	// �������Ă��邩
	if (r->mTag == EPLAYER){
		if (mColFlg){
			CVector2 aj;
			if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
				//��
				if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
				//�E
				if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
					r->mPosition.x = r->mPosition.x - aj.x;
					return true;
				}
			}
		}
		else{
			if (CRectangle::Collision(r) && r->mPosition.x > mPosition.x && !mColFlg){
				mColFlg = true;
				new CBossLifeBar();
				return true;
			}
		}
	}
	return false;
}

void CMapBossRoomSign::Render(){
	mTexBossRoomSign.DrawImage(SIGN_UV, 1.0f);
}