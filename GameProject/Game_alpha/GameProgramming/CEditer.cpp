#include "CScene.h"
#include "CGamePad.h"

#include "CCamera2D.h"
#include "CMapChip.h"
#include "CMapJewelry.h"
#include "CMapUnder.h"
#include "CMapSign.h"
#include "CMapChikuwa.h"
#include "CMapBelt.h"
#include "CMapSwitchGround.h"
#include "CMapIce.h"
#include "CMapCheckPoint.h"
#include "CMapBox.h"
#include "CMapSteel.h"
#include "CBoss.h"

#include "CBGM.h"

CEnemy *CEnemy::mpEnemy = 0;
CMapIO mMapIO;

void CEditer::Init(){
	//�}�b�v ������
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			editmap[i][j] = ENONE;
			editmap_cursor[i][j] = ENONE;
			editmap_update[i][j] = ENONE;
		}
	}

	MakeTaskList((int *)editmap);

	editmap_cursor[0][0] = CURSOR_NUM;
	cursor_posX = cursor_posY = 0;
	setcell = EGROUND;
	cursor_anime = 0;
	guideIO = true;
	prtscrIO = false;
	pauseflag = false;

	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			editmap_rect[i][j].SetVertex(j * CELLSIZE - 640, j * CELLSIZE + CELLSIZE - 640, i * -CELLSIZE + 280, i * -CELLSIZE + CELLSIZE + 280);
		}
	}
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexSetCell.Load(".\\Data\\Images\\Map\\SetCell.tga");
	mTexBack.Load(".\\Data\\Images\\Result\\Back.tga");
}

