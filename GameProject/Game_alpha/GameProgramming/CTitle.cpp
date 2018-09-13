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
	mTexRanking.Load(".//Data//Images//Title//ranking.tga");
	mTexStart.Load(".//Data//Images//Title//gamestart.tga");
	mTexCredit.Load(".//Data//Images//Title//credit.tga");
	mTexEnd.Load(".//Data//Images//Title//quitgame.tga");
	mTexEdit.Load(".//Data//Images//Title//editermode.tga");
	mTitleNum[0].mTextSize.x = 296.0f;
	mTitleNum[1].mTextSize.x = 212.0f;
	mTitleNum[2].mTextSize.x = 173.0f;
	mTitleNum[3].mTextSize.x = 256.0f;
	mTitleNum[4].mTextSize.x = 308.0f;

	mTitleNum[0].mSize[0] = -252 - (mTitleNum[0].mTextSize.x * 0.375f); mTitleNum[0].mSize[1] = -252 + (mTitleNum[0].mTextSize.x * 0.375f);
	mTitleNum[1].mSize[0] = -252 - (mTitleNum[1].mTextSize.x * 0.375f); mTitleNum[1].mSize[1] = -252 + (mTitleNum[1].mTextSize.x * 0.375f);
	mTitleNum[2].mSize[0] = -252 - (mTitleNum[2].mTextSize.x * 0.375f); mTitleNum[2].mSize[1] = -252 + (mTitleNum[2].mTextSize.x * 0.375f);
	mTitleNum[3].mSize[0] = -252 - (mTitleNum[3].mTextSize.x * 0.375f); mTitleNum[3].mSize[1] = -252 + (mTitleNum[3].mTextSize.x * 0.375f);
	mTitleNum[4].mSize[0] = -252 - (mTitleNum[4].mTextSize.x * 0.375f); mTitleNum[4].mSize[1] = -252 + (mTitleNum[4].mTextSize.x * 0.375f);
	for (int i = 0; i < 5; i++){
		mTitleNum[i].mSize[2] = -64 - (i * 64);
		mTitleNum[i].mSize[3] = -16 - (i * 64);
		mTitleNum[i].mAnimation= false;
	}
#if _DEBUG
	mEditerMode = 1;
#else
	mEditerMode = 2;
#endif
}

void CTitle::Update(){
	mTexTitle.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush(VK_DOWN) || CKey::OncePush('S')) && cursor_num < CSceneChange::ESIZE - mEditerMode){
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

#if _DEBUG
	if (CGamePad::Once(PAD_9))
		CText::DrawSppedReset();
#else
	if (CGamePad::Push(PAD_11) && CGamePad::Once(PAD_12)){
		CSE::mSoundSwitch.Play();
		if (mEditerMode == 1){
			mEditerMode = 2;
			if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::EEDITER)
				cursor_num = CSceneChange::ECSCENECHANGE_NUM::EEXIT;
		}
		else
			mEditerMode = 1;
	}
