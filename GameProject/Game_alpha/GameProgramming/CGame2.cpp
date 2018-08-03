#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"

void CGame2::Init() {
	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");

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
		fread(gamemap, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
		//		buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
		fclose(fp);	//�t�@�C�����N���[�Y����

		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
				if (gamemap[i][j] >= CEditer::ESIZE){
					MessageBox(NULL, "�}�b�v�f�[�^���j�����Ă��邩�A�Ⴄ�t�@�C���ł��B", "�G���[", 0x00040010L);
					for (int i = 0; i < MAP_SIZEY; i++){
						for (int j = 0; j < MAP_SIZEX; j++)
							gamemap[i][j] = CEditer::ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//�t�@�C�������
					return;
				}
				else {
					if (gamemap[i][j] == EGROUND){
						if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
							//���� �� ����
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//���� �� �Ȃ�
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}

						else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] == EGROUND){
							//���� �� ����
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//���� �� �Ȃ�
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}

						else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] != EGROUND){
							//�E�� �� ����
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//�E�� �� �Ȃ�
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//�E��
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//�E��
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}
						else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] != EGROUND){
							//���� �� ����
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//���� �� �Ȃ�
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//����
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							// mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}
					}

					//�����甲���鑫��
					if (gamemap[i][j] == EUNDER){
						if (gamemap[i][j - 1] != EUNDER && gamemap[i][j + 1] == EUNDER)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] == EUNDER)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] != EUNDER)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					}
					//�x���g�R���x�A
					if (gamemap[i][j] == EBELT){
						if (gamemap[i][j - 1] != EBELT && gamemap[i][j + 1] == EBELT)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else if (gamemap[i][j - 1] == EBELT && gamemap[i][j + 1] == EBELT)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else if (gamemap[i][j - 1] == EBELT && gamemap[i][j + 1] != EBELT)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

						else
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					}

					//���̑�
					if (gamemap[i][j] >= EJEWELRY && gamemap[i][j] < EPLAYER)
						new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
					//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

					//�L�����N�^�[
					if (gamemap[i][j] >= EPLAYER){
						int temp_setcell = gamemap[i][j];

						if (gamemap[i - 1][j] == temp_setcell && gamemap[i + 1][j] != temp_setcell)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexCharacter, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);

						else if (gamemap[i + 1][j] == temp_setcell && gamemap[i - 1][j] != temp_setcell)
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexCharacter, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);

						else
							new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexCharacter, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						//	mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
					}

				}
			}
		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//�t�@�C�������

	}
}

void CGame2::Update() {
	CTaskManager::Get()->Update();
}

void CGame2::Render() {
	CTaskManager::Get()->Render();
}
