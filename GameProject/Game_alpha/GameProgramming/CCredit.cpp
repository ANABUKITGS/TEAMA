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
	//�I��
	if (CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3) || CGamePad::Once(PAD_10)){
		CSE::mSoundContinue.Play();
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
	}

	//������
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

	//�I�������I��
	if (mTextPos - 32 * 24 > 360.0f)
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
}

void CCredit::Render(){
	mTexBack.DrawImage(-640.0f, 640.0f, -360.0f, 360.0f, 0, 1280, 720, 0, 1.0f);
	CText::DrawStringW(L"[����`�[��]",	-16 * 7, mTextPos, 32, 1.0f, 0);
	CText::DrawStringW(L"�O�c ��",		-16 * 5, mTextPos - 32 * 1, 32, 1.0f, 0);
	CText::DrawStringW(L"���� �@",		-16 * 4, mTextPos - 32 * 2, 32, 1.0f, 0);
	CText::DrawStringW(L"�����R �䎡",	-16 * 6, mTextPos - 32 * 3, 32, 1.0f, 0);
	CText::DrawStringW(L"��� �ʊ�",		-16 * 5, mTextPos - 32 * 4, 32, 1.0f, 0);
	CText::DrawStringW(L"�Γc �G��",		-16 * 5, mTextPos - 32 * 5, 32, 1.0f, 0);
	CText::DrawStringW(L"[����]",		-16 * 4, mTextPos - 32 * 12, 32, 1.0f, 0);
	CText::DrawStringW(L"���� �E",		-16 * 4, mTextPos - 32 * 13, 32, 1.0f, 0);
	CText::DrawStringW(L"���c ��",		-16 * 4, mTextPos - 32 * 14, 32, 1.0f, 0);
	CText::DrawStringW(L"��� �G��",		-16 * 5, mTextPos - 32 * 15, 32, 1.0f, 0);
	CText::DrawStringW(L"[�f�ގؗp]",	-16 * 6, mTextPos - 32 * 21, 32, 1.0f, 0);
	CText::DrawStringW(L"M+FONTS",		-16 * 7, mTextPos - 32 * 22, 32, 1.0f, 0);
	CText::DrawStringW(L"������",		-16 * 3, mTextPos - 32 * 23, 32, 1.0f, 0);
	CText::DrawStringW(L"Music is VFR",	-16 * 12, mTextPos - 32 * 24, 32, 1.0f, 0);
}