#include "CScore.h"
#include "CKey.h"
#include "CGamePad.h"
#include "CPlayerT.h"
#include "CTime.h"
#include "CGame2.h"
#include "CSE.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "CFade.h"
#include "CFileIO.h"

int CScore::mScore[5] = { 0, 0, 0, 0, 0 };;
char CName::name[3] = { '   ' };
int CName::charnum = 0;
bool CScore::mSort = false;
int CScore::mJewelScore;
int CScore::mMiniJewelScore;
int CScore::mLifeScore;
int CScore::mTimerScore;
int CScore::mScoreNum;

char buf[11];
wchar_t bufw[512];
int mCount[5] = {0,0,0,0,0};
enum CSceneResult::EResultTag CSceneResult::mResultTag;

extern CScore mScore;
extern CName mName;
extern CRanking mRanking;


void CSceneResult::Init(){
	mTexResult.Load(".\\Data\\Images\\Result\\result.tga");
	mTexResultback.Load(".\\Data\\Images\\Result\\Back.tga");
	mResultTag = ESCORE;
}
void CSceneResult::Update(){
	
	mTexResultback.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);
	mTexResult.DrawImage(-382, 382, -320, 320, 0, 764, 640, 0, 1.0f);
	switch (mResultTag){
	case CSceneResult::ESCORE:
		mScore.Update();
		break;
	case CSceneResult::ENAME:
		mName.Update();
		break;
	case CSceneResult::ERANKING:
		mRanking.Update();
		break;
	default:
		break;
	}
}

void CScore::Init(){
	mJewelScore = 150;
	mMiniJewelScore = 10;
	mLifeScore = 100;
	mTimerScore = 1;
	mScoreNum = 0;
	mTexResultTitle.Load(".\\Data\\Images\\Result\\Title.tga");
}
void CScore::Update(){	
	mTexResultTitle.DrawImage(-255, 255, 158, 300, 0, 510, 143, 0, 1.0f);
	if (mScore[mScoreNum] <= mCount[mScoreNum])
		mScoreNum++;
	if (mScore[4] > mCount[4])
	mCount[mScoreNum]=CountUp(mScore[mScoreNum], mCount[mScoreNum]);
	swprintf(bufw, L"•ó      %3d ~%4d  = %4d\n\n•Ð      %3d ~%4d  = %4d\n\n–½      %3d ~%4d  = %4d\n\nƒ^ƒCƒ}[   %03d ~ %3d  = %4d\n\n\n\nƒXƒRƒA                 %4d", CPlayerT::mpPlayer->mJewel, mJewelScore, mCount[0], CPlayerT::mpPlayer->mMiniJewel, mMiniJewelScore, mCount[1], CPlayerT::mpPlayer->mLife, mLifeScore, mCount[2], CGame2::mTime, -mTimerScore, -mCount[3], mCount[4]);
	CText::DrawStringW(bufw, -350, 100, 30, 1.0f, 0);
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE)){
		if (mScore[0] == mCount[0] && mScore[1] == mCount[1] && mScore[2] == mCount[2] && mScore[3] == mCount[3] &&mScore[4] == mCount[4]){
			CSE::mSoundContinue.Play();
			CSceneResult::mResultTag = CSceneResult::ENAME;
			mSort = true;
			for (int i = 0; i < 3; i++){
				CName::name[i] = 'A';
			}
			CName::charnum = 0;
		}
		else{
			for (int i = 0; i < 5; i++)
				mCount[i] = mScore[i];
		}
	}
	
}

int CScore::CountUp(int max,int count){
	if (max>0){
		if (max > count){
			if (max - count > 10){
				count += 10;
				CSE::mSoundScore.Play();
			}

			else{
				count++;
				CSE::mSoundScore.Play();
			}
			return count;
		}
	}
	return count;
	
}

void CScore::GetScore(){
	for (int i = 0; i < 5; i++){
		mCount[i] = 0;
		mScore[i] = 0;
	}
	mScoreNum = 0;
	mScore[0] = CPlayerT::mpPlayer->mJewel * mJewelScore;
	mScore[1] = CPlayerT::mpPlayer->mMiniJewel* mMiniJewelScore;
	mScore[2] = CPlayerT::mpPlayer->mLife * mLifeScore;
	mScore[3] = (CGame2::mTime / 6) * mTimerScore;
	mScore[4] += mScore[0] + mScore[1] + mScore[2] - mScore[3];
}