void CEditer::Update(){
	CMapSwitchGround::mNumber = ESWITCH_GROUND1;
	if (!pauseflag){
		if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::OncePush('W')) && cursor_posY - 1 >= 0){
			//if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
			//	for (int i = 0; i < MAP_SIZEY; i++){
			//		for (int j = 0; j < MAP_SIZEX; j++){
			//			editmap_rect[i][j].mBottom -= 32;
			//			editmap_rect[i][j].mTop -= 32;
			//		}
			//	}
			//}
			editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posY = cursor_posY - 1;
		}
		if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush('S')) && cursor_posY + 1 < MAP_SIZEY){
			//if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
			//	for (int i = 0; i < MAP_SIZEY; i++){
			//		for (int j = 0; j < MAP_SIZEX; j++){
			//			editmap_rect[i][j].mBottom += 32;
			//			editmap_rect[i][j].mTop += 32;
			//		}
			//	}
			//}
			editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posY = cursor_posY + 1;
		}
		if ((CGamePad::OncePush(PAD_LEFT) || CGamePad::OncePush(PAD_LSTICKX, -0.5f) || CKey::OncePush('A')) && cursor_posX - 1 >= 0){
			if (editmap_rect[cursor_posY][cursor_posX].mLeft - CELLSIZE <= -640){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++){
						editmap_rect[i][j].mLeft += 32;
						editmap_rect[i][j].mRight += 32;
					}
				}
			}
			editmap_cursor[cursor_posY][cursor_posX - 1] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posX = cursor_posX - 1;
		}
		if ((CGamePad::OncePush(PAD_RIGHT) || CGamePad::OncePush(PAD_LSTICKX, 0.5f) || CKey::OncePush('D')) && cursor_posX + 1 < MAP_SIZEX){
			if (editmap_rect[cursor_posY][cursor_posX].mRight + CELLSIZE / 2 >= 640){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++){
						editmap_rect[i][j].mLeft -= 32;
						editmap_rect[i][j].mRight -= 32;
					}
				}
			}
			editmap_cursor[cursor_posY][cursor_posX + 1] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posX = cursor_posX + 1;
		}
		if (CGamePad::OncePush(PAD_5) || CGamePad::OncePush(PAD_7) || CKey::OncePush(VK_LEFT)){	//�p�[�c�I��
			if (setcell <= EGROUND)
				setcell = ECELLNUM::ESIZE - 1;
			else
				setcell--;
		}
		if (CGamePad::OncePush(PAD_6) || CGamePad::OncePush(PAD_8) || CKey::OncePush(VK_RIGHT)){	//�p�[�c�I��
			if (setcell >= ECELLNUM::ESIZE - 1)
				setcell = ECELLNUM::EGROUND;
			else
				setcell++;
		}
		if (CGamePad::Push(PAD_2) || CKey::Once(VK_RETURN)){	//�ݒu
			if (editmap[cursor_posY][cursor_posX] != ENONE && editmap[cursor_posY][cursor_posX] == setcell)
				return;

			if (setcell >= ECELLNUM::EPLAYER && setcell <= EBOSS){
				if (cursor_posY > 0){
					int temp_setcell = editmap[cursor_posY][cursor_posX];

					if (temp_setcell == ECELLNUM::EPLAYER){
						for (int i = 0; i < MAP_SIZEY; i++){
							for (int j = 0; j < MAP_SIZEX; j++){
								if (editmap[i][j] == EPLAYER){
									editmap[i][j] = ENONE;
									editmap_update[i][j] = UPDATE_NUM;
								}
							}
						}
					}

					if (editmap[cursor_posY - 1][cursor_posX] == setcell && editmap[cursor_posY - 2][cursor_posX] == setcell)
						return;

					else if (editmap[cursor_posY - 2][cursor_posX] == setcell && editmap[cursor_posY - 3][cursor_posX] == setcell)
						return;

					else if (editmap[cursor_posY + 1][cursor_posX] == setcell && editmap[cursor_posY + 2][cursor_posX] == setcell)
						return;

					else{
						if (editmap[cursor_posY][cursor_posX] >= EPLAYER){
							if (editmap[cursor_posY + 1][cursor_posX] == temp_setcell){
								editmap[cursor_posY][cursor_posX] = setcell;
								editmap[cursor_posY + 1][cursor_posX] = setcell;

								editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
								editmap_update[cursor_posY + 1][cursor_posX] = UPDATE_NUM;
							}
							else{
								editmap[cursor_posY][cursor_posX] = setcell;
								editmap[cursor_posY - 1][cursor_posX] = setcell;

								editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
								editmap_update[cursor_posY - 1][cursor_posX] = UPDATE_NUM;
							}
						}
						else{
							if (editmap[cursor_posY - 1][cursor_posX] >= EPLAYER && editmap[cursor_posY - 1][cursor_posX] == editmap[cursor_posY - 2][cursor_posX])
								return;
							editmap[cursor_posY][cursor_posX] = setcell;
							editmap[cursor_posY - 1][cursor_posX] = setcell;

							editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
							editmap_update[cursor_posY - 1][cursor_posX] = UPDATE_NUM;
						}
					}
				}
			}
			else{
				if (editmap[cursor_posY][cursor_posX] >= EPLAYER && editmap[cursor_posY][cursor_posX] <= EBOSS){
					int temp_setcell = editmap[cursor_posY][cursor_posX];

					if (editmap[cursor_posY + 1][cursor_posX] == temp_setcell){
						editmap[cursor_posY][cursor_posX] = setcell;
						editmap[cursor_posY + 1][cursor_posX] = ENONE;

						editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
						editmap_update[cursor_posY + 1][cursor_posX] = UPDATE_NUM;
					}
					else{
						editmap[cursor_posY][cursor_posX] = setcell;
						editmap[cursor_posY - 1][cursor_posX] = ENONE;

						editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
						editmap_update[cursor_posY - 1][cursor_posX] = UPDATE_NUM;
					}
				}
				else{
					editmap[cursor_posY][cursor_posX] = setcell;
					editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
				}
			}
			//MakeTaskList((int *)editmap);
		}

		if (CGamePad::Push(PAD_3) || CKey::Once(VK_DELETE) || CKey::Once(VK_BACK)){	//�폜
			if (editmap[cursor_posY][cursor_posX] == ENONE)
				return;
			if (editmap[cursor_posY][cursor_posX] >= EPLAYER && editmap[cursor_posY][cursor_posX] <= EBOSS){
				int temp_setcell = editmap[cursor_posY][cursor_posX];

				if (editmap[cursor_posY + 1][cursor_posX] == temp_setcell){
					editmap[cursor_posY][cursor_posX] = ENONE;
					editmap[cursor_posY + 1][cursor_posX] = ENONE;

					editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
					editmap_update[cursor_posY + 1][cursor_posX] = UPDATE_NUM;
				}
				else{
					editmap[cursor_posY][cursor_posX] = ENONE;
					editmap[cursor_posY - 1][cursor_posX] = ENONE;

					editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
					editmap_update[cursor_posY - 1][cursor_posX] = UPDATE_NUM;
				}
			}
			else{
				editmap[cursor_posY][cursor_posX] = ENONE;
				editmap_update[cursor_posY][cursor_posX] = UPDATE_NUM;
			}
			//MakeTaskList((int *)editmap);
		}

		if (CGamePad::Once(PAD_1) || CKey::Once(VK_F5)){	//�X�V
			CSE::mSoundContinue.Play();
			MakeTaskList((int *)editmap);
			for (int i = 0; i < MAP_SIZEY; i++)
				for (int j = 0; j < MAP_SIZEX; j++)
					editmap_update[i][j] = ENONE;
		}

		if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE)){
			CSE::mSoundContinue.Play();
			pauseflag = true;
		}

		if (CGamePad::Once(PAD_9) || CKey::Once('G')){
			if (guideIO)
				guideIO = false;
			else
				guideIO = true;
		}

		if (CGamePad::Once(PAD_4) || CKey::Once('R')){
			int msg_button;
			msg_button = MessageBox(NULL, "�}�b�v�����Z�b�g���܂���?\n�ۑ����Ă��Ȃ��}�b�v�͎����܂�", "�}�b�v�̃��Z�b�g", 0x00040031L);
			if (msg_button == IDYES || msg_button == IDOK){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++)
						editmap[i][j] = ENONE;
				}
				//MakeTaskList((int *)editmap);
			}
		}

		//�}�b�v�f�[�^���J��
		if (CKey::Once('O')) {
			CSE::mSoundContinue.Play();
			mMapIO.LoadDialog(NULL);
			MakeTaskList((int *)editmap);
		}

		//�}�b�v�f�[�^��ۑ�
		if (CKey::Once('P')){
			CSE::mSoundContinue.Play();
			mMapIO.SaveDialog(NULL);
		}

		if (CKey::Once('M')){
			if (prtscrIO)
				prtscrIO = false;
			else
				prtscrIO = true;
		}

		/*------ �J�[�\�� �O�ʊO �h�~ ------*/
		if (editmap_rect[cursor_posY][cursor_posX].mBottom + CELLSIZE / 2 >= 360 && cursor_posY + 1 < MAP_SIZEY){
			editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posY = cursor_posY + 1;
		}
		if (editmap_rect[cursor_posY][cursor_posX].mTop - CELLSIZE / 2 <= -360 && cursor_posY - 1 >= 0){
			editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posY = cursor_posY - 1;
		}
		if (editmap_rect[cursor_posY][cursor_posX].mLeft + CELLSIZE / 2 <= -640 && cursor_posX + 1 < MAP_SIZEX){
			editmap_cursor[cursor_posY][cursor_posX + 1] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posX = cursor_posX + 1;
		}
		if (editmap_rect[cursor_posY][cursor_posX].mRight - CELLSIZE / 2 >= 640 && cursor_posX - 1 >= 0){
			editmap_cursor[cursor_posY][cursor_posX - 1] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posX = cursor_posX - 1;
		}
	}
}

