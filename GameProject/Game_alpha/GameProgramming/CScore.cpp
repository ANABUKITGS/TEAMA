#include "CScore.h"
#include "CKey.h"
#include "CGamePad.h"
#include "CPlayerT.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>

int CGetScore::mScore;
char CName::name[3] = { 'aaa' };
int CName::charnum = 0;
bool CGetScore::mSort = false;
char buf[11];
wchar_t bufw[64];

void CGetScore::Init(){
	mScore = 0;
	mdammy = 0;
	mdammy2 = 0;
	mJewelScore = 150;
	mMiniJewelScore = 10;
	mLifeScore = 100;
	mTimerScore = -1;
}
void CGetScore::Update(){
	if (GetKeyState(VK_DOWN) & 0x8000 || CGamePad::OncePush(PAD_LSTICKY, -0.5f)){
		mScore--;
	}
	if (GetKeyState(VK_UP) & 0x8000 || CGamePad::OncePush (PAD_LSTICKY, 0.5f)){
		mScore++;
	}
	
	mdammy = CPlayerT::mpPlayer->mJewel * mJewelScore;
	mScore += mdammy;
	swprintf(bufw, L"ダイヤモンド  %3d ×%4d = %4d", CPlayerT::mpPlayer->mJewel,mJewelScore,mdammy);
	CText::DrawStringW(bufw, -100, 200, 20, 1.0f, 0);
	mdammy = CPlayerT::mpPlayer->mMiniJewel* mMiniJewelScore;
	mScore += mdammy;
	swprintf(bufw, L"ダイヤモンド  %3d ×%4d = %4d", CPlayerT::mpPlayer->mMiniJewel,mMiniJewelScore,mdammy);
	CText::DrawStringW(bufw, -100, 100, 20, 1.0f, 0);
	mdammy = CPlayerT::mpPlayer->mLife * mLifeScore;
	mScore += mdammy;
	swprintf(bufw, L"ザンキ     %3d ×%4d = %4d", CPlayerT::mpPlayer->mLife,mLifeScore,mdammy);
	CText::DrawStringW(bufw, -100, 0, 20, 1.0f, 0);
	mdammy = CPlayerT::mpPlayer->mLife * mLifeScore;
	mScore += mdammy;
	swprintf(bufw, L"タイマー    %3d ×%4d", mTimerScore,mdammy);
	CText::DrawStringW(bufw, -100, -100, 20, 1.0f, 0);
	swprintf(bufw, L"スコア      %4d", mScore);
	CText::DrawStringW(bufw, -100, -200, 20, 1.0f, 0);
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2)){
		CSceneChange::changenum = CSceneChange::ENAME;
		mSort = true;
		for (int i = 0; i < 3; i++){
			CName::name[i] = 'a';
		}
		CName::charnum = 0;
	}
	else
		mScore = 0;
	
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
	if (CGetScore::mSort){
		Sort(CGetScore::mScore, CName::name);
		CGetScore::mSort = false;
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