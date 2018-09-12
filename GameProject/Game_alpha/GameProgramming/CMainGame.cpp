#include "CScene.h"
#include "CGamePad.h"
#include "CCollision.h"
#include "CBGM.h"
#include "CFade.h"

extern CMapIO mMapIO;
extern CCharcter player;
CCollision mCollision;

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
	pauseflag = false;
	//mMapIO.GameMapLoad(mMapIO.ETUTORIAL);
}

void CGame::Update(){
	if (!pauseflag){
		Scroll();
		//�X�N���[�� ���Z�b�g
		if (CGamePad::Once(PAD_1) || CKey::Once('R')){
			mapsctoll_flag = false;
			for (int i = 0; i < MAP_SIZEY; i++){
				for (int j = 0; j < MAP_SIZEX; j++){
					gamemap_rect[i][j].mLeft += mapscrollnum;
					gamemap_rect[i][j].mRight += mapscrollnum;
				}
			}
			mapscrollnum = 0;
		}
		if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE)){
			pauseflag = true;
		}
	}
}

void CGame::Scroll(){
	if (mapsctoll_flag){
		mapscrollnum += 2;
		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				gamemap_rect[i][j].mLeft -= 2;
				gamemap_rect[i][j].mRight -= 2;
			}
		}
	}
}

void CGame::Render(){
	//mTexBack.DrawImage(TEX_FULLSCREEN, 0, 1280, 720, 0, 1.0f);

	//for (int i = 0; i < MAP_SIZEY; i++){
	//	for (int j = 0; j < MAP_SIZEX; j++){	
	//		//�I�u�W�F�N�g
	//		//�����
	//		if (gamemap[i][j] == EGROUND){
	//			if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
	//				//���� �� ����
	//				if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//���� �� �Ȃ�
	//				else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//			}
	//
	//			else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] == EGROUND){
	//				//���� �� ����
	//				if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//���� �� �Ȃ�
	//				else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//			}
	//
	//			else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] != EGROUND){
	//				//�E�� �� ����
	//				if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//�E�� �� �Ȃ�
	//				else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//�E��
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//�E��
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//			}
	//			else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] != EGROUND){
	//				//���� �� ����
	//				if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//���� �� �Ȃ�
	//				else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//				//����
	//				else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
	//					mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//			}
	//		}
	//
	//		//�����甲���鑫��
	//		if (gamemap[i][j] == EUNDER){
	//			if (gamemap[i][j - 1] != EUNDER && gamemap[i][j + 1] == EUNDER)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] == EUNDER)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else if (gamemap[i][j - 1] == EUNDER && gamemap[i][j + 1] != EUNDER)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//		}
	//		//�x���g�R���x�A
	//		if (gamemap[i][j] == EBELTL){
	//			if (gamemap[i][j - 1] != EBELTL && gamemap[i][j + 1] == EBELTL)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else if (gamemap[i][j - 1] == EBELTL && gamemap[i][j + 1] == EBELTL)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else if (gamemap[i][j - 1] == EBELTL && gamemap[i][j + 1] != EBELTL)
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//			else
	//				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//		}
	//
	//		//���̑�
	//		if (gamemap[i][j] >= EJEWELRY && gamemap[i][j] < EPLAYER)
	//			mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
	//
	//		//�L�����N�^�[
	//		if (gamemap[i][j] >= EPLAYER){
	//			int temp_setcell = gamemap[i][j];
	//
	//			if (gamemap[i - 1][j] == temp_setcell && gamemap[i + 1][j] != temp_setcell)
	//			mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
	//
	//			else if (gamemap[i + 1][j] == temp_setcell && gamemap[i - 1][j] != temp_setcell)
	//				mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
	//			
	//			else
	//				mTexCharacter.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * (gamemap[i][j] - EPLAYER + 1), CELLSIZE * (gamemap[i][j] - EPLAYER), 1.0f);
	//		}
	//	}
	//}
	//player.Update();
	//player.Render();
	CPauseMenu::Update();
	CPauseMenu::Render();
}

void CPauseMenu::Update(){
	if (pauseflag){
		if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::Once('S') || CKey::Once(VK_UP)) && cursor_num < ESIZE - 1){
			CSE::mSoundSelect.Play();
			cursor_num++;
		}
		if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::Once('W') || CKey::Once(VK_DOWN)) && cursor_num > EBACK){
			CSE::mSoundSelect.Play();
			cursor_num--;
		}
		if (CGamePad::Once(PAD_10) || CGamePad::Once(PAD_3) || CKey::Once(VK_ESCAPE)){
			cursor_num = EBACK;
			pauseflag = false;
		}

		if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN) || CKey::Once(VK_SPACE)){
			CSE::mSoundContinue.Play();
			switch (cursor_num){
			case EBACK:
				pauseflag = false;
				cursor_num = EBACK;
				break;

			case ETITLE:
				pauseflag = false;
				cursor_num = EBACK;
				CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
				break;

			default:
				break;
			}
		}
	}
}

void CPauseMenu::Render(){
	if (pauseflag){
		mTexBack.DrawImageSetColor(-640.0f, 640.0f, -360.0f, 360.0f, 0, 0, 0, 0, BLACK, 0.5f);
		/*�J�[�\��*/
		switch (cursor_num){
		case EBACK:
			CText::DrawStringWSetColor(L"�Q�[���� ���ǂ�", -16 * 8, 0, 32, 0.2f, 0.8f, 0.4f, 1.0f, 0);
			CText::DrawStringWSetColor(L"�^�C�g���� ���ǂ�", -16 * 9, -32, 32, WHITE, 1.0f, 0);
			break;

		case ETITLE:
			CText::DrawStringWSetColor(L"�Q�[���� ���ǂ�", -16 * 8, 0, 32, WHITE, 1.0f, 0);
			CText::DrawStringWSetColor(L"�^�C�g���� ���ǂ�", -16 * 9, -32, 32, 0.2f, 0.8f, 0.4f, 1.0f, 0);
			break;

		default:
			break;
		}
	}
}