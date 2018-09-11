#include "CScene.h"
#include "CScore.h"
#include "CGame2.h"
#include "CTime.h"
#include "CBGM.h"
#include "CSE.h"
#include "CFade.h"
#include "CCredit.h"

extern CEditer mEditer;
extern CGame mGame;
extern CGame2 mGame2;
extern CCharcter player;
extern CTitle mTitle;
extern CScore mScore;
extern CCredit mCredit;

#define TITLE_TEXT_POS(i) (mTitleNum[i].mPositionX - (((float)(mTitleNum[i].mSize) - 32) / 2) * (float)(mTitleNum[i].mTextSize)) - 192, mTitleNum[i].mPositionY - (mTitleNum[i].mSize - 32) / 2

void CTitle::Init(){
	cursor_num = CSceneChange::EGAME;
	//テクスチャを読み込む
	mTexTitle.Load(".//Data//Images//Title//Title.tga");
	mTitleNum[0].mPositionX = -112;
	mTitleNum[1].mPositionX = -80;
	mTitleNum[2].mPositionX = -80;
	mTitleNum[3].mPositionX = -80;
	mTitleNum[4].mPositionX = -128;
	mTitleNum[0].mTextSize = 7;
	mTitleNum[1].mTextSize = 5;
	mTitleNum[2].mTextSize = 5;
	mTitleNum[3].mTextSize = 5;
	mTitleNum[4].mTextSize = 8;
	for (int i = 0; i < 5; i++){
		mTitleNum[i].mPositionY = 0 - (i * 64);
		mTitleNum[i].mSize =32;
		mTitleNum[i].mAnimation= false;
		mTitleNum[i].mColor[0] = 1.0f; mTitleNum[i].mColor[1] = 1.0f; mTitleNum[i].mColor[2] = 1.0f;
	}
}

void CTitle::Update(){
	mTexTitle.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush(VK_DOWN) || CKey::OncePush('S')) && cursor_num < CSceneChange::ESIZE - 1){
		cursor_num++;
		CSE::mSoundSelect.Play();
	}


	if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::OncePush(VK_UP) || CKey::OncePush('W')) && cursor_num > CSceneChange::EGAME){
		cursor_num--;
		CSE::mSoundSelect.Play();
	}
	
	if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN) || CKey::Once(VK_SPACE)){
		CSE::mSoundContinue.Play();
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

		case CSceneChange::ECSCENECHANGE_NUM::ECREDIT:
			mCredit.Init();
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ECREDIT);
			break;

		default:
			break;
		}
	}
	if (CKey::Once(VK_ESCAPE)){
		CSE::mSoundContinue.Play();
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EEXIT);
	}

#ifdef _DEBUG
	if (CGamePad::Once(PAD_9))
		CText::DrawSppedReset();