void CEditer::Render(){
	mTexBack.DrawImage(-640.0f, 640.0f, -360.0f, 360.0f, 0, 1280, 720, 0, 1.0f);
	CCamera2D mCamera;
	mCamera.SetOrtho(-editmap_rect[0][0].mRight + CELLSIZE / 2, editmap_rect[0][0].mTop + CELLSIZE, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);

	mCamera.Begin();
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Render();
	CCamera2D::End();

	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			//�K�C�h
			if (guideIO)
				mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 0, 64, 1.0f);

			//�X�V�}�X
			if (editmap_update[i][j] == UPDATE_NUM){
				if (cursor_anime >= 0 && cursor_anime < 30)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 128, 192, 1.0f);
				else if (cursor_anime >= 30 && cursor_anime < 60)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, 128, 192, 1.0f);
				else{
					int hoge = cursor_anime;
				}
			}

			//�J�[�\��
			if (editmap_cursor[i][j] == CURSOR_NUM && !prtscrIO){
				//�I�u�W�F�N�g
				//if (setcell > ENONE && setcell < EPLAYER)
				mTexSetCell.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * setcell, CELLSIZE * (setcell - 1), 0.5f);

				//�L�����N�^�[
				//if (setcell >= EPLAYER)
				//	mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * (setcell - EPLAYER + 1), CELLSIZE * (setcell - EPLAYER), 0.5f);
				if (cursor_anime >= 0 && cursor_anime < 30)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 128, 64, 1.0f);
				else if (cursor_anime >= 30 && cursor_anime < 60)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, 128, 64, 1.0f);
			}
		}
	}
	if (cursor_anime < 59)
		cursor_anime++;
	else
		cursor_anime = 0;

	if (!prtscrIO)
		CText::DrawStringW(L"�}�b�v�G�f�B�^�[", -640, 300, 48, 1.0f, 0);

	CPauseMenu::Update();
	CPauseMenu::Render();
}