#endif

	/*カーソル*/
	switch (cursor_num){
	case CSceneChange::ECSCENECHANGE_NUM::EGAME:
		//swprintf(cursor_buf, L"→");
		mTitleNum[0].mAnimation = true;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
		//swprintf(cursor_buf, L"\n→");
		mTitleNum[1].mAnimation = true;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ECREDIT:
		mTitleNum[2].mAnimation = true;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
		//swprintf(cursor_buf, L"\n\n\n→");
		mTitleNum[3].mAnimation = true;
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
		//swprintf(cursor_buf, L"\n\n→");
		mTitleNum[4].mAnimation = true;

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

	//CText::DrawStringWSetColor(L"ゲームスタート", TITLE_TEXT_POS(0), mTitleNum[0].mSize, mTitleNum[0].mColor[0], mTitleNum[0].mColor[1], mTitleNum[0].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(L"ランキング", TITLE_TEXT_POS(1), mTitleNum[1].mSize, mTitleNum[1].mColor[0], mTitleNum[1].mColor[1], mTitleNum[1].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(L"クレジット", TITLE_TEXT_POS(2), mTitleNum[2].mSize, mTitleNum[2].mColor[0], mTitleNum[2].mColor[1], mTitleNum[2].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(L"ゲーム終了", TITLE_TEXT_POS(3), mTitleNum[3].mSize, mTitleNum[3].mColor[0], mTitleNum[3].mColor[1], mTitleNum[3].mColor[2], 1.0f, 0);
	//CText::DrawStringWSetColor(L"エディターモード", TITLE_TEXT_POS(4), mTitleNum[4].mSize, mTitleNum[4].mColor[0], mTitleNum[4].mColor[1], mTitleNum[4].mColor[2], 1.0f, 0);

	if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::EGAME)
		mTexStart.DrawImageSetColor(mTitleNum[0].mSize[0], mTitleNum[0].mSize[1], mTitleNum[0].mSize[2], mTitleNum[0].mSize[3], 0, 296, 64, 0, GREEN, 1.0f);
	else
		mTexStart.DrawImageSetColor(mTitleNum[0].mSize[0], mTitleNum[0].mSize[1], mTitleNum[0].mSize[2], mTitleNum[0].mSize[3], 0, 296, 64, 0, WHITE, 1.0f);

	if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::ERANKING)
		mTexRanking.DrawImageSetColor(mTitleNum[1].mSize[0], mTitleNum[1].mSize[1], mTitleNum[1].mSize[2], mTitleNum[1].mSize[3], 0, 212, 64, 0, GREEN, 1.0f);
	else 
		mTexRanking.DrawImageSetColor(mTitleNum[1].mSize[0], mTitleNum[1].mSize[1], mTitleNum[1].mSize[2], mTitleNum[1].mSize[3], 0, 212, 64, 0, WHITE, 1.0f);

	if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::ECREDIT)
		mTexCredit.DrawImageSetColor(mTitleNum[2].mSize[0], mTitleNum[2].mSize[1], mTitleNum[2].mSize[2], mTitleNum[2].mSize[3], 0, 173, 64, 0, GREEN, 1.0f);
	else
		mTexCredit.DrawImageSetColor(mTitleNum[2].mSize[0], mTitleNum[2].mSize[1], mTitleNum[2].mSize[2], mTitleNum[2].mSize[3], 0, 173, 64, 0, WHITE, 1.0f);

	if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::EEXIT)
		mTexEnd.DrawImageSetColor(mTitleNum[3].mSize[0], mTitleNum[3].mSize[1], mTitleNum[3].mSize[2], mTitleNum[3].mSize[3], 0, 256, 64, 0, GREEN, 1.0f);
	else
		mTexEnd.DrawImageSetColor(mTitleNum[3].mSize[0], mTitleNum[3].mSize[1], mTitleNum[3].mSize[2], mTitleNum[3].mSize[3], 0, 256, 64, 0, WHITE, 1.0f);

	if (mEditerMode == 1){
		if (cursor_num == CSceneChange::ECSCENECHANGE_NUM::EEDITER)
			mTexEdit.DrawImageSetColor(mTitleNum[4].mSize[0], mTitleNum[4].mSize[1], mTitleNum[4].mSize[2], mTitleNum[4].mSize[3], 0, 308, 64, 0, GREEN, 1.0f);
		else
			mTexEdit.DrawImageSetColor(mTitleNum[4].mSize[0], mTitleNum[4].mSize[1], mTitleNum[4].mSize[2], mTitleNum[4].mSize[3], 0, 308, 64, 0, WHITE, 1.0f);
	}
}

void CTitle::Animation(){
	for (int i = 0; i < 5; i++){
		if (mTitleNum[i].mAnimation){
			mTitleNum[i].mAnimationTime--;
			if (mTitleNum[i].mAnimationTime>15){
				mTitleNum[i].mSize[0] -= mTitleNum[i].mTextSize.x * 0.01f;
				mTitleNum[i].mSize[1] += mTitleNum[i].mTextSize.x * 0.01f;
				mTitleNum[i].mSize[2] -= 64 * 0.01f;
				mTitleNum[i].mSize[3] += 64 * 0.01f;
			}
			else if (mTitleNum[i].mAnimationTime > 1){
				mTitleNum[i].mSize[0] += mTitleNum[i].mTextSize.x * 0.01f;
				mTitleNum[i].mSize[1] -= mTitleNum[i].mTextSize.x * 0.01f;
				mTitleNum[i].mSize[2] += 64 * 0.01f;
				mTitleNum[i].mSize[3] -= 64 * 0.01f;
			}
			else if (mTitleNum[i].mAnimationTime < 0){
				mTitleNum[i].mAnimationTime = 30;
				mTitleNum[i].mAnimation = false;
			}
		}
	}
}