#endif
	/*カーソル*/
	switch (cursor_num){
	case CSceneChange::ECSCENECHANGE_NUM::EGAME:
		//swprintf(cursor_buf, L"→");
		mTitleNum[0].mAnimation = true;
		mTitleNum[0].mColor[0] = 0.2f; mTitleNum[0].mColor[1] = 0.8f; mTitleNum[0].mColor[2] = 0.4f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		mTitleNum[4].mColor[0] = 1.0f; mTitleNum[4].mColor[1] = 1.0f; mTitleNum[4].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
		//swprintf(cursor_buf, L"\n→");
		mTitleNum[1].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 0.2f; mTitleNum[1].mColor[1] = 0.8f; mTitleNum[1].mColor[2] = 0.4f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		mTitleNum[4].mColor[0] = 1.0f; mTitleNum[4].mColor[1] = 1.0f; mTitleNum[4].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ECREDIT:
		mTitleNum[2].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 0.2f; mTitleNum[2].mColor[1] = 0.8f; mTitleNum[2].mColor[2] = 0.4f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		mTitleNum[4].mColor[0] = 1.0f; mTitleNum[4].mColor[1] = 1.0f; mTitleNum[4].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
		//swprintf(cursor_buf, L"\n\n\n→");
		mTitleNum[3].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 0.2f; mTitleNum[3].mColor[1] = 0.8f; mTitleNum[3].mColor[2] = 0.4f;
		mTitleNum[4].mColor[0] = 1.0f; mTitleNum[4].mColor[1] = 1.0f; mTitleNum[4].mColor[2] = 1.0f;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
		//swprintf(cursor_buf, L"\n\n→");
		mTitleNum[4].mAnimation = true;
		mTitleNum[0].mColor[0] = 1.0f; mTitleNum[0].mColor[1] = 1.0f; mTitleNum[0].mColor[2] = 1.0f;
		mTitleNum[1].mColor[0] = 1.0f; mTitleNum[1].mColor[1] = 1.0f; mTitleNum[1].mColor[2] = 1.0f;
		mTitleNum[2].mColor[0] = 1.0f; mTitleNum[2].mColor[1] = 1.0f; mTitleNum[2].mColor[2] = 1.0f;
		mTitleNum[3].mColor[0] = 1.0f; mTitleNum[3].mColor[1] = 1.0f; mTitleNum[3].mColor[2] = 1.0f;
		mTitleNum[4].mColor[0] = 0.2f; mTitleNum[4].mColor[1] = 0.8f; mTitleNum[4].mColor[2] = 0.4f;

		break;

	default:
		break;
	}
	Animation();
}

void CTitle::Render(){
	//CText::DrawStringWSetColor(cursor_buf, mTitleNum[0].mPositionX, mTitleNum[0].mPositionY, mTitleNum[0].mSize, mTitleNum[0].mColor[0], mTitleNum[0].mColor[1], mTitleNum[0].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(cursor_buf, mTitleNum[1].mPositionX, mTitleNum[1].mPositionY, mTitleNum[0].mSize, mTitleNum[1].mColor[0], mTitleNum[1].mColor[1], mTitleNum[1].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(cursor_buf, mTitleNum[2].mPositionX, mTitleNum[2].mPositionY, mTitleNum[0].mSize, mTitleNum[2].mColor[0], mTitleNum[2].mColor[1], mTitleNum[2].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(cursor_buf, mTitleNum[3].mPositionX, mTitleNum[3].mPositionY, mTitleNum[0].mSize, mTitleNum[3].mColor[0], mTitleNum[3].mColor[1], mTitleNum[3].mColor[2], 1.0f, 0);

	CText::DrawStringWSetColor(L"ゲームスタート", TITLE_TEXT_POS(0), mTitleNum[0].mSize, mTitleNum[0].mColor[0], mTitleNum[0].mColor[1], mTitleNum[0].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L"ランキング", TITLE_TEXT_POS(1), mTitleNum[1].mSize, mTitleNum[1].mColor[0], mTitleNum[1].mColor[1], mTitleNum[1].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L"クレジット", TITLE_TEXT_POS(2), mTitleNum[2].mSize, mTitleNum[2].mColor[0], mTitleNum[2].mColor[1], mTitleNum[2].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L"ゲーム終了", TITLE_TEXT_POS(3), mTitleNum[3].mSize, mTitleNum[3].mColor[0], mTitleNum[3].mColor[1], mTitleNum[3].mColor[2], 1.0f, 0);
	CText::DrawStringWSetColor(L"エディターモード", TITLE_TEXT_POS(4), mTitleNum[4].mSize, mTitleNum[4].mColor[0], mTitleNum[4].mColor[1], mTitleNum[4].mColor[2], 1.0f, 0);
}

void CTitle::Animation(){
	for (int i = 0; i < 5; i++){
		if (mTitleNum[i].mAnimation){
			mTitleNum[i].mAnimationTime--;
			if (mTitleNum[i].mAnimationTime>15)
				mTitleNum[i].mSize += 1;
			else if (mTitleNum[i].mAnimationTime > 1)
				mTitleNum[i].mSize -= 1;
			else if (mTitleNum[i].mAnimationTime < 0){
				mTitleNum[i].mAnimationTime = 30;
				mTitleNum[i].mAnimation = false;
			}
		}
	}
}