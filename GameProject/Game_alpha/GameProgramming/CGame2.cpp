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

CRectangle *CGame2::mRectPlayer;


void CGame2::Init() {

	CRectangle *mapchip;	//Init�ł����g�p���Ă��Ȃ��̂ŁAInit���\�b�h�̃��[�J���ϐ��Ő錾

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

//		for (int i = 0; i < MAP_SIZEY; i++){
//			for (int j = 0; j < MAP_SIZEX; j++){
//				//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
//				if (gamemap[i][j] >= ECELLNUM::ESIZE){
//					MessageBox(NULL, "�}�b�v�f�[�^���j�����Ă��邩�A�Ⴄ�t�@�C���ł��B", "�G���[", 0x00040010L);
//					for (int i = 0; i < MAP_SIZEY; i++){
//						for (int j = 0; j < MAP_SIZEX; j++)
//							gamemap[i][j] = ECELLNUM::ENONE;
//					}
//					char loadmsg[MAX_PATH + 8];
//					sprintf(loadmsg, "Load to %s\n", filepath);
//					printf(loadmsg);
////					fclose(fp);	//�t�@�C�������
//					return;
//				}
//				else {
//					if (gamemap[i][j] == ECELLNUM::EGROUND){
//						//�� �Ȃ�, �� �Ȃ�
//						if (gamemap[i - 1][j] != ECELLNUM::EGROUND && gamemap[i + 1][j] != ECELLNUM::EGROUND){
//							//���E �Ȃ�
//							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//							//�� �Ȃ�, �E ����
//							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//							//�� ����, �E ����
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//							//�� ����, �E �Ȃ�
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//						}
//						//�� �Ȃ�, �� ����
//						else if ((gamemap[i - 1][j] != ECELLNUM::EGROUND && gamemap[i + 1][j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[i + 1][j] != ECELLNUM::EGROUND)){
//							//���E �Ȃ�
//							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//								mapchip->mRotation = -90;
//							}
//							//�� �Ȃ�, �E ����
//							else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//							//�� ����, �E ����
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//							//�� ����, �E �Ȃ�
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//							}
//						}
//						//�� ����, �� �Ȃ�
//						else if ((gamemap[i - 1][j] == ECELLNUM::EGROUND && gamemap[i + 1][j] != ECELLNUM::EGROUND) || (gamemap[i - 1][j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
//							//���E �Ȃ�
//							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//								mapchip->mRotation = 90;
//							}
//							//�� �Ȃ�, �E ����
//							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//							}
//							//�� ����, �E ����
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//							}
//							//�� ����, �E �Ȃ�
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//							}
//						}
//						//�� ����, �� ����
//						else if ((gamemap[i - 1][j] == ECELLNUM::EGROUND && gamemap[i + 1][j] == ECELLNUM::EGROUND)){
//							//���E �Ȃ�
//							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//								mapchip->mRotation = 90;
//							}
//							//�� �Ȃ�, �E ����
//							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//								mapchip->mRotation = -90;
//							}
//							//�� ����, �E ����
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//							}
//							//�� ����, �E �Ȃ�
//							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
//								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
//								mapchip->mRotation = 90;
//							}
//						}
//						else {
//							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//						}
//					}
//					//�����甲���鑫��
//					else if (gamemap[i][j] == ECELLNUM::EUNDER){
//						if (gamemap[i][j - 1] != ECELLNUM::EUNDER && gamemap[i][j + 1] == ECELLNUM::EUNDER)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EUNDER && gamemap[i][j + 1] == ECELLNUM::EUNDER)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EUNDER && gamemap[i][j + 1] != ECELLNUM::EUNDER)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);
//
//						else
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);
//					}
//					//�x���g�R���x�A ��
//					else if (gamemap[i][j] == EBELTL){
//						if (gamemap[i][j - 1] != ECELLNUM::EBELTL && gamemap[i][j + 1] == ECELLNUM::EBELTL)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EBELTL && gamemap[i][j + 1] == ECELLNUM::EBELTL)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EBELTL && gamemap[i][j + 1] != ECELLNUM::EBELTL)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);
//
//						else
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);
//					}
//					//�x���g�R���x�A �E
//					else if (gamemap[i][j] == ECELLNUM::EBELTR){
//						if (gamemap[i][j - 1] != ECELLNUM::EBELTR && gamemap[i][j + 1] == ECELLNUM::EBELTR)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EBELTR && gamemap[i][j + 1] == ECELLNUM::EBELTR)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);
//
//						else if (gamemap[i][j - 1] == ECELLNUM::EBELTR && gamemap[i][j + 1] != ECELLNUM::EBELTR)
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);
//
//						else
//							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);
//					}
//					//��� ~ �X�C�b�`
//					else if (gamemap[i][j] == ECELLNUM::EJEWELRY)
//						//						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EJEWELRY);
//						new CMapJewelry(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject);
//
//					else if (gamemap[i][j] > ECELLNUM::EJEWELRY && gamemap[i][j] < ECELLNUM::EPLAYER)
//						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EJEWELRY);
//
//					//�v���C���[ ~ �{�X
//					if (gamemap[i][j] >= ECELLNUM::EPLAYER && gamemap[i][j] < ECELLNUM::EBOX){
//						int temp_setcell = gamemap[i][j];
//						if (gamemap[i - 1][j] == temp_setcell && gamemap[i + 1][j] != temp_setcell){
//							if (temp_setcell == ECELLNUM::EPLAYER)
//								new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexPlayer, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
//
//							else if (temp_setcell == ECELLNUM::EENEMY1)
//								new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexEnemy, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EENEMY1);
//						}
//					}
//
//					//����M�~�b�N
//					if (gamemap[i][j] >= ECELLNUM::EBOX && gamemap[i][j] < ECELLNUM::ESIZE){
//
//					}
//				}
//			}
//		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//�t�@�C�������

	}
	mRectPlayer = new CPlayerT(CVector2(64, 264), CVector2(16, 60), NULL);
	//�G���Ăяo��
	new CEnemy(CVector2(1000, 265), CVector2(32, 32), NULL);
	new CEnemy(CVector2(1600, 265), CVector2(32, 32), NULL);
	new CEnemy(CVector2(2600, 265), CVector2(32, 32), NULL);
	//�ؔ��̐ݒu
	new CMapBox(CVector2(1000, 400), CVector2(50, 50), NULL);
}