void CEditer::MakeTaskList(int *gamemap) {
	static CTexture mTexUI;// .Load(".\\Data\\Images\\Map\\MapUI.tga");
	static CTexture mTexObject;// .Load(".\\Data\\Images\\Map\\MapObject.tga");
	static CTexture mTexGround;

	if (mTexUI.id == 0) {
		mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
		mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
		mTexGround.Load(".\\Data\\Images\\Map\\MapGround.tga");
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
				char colFlg = 0;
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EGROUND){
					//�� �Ȃ�, �� �Ȃ�
					if (gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND){
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//�� �Ȃ�, �� ����
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND)){
						colFlg |= EDT_BOTTOM;
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
							mapchip->mRotation = -90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != EGROUND && gamemap[i * MAP_SIZEX + j + 1] == EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//�� ����, �� �Ȃ�
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND) || (gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
						colFlg |= EDT_TOP;
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
					}
					//�� ����, �� ����
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND)){
						colFlg |= EDT_TOP | EDT_BOTTOM;
						//���E �Ȃ�
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//�� �Ȃ�, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = -90;
						}
						//�� ����, �E ����
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//�� ����, �E �Ȃ�
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
					}
					else {
						mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexGround, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
					}
					mapchip->mColFlg = colFlg;
				}
				//�����甲���鑫��
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EUNDER){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EUNDER)
						new CMapUnder(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EUNDER)
						new CMapUnder(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EUNDER && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EUNDER)
						new CMapUnder(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

					else
						new CMapUnder(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));
				}
				//�x���g�R���x�A ��
				else if (gamemap[i * MAP_SIZEX + j] == EBELTL){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, CMapBelt::ETEXTURE_POSNUM::ELEFT);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, CMapBelt::ETEXTURE_POSNUM::ECENTER);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, CMapBelt::ETEXTURE_POSNUM::ERIGHT);

					else
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, CMapBelt::ETEXTURE_POSNUM::EONE);
				}
				//�x���g�R���x�A �E
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBELTR){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, CMapBelt::ETEXTURE_POSNUM::ELEFT);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, CMapBelt::ETEXTURE_POSNUM::ECENTER);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, CMapBelt::ETEXTURE_POSNUM::ERIGHT);

					else
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, CMapBelt::ETEXTURE_POSNUM::EONE);
				}
				
				//���
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY)
					new CMapJewelry(POS(i, j));

				//��΂̌���
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY2)
					new CMapMiniJewelry(POS(i, j));

				//�����鏰
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ECHIKUWA)
					new CMapChikuwa(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

				//�X�C�b�`��1
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH_GROUND1)
					new CMapSwitchGround(POS(i, j), ECELLNUM::ESWITCH_GROUND1);

				//�X�C�b�`��2
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH_GROUND2)
					new CMapSwitchGround(POS(i, j), ECELLNUM::ESWITCH_GROUND2);

				//�`�F�b�N�|�C���g
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ECHECKPOINT)
					new CMapCheckPoint(POS(i, j));

				//�X�C�b�`
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH)
					new CMapSwitch(POS(i, j));

				//�X
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EICE){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EICE && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EICE)
						new CMapIce(POS(i, j), CMapIce::ETEXTURE_POSNUM::ELEFT);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EICE && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EICE)
						new CMapIce(POS(i, j), CMapIce::ETEXTURE_POSNUM::ECENTER);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EICE && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EICE)
						new CMapIce(POS(i, j), CMapIce::ETEXTURE_POSNUM::ERIGHT);

					else
						new CMapIce(POS(i, j), CMapIce::ETEXTURE_POSNUM::EONE);
				}

				//�v���C���[ ~ �{�X
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EPLAYER && gamemap[i * MAP_SIZEX + j] <= ECELLNUM::EBOSS){
					if (gamemap[i * MAP_SIZEX + j] == gamemap[(i - 1) * MAP_SIZEX + j]){
						//�v���C���[
						if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EPLAYER)
							new CPlayerT(POS(i, j));

						//�G1
						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY1)
							new CEnemy(POS(i, j), ECELLNUM::EENEMY1);

						//�G2
						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY2)
							new CEnemy(POS(i, j), ECELLNUM::EENEMY2);

						//�G3
						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY3)
							new CEnemy(POS(i, j), ECELLNUM::EENEMY3);

						//�{�X
						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBOSS)
							CBoss::mpBoss = new CBoss(POS(i, j));
					}
				}

				//����M�~�b�N
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EBOX && gamemap[i * MAP_SIZEX + j] < ECELLNUM::ESIGN){
					//��
					if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBOX)
						new CMapBox(POS(i, j));

					//�S��
					else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESTEEL)
						new CMapSteel(POS(i, j));
				}

				//�`���[�g���A���p �Ŕ�
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESIGN)
					new CMapSign(POS(i, j));

				//�`���[�g���A�� �I�� �Ŕ�
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENDSIGN)
					CMapEndSign::mpEndSign = new CMapEndSign(POS(i, j));

				//�{�X�̕��� �Ŕ�
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBOSSROOM)
					CMapBossRoomSign::mpBossRoomSign = new CMapBossRoomSign(POS(i, j));
			}
		}
	}

}
