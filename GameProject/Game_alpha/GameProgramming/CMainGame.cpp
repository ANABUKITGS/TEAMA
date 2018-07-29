#include "CMap.h"
#include "CGamePad.h"

extern CMapIO mMapIO;
extern CCharcter player;

void CGame::Init(){
	//�}�b�v ������
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			gamemap[i][j] = ENONE;
		}
	}

	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			gamemap_rect[i][j].SetVertex(j * CELLSIZE - 640, j * CELLSIZE + CELLSIZE - 640, i * - CELLSIZE + 280, i * - CELLSIZE + CELLSIZE + 280);
		}
	}
	mapsctoll_flag = false;

	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
	mMapIO.GameMapLoad(mMapIO.ETUTORIAL);
}

void CGame::Update(){
	Scroll();
	if (CGamePad::Once(PAD_10)){
		mapsctoll_flag = false;
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				gamemap_rect[i][j].mLeft += mapscrollnum;
				gamemap_rect[i][j].mRight += mapscrollnum;
			}
		}
		mapscrollnum = 0;
	}
}

void CGame::Scroll(){
	if (mapsctoll_flag){
		mapscrollnum += SCROLL_SPEED;
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				gamemap_rect[i][j].mLeft -= SCROLL_SPEED;
				gamemap_rect[i][j].mRight -= SCROLL_SPEED;
			}
		}
	}
}

void CGame::Render(){
	mTexBack.DrawImage(TEX_FULLSCREEN, 0, 1280, 720, 0, 1.0f);

	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){	
			//�I�u�W�F�N�g
			//�����
			if (gamemap[i][j] == EGROUND){
				if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
					//���� �� ����
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}

				else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] == EGROUND){
					//���� �� ����
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}

				else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] != EGROUND){
					//�E�� �� ����
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//�E�� �� �Ȃ�
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//�E��
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//�E��
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}
				else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] != EGROUND){
					//���� �� ����
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//���� �� �Ȃ�
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//����
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}
			}

			//�����甲���鑫��
			if (gamemap[i][j] == EUNDER){
				if (gamemap[i][j - 1] != EUNDER && gamemap[i][j + 1] == EUNDER)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] == EUNDER)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] != EUNDER)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
			}
			//�x���g�R���x�A
			if (gamemap[i][j] == EBELT){
				if (gamemap[i][j - 1] != EBELT && gamemap[i][j + 1] == EBELT)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else if (gamemap[i][j - 1] == EBELT && gamemap[i][j + 1] == EBELT)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else if (gamemap[i][j - 1] == EBELT && gamemap[i][j + 1] != EBELT)
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

				else
					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
			}

			//���̑�
			if (gamemap[i][j] >= EJEWELRY && gamemap[i][j] < EPLAYER)
				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

			//�L�����N�^�[
			if (gamemap[i][j] >= EPLAYER){
				int temp_setcell = gamemap[i][j];

				if (gamemap[i - 1][j] == temp_setcell && gamemap[i + 1][j] != temp_setcell)
				mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);

				else if (gamemap[i + 1][j] == temp_setcell && gamemap[i - 1][j] != temp_setcell)
					mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
				
				else
					mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
			}
		}
	}
}