/*
void CGame2::MakeTaskList(int *gamemap) {
	
	static CTexture mTexBack;// .Load(".\\Data\\Images\\Map\\Background.tga");
	static CTexture mTexUI;// .Load(".\\Data\\Images\\Map\\MapUI.tga");
	static CTexture mTexObject;// .Load(".\\Data\\Images\\Map\\MapObject.tga");
	static CTexture mTexCharacter;// .Load(".\\Data\\Images\\Map\\MapCharacter.tga");
	static CTexture mTexPlayer;// .Load(".\\Data\\Images\\Map\\MapPlayer.tga");
	static CTexture mTexEnemy;// .Load(".\\Data\Images\\Map\\MapEnemy.tga");

	if (mTexBack.id == 0) {
		mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
		mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
		mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
		mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
		mTexPlayer.Load(".\\Data\\Images\\Map\\MapPlayer.tga");
		//	mTexEnemy.Load(".\\Data\Images\\Map\\MapEnemy.tga");
	}


	CTaskManager::Get()->Destroy();

	CRectangle *mapchip;	//Init�ł����g�p���Ă��Ȃ��̂ŁAInit���\�b�h�̃��[�J���ϐ��Ő錾
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
			if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::ESIZE){
				MessageBox(NULL, "�}�b�v�f�[�^���j�����Ă��邩�A�Ⴄ�t�@�C���ł��B", "�G���[", 0x00040010L);
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++)
						gamemap[i * MAP_SIZEX + j] = ECELLNUM::ENONE;
				}
//				char loadmsg[MAX_PATH + 8];
//				sprintf(loadmsg, "Load to %s\n", filepath);
//				printf(loadmsg);
//				fclose(fp);	//�t�@�C�������
				return;
			}
			else {
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EGROUND){
					//�� �Ȃ�, �� �Ȃ�
					if (gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND){
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//�� �Ȃ�, �� ����
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND)){
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
							mapchip->mRotation = -90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != EGROUND && gamemap[i * MAP_SIZEX + j + 1] == EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//�� ����, �� �Ȃ�
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND) || (gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
					}
					//�� ����, �� ����
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND)){
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = -90;
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
					}
					else {
						mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
					}
				}
				//�����甲���鑫��
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EUNDER){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EUNDER)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EUNDER);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EUNDER)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EUNDER)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EUNDER);

					else
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EUNDER);
				}
				//�x���g�R���x�A ��
				else if (gamemap[i * MAP_SIZEX + j] == EBELTL){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTL);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTL);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTL)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTL);

					else
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTL);
				}
				//�x���g�R���x�A �E
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBELTR){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTR);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTR);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTR)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTR);

					else
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EBELTR);
				}
				//��� ~ �X�C�b�`
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY)
					//						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EJEWELRY);
					new CMapJewelry(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject);

				else if (gamemap[i * MAP_SIZEX + j] > ECELLNUM::EJEWELRY && gamemap[i * MAP_SIZEX + j] < ECELLNUM::EPLAYER)
					new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EJEWELRY);

				//�v���C���[ ~ �{�X
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EPLAYER && gamemap[i * MAP_SIZEX + j] < ECELLNUM::EBOX){
					int temp_setcell = gamemap[i * MAP_SIZEX + j];
					if (gamemap[(i - 1) * MAP_SIZEX + j] == temp_setcell && gamemap[(i + 1) * MAP_SIZEX + j] != temp_setcell){
						if (temp_setcell == ECELLNUM::EPLAYER)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexPlayer, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));

						else if (temp_setcell == ECELLNUM::EENEMY1)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexEnemy, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EENEMY1);
					}
				}

				//����M�~�b�N
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EBOX && gamemap[i * MAP_SIZEX + j] < ECELLNUM::ESIZE){

				}
			}
		}
	}

}

*/

void CGame2::Update() {
	if (CKey::Push('D')) {
		mCamera.x += 5;
	}
	if (CKey::Push('A')) {
		mCamera.x -= 5;
	}
	if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE))
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
	CTaskManager::Get()->Update();
}

void CGame2::Render() {
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CPlayerT::mpPlayer->mPosition.x;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();

	//�o�ߎ���
	char time_buf[16];
	for (int i = 0; i < 16; i++)
		time_buf[i] = '\0';
	sprintf(time_buf, "%02d:%06.3f", CTime::ElapsedTimeMin(), CTime::ElapsedTimeSec());
	CText::DrawString(time_buf, 352, 328, 32, 1.0f, 0);
}
