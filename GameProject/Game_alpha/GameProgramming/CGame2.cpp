#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CMapChip.h"
#include "CPlayerT.h"
#include "CScene.h"
#include "CEnemy.h"
#include "CMapBox.h"
#include "CTime.h"
#include "CBGM.h"
#include "CMapBackImage.h"

void CGame2::Init() {
	mCamera.SetOrtho(WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);
	//mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	//mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	//mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	//mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
	//mTexEnemy.Load(".\\Data\Images\\Map\\MapEnemy.tga");

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
	//�G���Ăяo��
	new CEnemy(CVector2(1000, 265), CVector2(32, 64), NULL);
	new CEnemy(CVector2(1600, 265), CVector2(32, 64), NULL);
	new CEnemy(CVector2(2600, 265), CVector2(32, 64), NULL);
	//�ؔ��̐ݒu
	new CMapBox(CVector2(1000, 400), CVector2(50, 50), NULL);

	new CMapBackImage(CVector2(0, 360), CMapBackImage::ETEXTURE_LAYER::LAYER2);
	new CMapBackImage(CVector2(0, 360), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	new CPlayerT(CVector2(64, 264), CVector2(16, 60), NULL);
}

void CGame2::Update() {
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
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Remove();
}

void CGame2::Render() {
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CPlayerT::mpPlayer->mPosition.x;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();

	//�o�ߎ���
	char time_buf[64];
	for (int i = 0; i < 16; i++)
		time_buf[i] = '\0';
	sprintf(time_buf, "%02d:%06.3f\nmJewel %-2d\nmLife %-2d", CTime::ElapsedTimeMin(), CTime::ElapsedTimeSec(), CPlayerT::mpPlayer->mJewel, CPlayerT::mpPlayer->mLife);
	CText::DrawString(time_buf, 352, 328, 32, 1.0f, 0);
}