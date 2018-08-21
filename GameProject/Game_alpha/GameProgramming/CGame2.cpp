#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CMapChip.h"
#include "CPlayerT.h"
#include "CScene.h"
#include "CTime.h"
#include "CBGM.h"
#include "CMapBackImage.h"
#include "CMapSwitchGround.h"

bool CGame2::mCheat[CHEAT_NUM::ESIZE];
CMapBackImage *mBackImage[2];
CCamera2D CGame2::mCamera;

void CGame2::Init() {
	mCamera.SetOrtho(WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);

	char filepath[256];
//	if (map == CMapIO::EGAMEMAP)
	//	sprintf(filepath, "%s", GAME_MAP);
	//else if (map == CMapIO::ETUTORIAL)
		sprintf(filepath, "%s", TUTORIAL_MAP);
	//else if (map == CMapIO::EEDITERMAP)
	//	sprintf(filepath, "%s", EDITER_MAP);
	//else{
	//	MessageBox(NULL, "�}�b�v�f�[�^�̎w�肪����Ă��܂���B", "�G���[", 0x00040010L);
	//	return;
	//}
	FILE *fp = fopen(filepath, "rb");	//�t�@�C�����J��(�ǂݍ���)
	if (fp == NULL){	//NULL���Ԃ��Ă�����G���[
		MessageBox(NULL, "�}�b�v�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B", "�G���[", 0x00040010L);
		printf("Load : fopen error!\n");
	}
	else {
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		int gamemap[MAP_SIZEY][MAP_SIZEX];
		//		char *buf = new char[size];	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
		fseek(fp, 0L, SEEK_SET);
		size = sizeof(gamemap);
		fread(gamemap, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
		//		buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
		fclose(fp);	//�t�@�C�����N���[�Y����

		CEditer::MakeTaskList((int*)gamemap);

		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//�t�@�C�������

	}
	//�w�i
	mBackImage[0] = new CMapBackImage(CVector2(mCamera.x, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	mBackImage[1] = new CMapBackImage(CVector2(mCamera.x + 1280, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	CMapSwitchGround::mNumber = ESWITCH_GROUND1;
}

void CGame2::Update() {
	if (CGame2::mCamera.x < mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x + 1280;

	if (CGame2::mCamera.x < mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x + 1280;

	if (CKey::Push('D')) {
		mCamera.x += 5;
	}
	if (CKey::Push('A')) {
		mCamera.x -= 5;
	}
	if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE)){
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
		CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
	}

#ifdef _DEBUG
	if (CGamePad::Push(PAD_11) || CKey::Push(LVKF_CONTROL)){
		if (CGamePad::Once(PAD_1) || CKey::Once('1')){
			if (!mCheat[CHEAT_NUM::EMUTEKI])
				mCheat[CHEAT_NUM::EMUTEKI] = true;
			else
				mCheat[CHEAT_NUM::EMUTEKI] = false;
		}
	}
#endif
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Remove();
}

void CGame2::Render() {
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CPlayerT::mpPlayer->mPosition.x;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();

#ifdef _DEBUG
	wchar_t jumptime_buf[256];
	swprintf(jumptime_buf, L"�v���C���[\nmVelocityX\n%6.2f\nmVelocityY\n%6.2f\nmPosition.x\n%.2f\nmPosition.y\n%.2f", CPlayerT::mpPlayer->mVelocityX, CPlayerT::mpPlayer->mVelocityY, CPlayerT::mpPlayer->mPosition.x, CPlayerT::mpPlayer->mPosition.y);
	CText::DrawStringW(jumptime_buf, 0, 0, 16, 1.0f, 0);
	CheatText();
#endif

	//�o�ߎ���
	char time_buf[64];
	for (int i = 0; i < 16; i++)
		time_buf[i] = '\0';
	sprintf(time_buf, "%02d:%06.3f\nmJewel     %-2d\nmMiniJewel %-2d\nmLife      %-2d", CTime::ElapsedTimeMin(), CTime::ElapsedTimeSec(), CPlayerT::mpPlayer->mJewel, CPlayerT::mpPlayer->mMiniJewel, CPlayerT::mpPlayer->mLife);
	CText::DrawString(time_buf, 352, 328, 16, 1.0f, 0);
}

void CGame2::CheatText(){
#ifdef _DEBUG
	for (int i = CHEAT_NUM::EMUTEKI; i < CHEAT_NUM::ESIZE; i++){
		if (mCheat[i])
			mCheat[CHEAT_NUM::EFLAG] = true;	//���̃Z�b�V�����Ń`�[�g���g������
	}

	if (mCheat[CHEAT_NUM::EFLAG]){
		wchar_t cheat_buf[16];
		swprintf(cheat_buf, L"\n�`�[�g���悤 �Z�b�V����");
		CText::DrawStringW(cheat_buf, -640, 328, 16, 1.0f, 0);

		if (mCheat[CHEAT_NUM::EMUTEKI]){
			wchar_t cheatname_buf[16];
			swprintf(cheatname_buf, L"�E�ނĂ�");
			CText::DrawStringW(cheatname_buf, -640, 296, 16, 1.0f, 0);
		}
	}
#endif
}