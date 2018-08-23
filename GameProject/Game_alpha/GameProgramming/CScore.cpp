#include "CScore.h"
#include "CKey.h"
#include "CGamePad.h"
#include "CPlayerT.h"
#include "CTime.h"
#include "CGame2.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>

int CScore::mScore[5] = { 0, 0, 0, 0, 0 };;
char CName::name[3] = { 'aaa' };
int CName::charnum = 0;
bool CScore::mSort = false;
int CScore::mJewelScore;
int CScore::mMiniJewelScore;
int CScore::mLifeScore;
int CScore::mTimerScore;
char buf[11];
wchar_t bufw[64];
int mCount[5] = {0,0,0,0,0};

void CScore::Init(){
	mJewelScore = 150;
	mMiniJewelScore = 10;
	mLifeScore = 100;
	mTimerScore = 1;
	mScoreNum = 0;
}
void CScore::Update(){	
	if (mScore[mScoreNum] <= mCount[mScoreNum])
		mScoreNum++;
	mCount[mScoreNum]=CountUp(mScore[mScoreNum], mCount[mScoreNum]);
	swprintf(bufw, L"宝            %3d ×%4d  = %4d", CPlayerT::mpPlayer->mJewel,mJewelScore,mCount[0]);
	CText::DrawStringW(bufw, -300, 200, 20, 1.0f, 0);
	swprintf(bufw, L"石            %3d ×%4d  = %4d", CPlayerT::mpPlayer->mMiniJewel,mMiniJewelScore,mCount[1]);
	CText::DrawStringW(bufw, -300, 100, 20, 1.0f, 0);
	swprintf(bufw, L"命            %3d ×%4d  = %4d", CPlayerT::mpPlayer->mLife,mLifeScore,mCount[2]);
	CText::DrawStringW(bufw, -300, 0, 20, 1.0f, 0);
	swprintf(bufw, L"タイマー       %02d:%02.0f × %3d  = %4d", CGame2::mTimeMin,CGame2::mTimeSec,-mTimerScore,-mCount[3]);
	CText::DrawStringW(bufw, -300, -100, 20, 1.0f, 0);
	swprintf(bufw, L"スコア                       %4d", mCount[4]);
	CText::DrawStringW(bufw, -300, -200, 20, 1.0f, 0);
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2)){
		CSceneChange::changenum = CSceneChange::ENAME;
		mSort = true;
		for (int i = 0; i < 3; i++){
			CName::name[i] = 'a';
		}
		CName::charnum = 0;
	}
	
}

int CScore::CountUp(int max,int count){
	if (max>0){
		if (max > count){
			count++;
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
	mScore[0] = CPlayerT::mpPlayer->mJewel * mJewelScore;
	mScore[1] = CPlayerT::mpPlayer->mMiniJewel* mMiniJewelScore;
	mScore[2] = CPlayerT::mpPlayer->mLife * mLifeScore;
	mScore[3] = ((CGame2::mTimeMin * 60 + CGame2::mTimeSec)/6) * mTimerScore;
	mScore[4] += mScore[0] + mScore[1] + mScore[2] + mScore[3];
}

void CName::Init(){
	CText::Init();
	
}
void CName::Update(){
	if (CKey::Once(VK_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f)){
		if (name[charnum] == 'z')
			name[charnum] = '1';
		else if (name[charnum] == '9')
			name[charnum] = 'a';
		else
			name[charnum]++;
	}
	if (CKey::Once(VK_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f)){
		if (name[charnum] == 'a')
			name[charnum] = '9';
		else if (name[charnum] == '1')
			name[charnum] = 'z';
		else
			name[charnum]--;
	}
	if (CKey::Once(VK_LEFT) || CGamePad::Once(PAD_LSTICKX, -0.5f))
	if (charnum > 0)
		charnum--;
	if (CKey::Once(VK_RIGHT) || CGamePad::Once(PAD_LSTICKX, 0.5f))
	if (charnum < 2)
		charnum++;
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2))
		CSceneChange::changenum = CSceneChange::ERANKING;
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  //描画色　黄色
	sprintf(buf2, "%s", name);
	CText::DrawString(buf2, -100, 0, 50, 1.0f, 0);
}

void CRanking::Init(){
	for (int i = 0; i < 3; i++){
		mRanking[i].s = 300 - i * 100;
		for (int j = 0; j < 3; j++){
			mRanking[i].n[j] = 'a';
		}
	}
}
void CRanking::Update(){
	if (CScore::mSort){
		Sort(CScore::mScore[4], CName::name);
		CScore::mSort = false;
	}
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);  //描画色　黄
	swprintf(bufw, L"ランキング");
	CText::DrawStringW(bufw, 0, 200, 20, 1.0f, 0);
	for (int i = 0; i < 3; i++){
		swprintf(bufw, L"%4.2d", i + 1);
		CText::DrawStringW(bufw, -200, 100 + i * -100, 20, 1.0f, 0);
		swprintf(bufw, L"%d", mRanking[i].s);
		CText::DrawStringW(bufw, 200, 100 + i * -100, 20, 1.0f, 0);
		sprintf(buf2, "%3s", mRanking[i].n);
		CText::DrawString(buf2, 0, 100 + i * -100, 20, 1.0f, 0);
	}
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2))
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
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
}