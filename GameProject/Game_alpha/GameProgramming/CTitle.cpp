#include "CScene.h"
#include "CScore.h"
#include "CGame2.h"
#include "CTime.h"
#include "CBGM.h"
#include "CFade.h"

extern CEditer mEditer;
extern CGame mGame;
extern CGame2 mGame2;
extern CCharcter player;
extern CTitle mTitle;
extern CScore mScore;

void CTitle::Init(){
	cursor_num = CSceneChange::EGAME;
	//テクスチャを読み込む
	mTexTitle.Load(".//Data//Images//Title//Title.tga");
	for (int i = 0; i < 4; i++){
		mTitleNum[i].mPositionX = -200;
		mTitleNum[i].mPositionY = 0 - (i * 32);
		mTitleNum[i].mAnimation= false;
		mTitleNum[i].mColor[0] = 1.0f; mTitleNum[i].mColor[1] = 1.0f; mTitleNum[i].mColor[2] = 1.0f;
	}
}

void CTitle::Update(){
	mTexTitle.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush(VK_DOWN) || CKey::OncePush('S')) && cursor_num < CSceneChange::ESIZE - 1){
		cursor_num++;
	}


	if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::OncePush(VK_UP) || CKey::OncePush('W')) && cursor_num > CSceneChange::EGAME){
		cursor_num--;
	}
	
	if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN) || CKey::Once(VK_SPACE)){
		switch (cursor_num){
		case CSceneChange::ECSCENECHANGE_NUM::EGAME:
			CFade::mMapfile = CFade::EGAMEMAP_NUM::ETUTORIAL;
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EGAME);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERANKING);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
			mEditer.Init();
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EEDITER);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EEXIT);
			break;

		default:
			break;
		}
	}
	if(CKey::Once(VK_ESCAPE))
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EEXIT);

#ifdef _DEBUG
	if (CGamePad::Once(PAD_9))
		CText::DrawSppedReset();
#endif
	/*カーソル*/
	switch (cursor_num){
	case CSceneChange::ECSCENECHANGE_NUM::EGAME:
		//swprintf(cursor_buf, L"→");
		mTitleNum[0].mAnimation = true;
		mTitleNum[0].mColor[0] = 0.0f; mTitleNum[0].mColor[1] = 0.0f; mTitleNum[0].mColor[2] = 0.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
		//swprintf(cursor_buf, L"\n→");
		mTitleNum[1].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 0.0f; mTitleNum[1].mColor[1] = 0.0f; mTitleNum[1].mColor[2] = 0.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
		//swprintf(cursor_buf, L"\n\n→");
		mTitleNum[2].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 0.0f; mTitleNum[2].mColor[1] = 0.0f; mTitleNum[2].mColor[2] = 0.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
		//swprintf(cursor_buf, L"\n\n\n→");
		mTitleNum[3].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 0.0f; mTitleNum[3].mColor[1] = 0.0f; mTitleNum[3].mColor[2] = 0.0f;
		break;

	default:
		break;
	}
	Animation();
}

void CTitle::Render(){
	CText::DrawStringWSetColor(L" ゲームスタート", mTitleNum[0].mPositionX, mTitleNum[0].mPositionY, 32, mTitleNum[0].mColor[0], mTitleNum[0].mColor[1], mTitleNum[0].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(cursor_buf, mTitleNum[0].mPositionX, mTitleNum[0].mPositionY, 32, mTitleNum[0].mColor[0], mTitleNum[0].mColor[1], mTitleNum[0].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L" ランキング", mTitleNum[1].mPositionX, mTitleNum[1].mPositionY, 32, mTitleNum[1].mColor[0], mTitleNum[1].mColor[1], mTitleNum[1].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(cursor_buf, mTitleNum[1].mPositionX, mTitleNum[1].mPositionY, 32, mTitleNum[1].mColor[0], mTitleNum[1].mColor[1], mTitleNum[1].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L" ゲームしゅうりょう", mTitleNum[2].mPositionX, mTitleNum[2].mPositionY, 32, mTitleNum[2].mColor[0], mTitleNum[2].mColor[1], mTitleNum[2].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(cursor_buf, mTitleNum[2].mPositionX, mTitleNum[2].mPositionY, 32, mTitleNum[2].mColor[0], mTitleNum[2].mColor[1], mTitleNum[2].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L" エディター(かり)", mTitleNum[3].mPositionX, mTitleNum[3].mPositionY, 32, mTitleNum[3].mColor[0], mTitleNum[3].mColor[1], mTitleNum[3].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(cursor_buf, mTitleNum[3].mPositionX, mTitleNum[3].mPositionY, 32, mTitleNum[3].mColor[0], mTitleNum[3].mColor[1], mTitleNum[3].mColor[2], 1.0f, 0);
}

void CTitle::Animation(){
	for (int i = 0; i < 4; i++){
		if (mTitleNum[i].mAnimation){
			mTitleNum[i].mAnimationTime--;
			if (mTitleNum[i].mAnimationTime>15)
				mTitleNum[i].mPositionY += 0.5;
			else if (mTitleNum[i].mAnimationTime > 1)
				mTitleNum[i].mPositionY -= 0.5;
			else if (mTitleNum[i].mAnimationTime < 0){
				mTitleNum[i].mAnimationTime = 30;
				mTitleNum[i].mAnimation = false;
			}
		}
	}
}