void CName::Init(){
	mTexName.Load(".\\Data\\Images\\Result\\Name.tga");
}
void CName::Update(){
	mTexName.DrawImage(-254, 254, 208, 300, 0, 508, 92, 0, 1.0f);
	if (CKey::OncePush('S') || CKey::OncePush(VK_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CGamePad::OncePush(PAD_LEFT)){
		if (name[charnum] == 'Z')
			name[charnum] = '0';
		else if (name[charnum] == '9')
			name[charnum] = '.';
		else if (name[charnum] == '.')
			name[charnum] = 'A';
		else
			name[charnum]++;
	}
	if (CKey::OncePush('W') || CKey::OncePush(VK_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CGamePad::OncePush(PAD_RIGHT)){
		if (name[charnum] == 'A')
			name[charnum] = '.';
		else if (name[charnum] == '.')
			name[charnum] = '9';
		else if (name[charnum] == '0')
			name[charnum] = 'Z';
		else
			name[charnum]--;
	}
	if (CKey::Once('A') || CKey::Once(VK_LEFT) || CGamePad::Once(PAD_LSTICKX, -0.5f) || CGamePad::Once(PAD_LEFT)){
		CSE::mSoundSelect.Play();
		if (charnum > 0)
			charnum--;
	}
	if (CKey::Once('D') || CKey::Once(VK_RIGHT) || CGamePad::Once(PAD_LSTICKX, 0.5f) || CGamePad::Once(PAD_RIGHT)){
		CSE::mSoundSelect.Play();
		if (charnum < 2)
			charnum++;
	}
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE)){
		CSE::mSoundContinue.Play();
		CSceneResult::mResultTag = CSceneResult::ERANKING;
	}

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  //•`‰æF@‰©F
	sprintf(buf, "%s", name);
	CText::DrawString(buf, -100, 0, 50, 1.0f, 0);
	swprintf(bufw, L"£");
	CText::DrawStringW(bufw, -97+50*charnum, 50 , 40, 1.0f, 0);
	swprintf(bufw, L"¥");
	CText::DrawStringW(bufw, -97 + 50 * charnum, -50, 40, 1.0f, 0);
}

void CRanking::Init(){
	mRanking[0].s = 300;
	mRanking[1].s = 200;
	mRanking[2].s = 100;
	strcpy(mRanking[0].r, "1st");
	strcpy(mRanking[1].r, "2ed");
	strcpy(mRanking[2].r, "3rd");
	strcpy(mRanking[0].n, "aaa");
	strcpy(mRanking[1].n, "aaa");
	strcpy(mRanking[2].n, "aaa");
	CRankingIO mRankingIO;
	mRankingIO.Load();
	mTexRankingTitle.Load(".\\Data\\Images\\Ranking\\Title.tga");
}
void CRanking::Update(){
	mTexRankingTitle.DrawImage(-250, 250, 152, 272, 0, 501, 120, 0, 1.0f);
	if (CScore::mSort){
		Sort(CScore::mScore[4], CName::name);
		CScore::mSort = false;
	}
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  //•`‰æF@‰©
	swprintf(bufw, L" ");
	CText::DrawStringW(bufw, -75, 200, 30, 1.0f, 0);
	for (int i = 0; i < 3; i++){
		sprintf(buf2, "%3s", mRanking[i].r);
		CText::DrawString(buf2, -300, 100 + i * -100, 40, 1.0f, 0);
		swprintf(bufw, L"%4d", mRanking[i].s);
		CText::DrawStringW(bufw, 200, 100 + i * -100, 40, 1.0f, 0);
		sprintf(buf2, "%3s", mRanking[i].n);
		CText::DrawString(buf2, -60, 100 + i * -100, 40, 1.0f, 0);
	}
	/*if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3)){
		mButton9 = true;
	}
	if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3)){
		mButton9 = true;
	}
	if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3)){
		mButton9 = true;
	}
	if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3)){
		mButton9 = true;
	}*/
	if (CGamePad::Push(PAD_11) && CGamePad::Once(PAD_12)){
		if (!mDelete)
			mDelete = true;
		else
			mDelete = false;
	}
	CRankingIO mRankingIO;
	if (mDelete){
		CText::DrawStringW(L"[íœ’†]", -16.0f * 5, -268.0f, 32.0f, 1.0f, 0);
		CText::DrawStringW(L"‚P:1st ‚Q:2nd ‚R:3rd ‚O:‘S‚Äíœ", -16.0f * 24, -300.0f, 32.0f, 1.0f, 0);
		if (CGamePad::Once(PAD_1)){
			strcpy(mRanking[0].n, "???");
			mDelete = false;
		}
		if (CGamePad::Once(PAD_2)){
			strcpy(mRanking[1].n, "???");
			mDelete = false;
		}
		if (CGamePad::Once(PAD_3)){
			strcpy(mRanking[2].n, "???");
			mDelete = false;
		}
		if (CGamePad::Once(PAD_10)){
			mRankingIO.Remove();
			mRankingIO.Load();
			mDelete = false;
		}
	}
	else{
		if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE)){
			CSE::mSoundContinue.Play();
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
			mRankingIO.Save();
		}
		if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3)){
			CSE::mSoundBack.Play();
			CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
			mRankingIO.Save();
		}
	}
}
void CRanking::Sort(int score, char *name){
	if (mRanking[2].s <= score){
		if (mRanking[0].s<score){
			mRanking[2].s = mRanking[1].s;
			mRanking[1].s = mRanking[0].s;
			mRanking[0].s = score;
			strcpy(mRanking[2].n, mRanking[1].n);
			strcpy(mRanking[1].n, mRanking[0].n);
			strcpy(mRanking[0].n, name);
		}
		else if (mRanking[1].s < score){
			mRanking[2].s = mRanking[1].s;
			mRanking[1].s = score;
			strcpy(mRanking[1].n, mRanking[0].n);
			strcpy(mRanking[1].n, name);
		}
		else{
			mRanking[2].s = score;
			strcpy(mRanking[2].n, name);
		}
	}
	CRankingIO mRankingIO;
	mRankingIO.Save();
}