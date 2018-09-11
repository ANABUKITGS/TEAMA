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
	if (CKey::Once(VK_RETURN) || CGamePad::Once(PAD_2) || CKey::Once(VK_SPACE) || CKey::Once(VK_ESCAPE) || CGamePad::Once(PAD_3) || CGamePad::Once(PAD_10)){
		CSE::mSoundContinue.Play();
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
	}

	//������
	if (CGamePad::Push(PAD_LSTICKY, 0.1f) || CGamePad::Push(PAD_LSTICKY, -0.1f)){
		if (CGamePad::Push(PAD_LSTICKY, 0.1f))
			mTextPos += 1.0f + 9.0f * CGamePad::GetStick(PAD_LSTICKY);

		if (CGamePad::Push(PAD_LSTICKY, -0.1f))
			mTextPos += 1.0f * (1.0f + CGamePad::GetStick(PAD_LSTICKY));
	}
	else
		mTextPos += 1.0f;

	//�I�������I��
	if (mTextPos - 32 * 22 > 360.0f)
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
}

void CCredit::Render(){
	mTexBack.DrawImage(-640.0f, 640.0f, -360.0f, 360.0f, 0, 1280, 720, 0, 1.0f);
	CText::DrawStringW(L"[����`�[��]", -16 * 7, mTextPos, 32, 1.0f, 0);
	CText::DrawStringW(L"�O�c  ��\n����  �@\n�����R �䎡\n���  �ʊ�\n�Γc  �G��", -16 * 6, mTextPos - 32 * 1, 32, 1.0f, 0);
	CText::DrawStringW(L"[����]", -16 * 4, mTextPos - 32 * 11, 32, 1.0f, 0);
	CText::DrawStringW(L"���� �E\n���c ��\n��� �G��", -16 * 4, mTextPos - 32 * 12, 32, 1.0f, 0);
	CText::DrawStringW(L"[�f�ގؗp]", -16 * 6, mTextPos - 32 * 20, 32, 1.0f, 0);
	CText::DrawStringW(L"������", -16 * 3, mTextPos - 32 * 21, 32, 1.0f, 0);
	CText::DrawStringW(L"Music is VFR", -16 * 12, mTextPos - 32 * 22, 32, 1.0f, 0);
}