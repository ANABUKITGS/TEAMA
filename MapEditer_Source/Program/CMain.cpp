#include "CMain.h"
#include <Windows.h>
#include "CText.h"
#include "CFrameRate.h"
#include "CEditer.h"

CEditer mEditer;

void CMain::Init() {
	//glutFullScreen();	//�t���X�N���[��
	CText::Init();	//�e�L�X�g�̃e�N�X�`���[�̓ǂݍ��݂Ȃ�
	mEditer.Init();
}

//�J��Ԃ����s���鏈���̒�`
void CMain::Update() {
	CFrameRate::Render();
	mEditer.Update();
	mEditer.Render();
}