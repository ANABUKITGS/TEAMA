#include "CCredit.h"

#include "CScene.h"
#include "CFade.h"
#include "CKey.h"
#include "CGamePad.h"
#include "CText.h"
#include "CSE.h"

CTexture mTexBack;

void CCredit::Init(){
	mTexBack.Load(".\\Data\\Images\\Result\\Back.tga");
	mTextPos = -424.0f;
}

void CCredit::Update(){
	//終了
	if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3) || CGamePad::Once(PAD_10)){
		CSE::mSoundContinue.Play();
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
	}

	//早送り
	if (CKey::Push(VK_RETURN) || CKey::Push(VK_SPACE) ||
		CKey::Push(VK_UP) || CKey::Push('W') || CGamePad::Push(PAD_2) || CGamePad::Push(PAD_UP))
		mTextPos += 10.0f;

	else if (CKey::Push(VK_DOWN) || CKey::Push('S') || CGamePad::Push(PAD_DOWN))
		mTextPos += 0.0f;

	else if (CGamePad::Push(PAD_LSTICKY, 0.1f) || CGamePad::Push(PAD_LSTICKY, -0.1f)){
		if (CGamePad::Push(PAD_LSTICKY, 0.1f))
			mTextPos += 1.0f + 9.0f * CGamePad::GetStick(PAD_LSTICKY);

		if (CGamePad::Push(PAD_LSTICKY, -0.1f))
			mTextPos += 1.0f * (1.0f + CGamePad::GetStick(PAD_LSTICKY));
	}
	else
		mTextPos += 1.0f;

	//終わったら終了
	if (mTextPos - 32 * 24 > 360.0f)
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
}

void CCredit::Render(){
	mTexBack.DrawImage(-640.0f, 640.0f, -360.0f, 360.0f, 0, 1280, 720, 0, 1.0f);
	CText::DrawStringW(L"[制作チーム]",	-16 * 7, mTextPos, 32, 1.0f, 0);
	CText::DrawStringW(L"前田 拓磨",		-16 * 5, mTextPos - 32 * 1, 32, 1.0f, 0);
	CText::DrawStringW(L"長尾 蓮",		-16 * 4, mTextPos - 32 * 2, 32, 1.0f, 0);
	CText::DrawStringW(L"小見山 嶺治",	-16 * 6, mTextPos - 32 * 3, 32, 1.0f, 0);
	CText::DrawStringW(L"南木 彩希",		-16 * 5, mTextPos - 32 * 4, 32, 1.0f, 0);
	CText::DrawStringW(L"石田 萌夏",		-16 * 5, mTextPos - 32 * 5, 32, 1.0f, 0);
	CText::DrawStringW(L"[教員]",		-16 * 4, mTextPos - 32 * 12, 32, 1.0f, 0);
	CText::DrawStringW(L"高橋 忍",		-16 * 4, mTextPos - 32 * 13, 32, 1.0f, 0);
	CText::DrawStringW(L"平田 大",		-16 * 4, mTextPos - 32 * 14, 32, 1.0f, 0);
	CText::DrawStringW(L"井上 萌美",		-16 * 5, mTextPos - 32 * 15, 32, 1.0f, 0);
	CText::DrawStringW(L"[素材借用]",	-16 * 6, mTextPos - 32 * 21, 32, 1.0f, 0);
	CText::DrawStringW(L"M+FONTS",		-16 * 7, mTextPos - 32 * 22, 32, 1.0f, 0);
	CText::DrawStringW(L"魔王魂",		-16 * 3, mTextPos - 32 * 23, 32, 1.0f, 0);
	CText::DrawStringW(L"Music is VFR",	-16 * 12, mTextPos - 32 * 24, 32, 1.0f, 0);
}