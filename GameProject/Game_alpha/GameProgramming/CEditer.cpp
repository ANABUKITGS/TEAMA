#include "CEditer.h"
#include "CGamePad.h"

CMapIO mMapIO;

void CEditer::Init(){
	//�}�b�v ������
	for (int i = 0; i < EDITMAP_SIZEY; i++){
		for (int j = 0; j < EDITMAP_SIZEX; j++){
			editmap[i][j] = ENONE;
			editmap_cursor[i][j] = ENONE;
		}
	}

	editmap_cursor[0][0] = CURSOR_NUM;
	setcell = EGROUND;
	cursor_anime = 0;
	guideIO = true;
	prtscrIO = false;

	for (int i = 0; i < EDITMAP_SIZEY; i++){
		for (int j = 0; j < EDITMAP_SIZEX; j++){
			editmap_rect[i][j].SetVertex(j * CELLSIZE - 640, j * CELLSIZE + CELLSIZE - 640, i * - CELLSIZE + 280, i * - CELLSIZE + CELLSIZE + 280);
		}
	}

	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
}

void CEditer::Update(){
	if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f)) && cursor_posY - 1 >= 0){
		if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mBottom -= 32;
					editmap_rect[i][j].mTop -= 32;
				}
			}
		}
		editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY - 1;
	}
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f)) && cursor_posY + 1 < EDITMAP_SIZEY){
		if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mBottom += 32;
					editmap_rect[i][j].mTop += 32;
				}
			}
		}
		editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY + 1;
	}
	if ((CGamePad::OncePush(PAD_LEFT) || CGamePad::OncePush(PAD_LSTICKX, -0.5f)) && cursor_posX - 1 >= 0){
		if (editmap_rect[cursor_posY][cursor_posX].mLeft - CELLSIZE <= -640){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mLeft += 32;
					editmap_rect[i][j].mRight += 32;
				}
			}
		}
		editmap_cursor[cursor_posY][cursor_posX - 1] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posX = cursor_posX - 1;
	}
	if ((CGamePad::OncePush(PAD_RIGHT) || CGamePad::OncePush(PAD_LSTICKX, 0.5f)) && cursor_posX + 1 < EDITMAP_SIZEX){
		if (editmap_rect[cursor_posY][cursor_posX].mRight + CELLSIZE / 2 >= 640){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mLeft -= 32;
					editmap_rect[i][j].mRight -= 32;
				}
			}
		}
		editmap_cursor[cursor_posY][cursor_posX + 1] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posX = cursor_posX + 1;
	}
	//if ((CKey::Push('I') || CXIn::PushStick(RSTICKY, 0.5f)) && cursor_posY - 1 >= 0){
	//	if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
	//		for (int i = 0; i < EDITMAP_SIZEY; i++){
	//			for (int j = 0; j < EDITMAP_SIZEX; j++){
	//				editmap_rect[i][j].mBottom -= 16;
	//				editmap_rect[i][j].mTop -= 16;
	//			}
	//		}
	//	}
	//	editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
	//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
	//	cursor_posY = cursor_posY - 1;
	//}
	//if ((CKey::Push('K') || CXIn::PushStick(RSTICKY, -0.5f)) && cursor_posY + 1 < EDITMAP_SIZEY){
	//	if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
	//		for (int i = 0; i < EDITMAP_SIZEY; i++){
	//			for (int j = 0; j < EDITMAP_SIZEX; j++){
	//				editmap_rect[i][j].mBottom += 16;
	//				editmap_rect[i][j].mTop += 16;
	//			}
	//		}
	//	}
	//	editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
	//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
	//	cursor_posY = cursor_posY + 1;
	//}
	//if ((CKey::Push('J') || CXIn::PushStick(RSTICKX, -0.5f)) && cursor_posX - 1 >= 0){
	//	if (editmap_rect[cursor_posY][cursor_posX].mLeft - CELLSIZE <= -640){
	//		for (int i = 0; i < EDITMAP_SIZEY; i++){
	//			for (int j = 0; j < EDITMAP_SIZEX; j++){
	//				editmap_rect[i][j].mLeft += 32;
	//				editmap_rect[i][j].mRight += 32;
	//			}
	//		}
	//	}
	//	editmap_cursor[cursor_posY][cursor_posX - 1] = CURSOR_NUM;
	//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
	//	cursor_posX = cursor_posX - 1;
	//}
	//if ((CKey::Push('L') || CXIn::PushStick(RSTICKX, 0.5f)) && cursor_posX + 1 < EDITMAP_SIZEX){
	//	if (editmap_rect[cursor_posY][cursor_posX].mRight + CELLSIZE / 2 >= 640){
	//		for (int i = 0; i < EDITMAP_SIZEY; i++){
	//			for (int j = 0; j < EDITMAP_SIZEX; j++){
	//				editmap_rect[i][j].mLeft -= 32;
	//				editmap_rect[i][j].mRight -= 32;
	//			}
	//		}
	//	}
	//	editmap_cursor[cursor_posY][cursor_posX + 1] = CURSOR_NUM;
	//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
	//	cursor_posX = cursor_posX + 1;
	//}
	if (CGamePad::OncePush(PAD_5) || CGamePad::OncePush(PAD_7)){	//�p�[�c�I��
		if (setcell <= EGROUND)
			setcell = ESIZE - 1;
		else
			setcell--;
	}
	if (CGamePad::OncePush(PAD_6) || CGamePad::OncePush(PAD_8)){	//�p�[�c�I��
		if (setcell >= ESIZE - 1)
			setcell = EGROUND;
		else
			setcell++;
	}
	if (CGamePad::Push(PAD_2)){	//�ݒu
		if (setcell >= EPLAYER){
			if (cursor_posY > 0){
				int temp_setcell = editmap[cursor_posY][cursor_posX];

				if (temp_setcell == EPLAYER){
					for (int i = 0; i < EDITMAP_SIZEY; i++){
						for (int j = 0; j < EDITMAP_SIZEX; j++){
							if (editmap[i][j] == EPLAYER)
								editmap[i][j] = ENONE;
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
						}
						else{
							editmap[cursor_posY][cursor_posX] = setcell;
							editmap[cursor_posY - 1][cursor_posX] = setcell;
						}
					}
					else{
						if (editmap[cursor_posY - 1][cursor_posX] >= EPLAYER && editmap[cursor_posY - 1][cursor_posX] == editmap[cursor_posY - 2][cursor_posX])
							return;
						editmap[cursor_posY][cursor_posX] = setcell;
						editmap[cursor_posY - 1][cursor_posX] = setcell;
					}
				}
			}
		}
		else{
			if (editmap[cursor_posY][cursor_posX] >= EPLAYER){
				int temp_setcell = editmap[cursor_posY][cursor_posX];

				if (editmap[cursor_posY + 1][cursor_posX] == temp_setcell){
					editmap[cursor_posY][cursor_posX] = setcell;
					editmap[cursor_posY + 1][cursor_posX] = ENONE;
				}
				else{
					editmap[cursor_posY][cursor_posX] = setcell;
					editmap[cursor_posY - 1][cursor_posX] = ENONE;
				}
			}
			else
				editmap[cursor_posY][cursor_posX] = setcell;
		}
	}

	if (CGamePad::Push(PAD_3)){	//�폜
		if (editmap[cursor_posY][cursor_posX] >= EPLAYER){
			int temp_setcell = editmap[cursor_posY][cursor_posX];

			if (editmap[cursor_posY + 1][cursor_posX] == temp_setcell){
				editmap[cursor_posY][cursor_posX] = ENONE;
				editmap[cursor_posY + 1][cursor_posX] = ENONE;
			}
			else{
				editmap[cursor_posY][cursor_posX] = ENONE;
				editmap[cursor_posY - 1][cursor_posX] = ENONE;
			}
		}
		else
			editmap[cursor_posY][cursor_posX] = ENONE;
	}

	if (CGamePad::Once(PAD_10)){
		int msg_button;
		msg_button = MessageBox(NULL, "�}�b�v�����Z�b�g���܂���?\n�ۑ����Ă��Ȃ��}�b�v�͎����܂�", "�}�b�v�̃��Z�b�g", 0x00040031L);
		if (msg_button == IDYES || msg_button == IDOK){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++)
					editmap[i][j] = ENONE;
			}
		}
	}

	if (CGamePad::Once(PAD_9)){
		if (guideIO)
			guideIO = false;
		else
			guideIO = true;
	}

	//�}�b�v�f�[�^���J��
	if (CKey::Once('O'))
		mMapIO.LoadDialog(NULL);

	//�}�b�v�f�[�^��ۑ�
	if (CKey::Once('P'))
		mMapIO.SaveDialog(NULL);

	if (CKey::Once('M')){
		if (prtscrIO)
			prtscrIO = false;
		else
			prtscrIO = true;
	}

	/*------ �J�[�\�� �O�ʊO �h�~ ------*/
	if (editmap_rect[cursor_posY][cursor_posX].mBottom + CELLSIZE / 2 >= 360 && cursor_posY + 1 < EDITMAP_SIZEY){
		editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY + 1;
	}
	if (editmap_rect[cursor_posY][cursor_posX].mTop - CELLSIZE / 2 <= -360 && cursor_posY - 1 >= 0){
		editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY - 1;
	}
	if (editmap_rect[cursor_posY][cursor_posX].mLeft + CELLSIZE / 2 <= -640 && cursor_posX + 1 < EDITMAP_SIZEX){
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

void CEditer::Render(){
	mTexBack.DrawImage(TEX_FULLSCREEN, 0, 1280, 720, 0, 1.0f);

	cursor_anime++;
	for (int i = 0; i < EDITMAP_SIZEY; i++){
		for (int j = 0; j < EDITMAP_SIZEX; j++){
			//�K�C�h
			if (guideIO)
				mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 0, 64, 1.0f);

			//�I�u�W�F�N�g
			//�����
			if (editmap[i][j] == EGROUND){
				if (editmap[i][j - 1] != EGROUND && editmap[i][j + 1] == EGROUND){
					//���� �� ����
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 320, 384, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 512, 576, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 704, 768, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}

				else if (editmap[i][j - 1] == EGROUND && editmap[i][j + 1] == EGROUND){
					//���� �� ����
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 384, 448, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 576, 640, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 768, 832, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}

				else if (editmap[i][j - 1] == EGROUND && editmap[i][j + 1] != EGROUND){
					//�E�� �� ����
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 448, 512, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//�E�� �� �Ȃ�
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//�E��
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 640, 704, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//�E��
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 832, 896, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}
				else if (editmap[i][j - 1] != EGROUND && editmap[i][j + 1] != EGROUND){
					//���� �� ����
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 256, 320, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 896, 960, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//����
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 960, 1024, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}
			}

			//�����甲���鑫��
			if (editmap[i][j] == EUNDER){
				if (editmap[i][j - 1] != EUNDER && editmap[i][j + 1] == EUNDER)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else if (editmap[i][j - 1] == EUNDER && editmap[i][j + 1] == EUNDER)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else if (editmap[i][j - 1] == EUNDER && editmap[i][j + 1] != EUNDER)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			}
			//�x���g�R���x�A
			if (editmap[i][j] == EBELT){
				if (editmap[i][j - 1] != EBELT && editmap[i][j + 1] == EBELT)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else if (editmap[i][j - 1] == EBELT && editmap[i][j + 1] == EBELT)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else if (editmap[i][j - 1] == EBELT && editmap[i][j + 1] != EBELT)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

				else
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			}

			//���̑�
			if (editmap[i][j] >= EJEWELRY && editmap[i][j] < EPLAYER)
				mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

			//�L�����N�^�[
			if (editmap[i][j] >= EPLAYER){
				int temp_setcell = editmap[i][j];

				if (editmap[i - 1][j] == temp_setcell && editmap[i + 1][j] != temp_setcell)
				mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);

				else if (editmap[i + 1][j] == temp_setcell && editmap[i - 1][j] != temp_setcell)
					mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);
				
				else
					mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);
			}

			//�J�[�\��
			if (editmap_cursor[i][j] == CURSOR_NUM && !prtscrIO){
				//�I�u�W�F�N�g
				if (setcell > ENONE && setcell < EPLAYER)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * setcell, CELLSIZE * (setcell - 1), 0.5f);

				//�L�����N�^�[
				if (setcell >= EPLAYER)
					mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * (setcell - EPLAYER + 1), CELLSIZE * (setcell - EPLAYER), 0.5f);
				if (cursor_anime >= 0 && cursor_anime < 30)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 128, 64, 1.0f);
				else if (cursor_anime >= 30 && cursor_anime < 60)
					mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, 128, 64, 1.0f);
				else if (cursor_anime >= 60)
					cursor_anime = 0;
			}
		}
	}
	if (!prtscrIO)
		CText::DrawStringW(L"�}�b�v�G�f�B�^�[", -640, 300, 48, 1.0f, 0);
}