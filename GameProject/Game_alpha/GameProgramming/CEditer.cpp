#include "CScene.h"
#include "CGamePad.h"

#include "CCamera2D.h"
#include "CMapChip.h"
#include "CMapJewelry.h"

CMapIO mMapIO;

void CEditer::Init(){
	//マップ 初期化
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			editmap[i][j] = ENONE;
			editmap_cursor[i][j] = ENONE;
		}
	}

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

	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
}

void CEditer::Update(){
	if (!pauseflag){
		if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f)) && cursor_posY - 1 >= 0){
			if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++){
						editmap_rect[i][j].mBottom -= 32;
						editmap_rect[i][j].mTop -= 32;
					}
				}
			}
			editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
			editmap_cursor[cursor_posY][cursor_posX] = ENONE;
			cursor_posY = cursor_posY - 1;
		}
		if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f)) && cursor_posY + 1 < MAP_SIZEY){
			if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++){
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
		if ((CGamePad::OncePush(PAD_RIGHT) || CGamePad::OncePush(PAD_LSTICKX, 0.5f)) && cursor_posX + 1 < MAP_SIZEX){
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
		//if ((CKey::Push('I') || CXIn::PushStick(RSTICKY, 0.5f)) && cursor_posY - 1 >= 0){
		//	if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
		//		for (int i = 0; i < MAP_SIZEY; i++){
		//			for (int j = 0; j < MAP_SIZEX; j++){
		//				editmap_rect[i][j].mBottom -= 16;
		//				editmap_rect[i][j].mTop -= 16;
		//			}
		//		}
		//	}
		//	editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
		//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		//	cursor_posY = cursor_posY - 1;
		//}
		//if ((CKey::Push('K') || CXIn::PushStick(RSTICKY, -0.5f)) && cursor_posY + 1 < MAP_SIZEY){
		//	if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
		//		for (int i = 0; i < MAP_SIZEY; i++){
		//			for (int j = 0; j < MAP_SIZEX; j++){
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
		//		for (int i = 0; i < MAP_SIZEY; i++){
		//			for (int j = 0; j < MAP_SIZEX; j++){
		//				editmap_rect[i][j].mLeft += 32;
		//				editmap_rect[i][j].mRight += 32;
		//			}
		//		}
		//	}
		//	editmap_cursor[cursor_posY][cursor_posX - 1] = CURSOR_NUM;
		//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		//	cursor_posX = cursor_posX - 1;
		//}
		//if ((CKey::Push('L') || CXIn::PushStick(RSTICKX, 0.5f)) && cursor_posX + 1 < MAP_SIZEX){
		//	if (editmap_rect[cursor_posY][cursor_posX].mRight + CELLSIZE / 2 >= 640){
		//		for (int i = 0; i < MAP_SIZEY; i++){
		//			for (int j = 0; j < MAP_SIZEX; j++){
		//				editmap_rect[i][j].mLeft -= 32;
		//				editmap_rect[i][j].mRight -= 32;
		//			}
		//		}
		//	}
		//	editmap_cursor[cursor_posY][cursor_posX + 1] = CURSOR_NUM;
		//	editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		//	cursor_posX = cursor_posX + 1;
		//}
		if (CGamePad::OncePush(PAD_5) || CGamePad::OncePush(PAD_7)){	//パーツ選択
			if (setcell <= EGROUND)
				setcell = ECELLNUM::ESIZE - 1;
			else
				setcell--;
		}
		if (CGamePad::OncePush(PAD_6) || CGamePad::OncePush(PAD_8)){	//パーツ選択
			if (setcell >= ECELLNUM::ESIZE - 1)
				setcell = ECELLNUM::EGROUND;
			else
				setcell++;
		}
		if (CGamePad::Push(PAD_2)){	//設置
			if (setcell >= ECELLNUM::EPLAYER){
				if (cursor_posY > 0){
					int temp_setcell = editmap[cursor_posY][cursor_posX];

					if (temp_setcell == ECELLNUM::EPLAYER){
						for (int i = 0; i < MAP_SIZEY; i++){
							for (int j = 0; j < MAP_SIZEX; j++){
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

		if (CGamePad::Push(PAD_3)){	//削除
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
			//int msg_button;
			//msg_button = MessageBox(NULL, "マップをリセットしますか?\n保存していないマップは失われます", "マップのリセット", 0x00040031L);
			//if (msg_button == IDYES || msg_button == IDOK){
			//	for (int i = 0; i < MAP_SIZEY; i++){
			//		for (int j = 0; j < MAP_SIZEX; j++)
			//			editmap[i][j] = ENONE;
			//	}
			//}
			pauseflag = true;
		}

		if (CGamePad::Once(PAD_9)){
			if (guideIO)
				guideIO = false;
			else
				guideIO = true;
		}

		//マップデータを開く
		if (CKey::Once('O'))
			mMapIO.LoadDialog(NULL);

		//マップデータを保存
		if (CKey::Once('P'))
			mMapIO.SaveDialog(NULL);

		if (CKey::Once('M')){
			if (prtscrIO)
				prtscrIO = false;
			else
				prtscrIO = true;
		}

		/*------ カーソル 外面外 防止 ------*/
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
	CCamera2D mCamera;
	mCamera.SetOrtho(-editmap_rect[0][0].mRight + CELLSIZE / 2, editmap_rect[0][0].mTop + CELLSIZE, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);

	mTexBack.DrawImage(TEX_FULLSCREEN, 0, 1280, 720, 0, 1.0f);

	MakeTaskList((int *)editmap);
	mCamera.Begin();
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Render();
	CCamera2D::End();

	cursor_anime++;
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			//ガイド
			if (guideIO)
				mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 0, 64, 1.0f);

			////オブジェクト
			////床や壁
			//if (editmap[i][j] == ECELLNUM::EGROUND){
			//	//上 なし, 下 なし
			//	if (editmap[i - 1][j] != ECELLNUM::EGROUND && editmap[i + 1][j] != ECELLNUM::EGROUND){
			//		//左右 なし
			//		if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 なし, 右 あり
			//		else if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 あり, 右 あり
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 あり, 右 なし
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//	}
			//	//上 なし, 下 あり
			//	else if ((editmap[i - 1][j] != ECELLNUM::EGROUND && editmap[i + 1][j] == ECELLNUM::EGROUND) || (i == 0 && editmap[i + 1][j] != ECELLNUM::EGROUND)){
			//		//左右 なし
			//		if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 なし, 右 あり
			//		else if (editmap[i][j - 1] != EGROUND && editmap[i][j + 1] == EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 あり, 右 あり
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//		//左 あり, 右 なし
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//		}
			//	}
			//	//上 あり, 下 なし
			//	else if ((editmap[i - 1][j] == ECELLNUM::EGROUND && editmap[i + 1][j] != ECELLNUM::EGROUND) || (editmap[i - 1][j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
			//		//左右 なし
			//		if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 なし, 右 あり
			//		else if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 あり, 右 あり
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 あり, 右 なし
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//	}
			//	//上 あり, 下 あり
			//	else if ((editmap[i - 1][j] == ECELLNUM::EGROUND && editmap[i + 1][j] == ECELLNUM::EGROUND)){
			//		//左右 なし
			//		if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 なし, 右 あり
			//		else if (editmap[i][j - 1] != ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 あり, 右 あり
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] == ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//		//左 あり, 右 なし
			//		else if (editmap[i][j - 1] == ECELLNUM::EGROUND && editmap[i][j + 1] != ECELLNUM::EGROUND){
			//			mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (editmap[i][j] - 1), CELLSIZE * editmap[i][j], 1.0f);
			//		}
			//	}
			//	else {
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	}
			//}
			////下から抜ける足場
			//if (editmap[i][j] == EUNDER){
			//	if (editmap[i][j - 1] != EUNDER && editmap[i][j + 1] == EUNDER)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EUNDER && editmap[i][j + 1] == EUNDER)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EUNDER && editmap[i][j + 1] != EUNDER)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//}
			////ベルトコンベア 左
			//if (editmap[i][j] == EBELTL){
			//	if (editmap[i][j - 1] != EBELTL && editmap[i][j + 1] == EBELTL)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EBELTL && editmap[i][j + 1] == EBELTL)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EBELTL && editmap[i][j + 1] != EBELTL)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//}
			////ベルトコンベア 右
			//if (editmap[i][j] == EBELTR){
			//	if (editmap[i][j - 1] != EBELTR && editmap[i][j + 1] == EBELTR)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EBELTR && editmap[i][j + 1] == EBELTR)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else if (editmap[i][j - 1] == EBELTR && editmap[i][j + 1] != EBELTR)
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//	else
			//		mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			//}
			////その他
			//if (editmap[i][j] >= EJEWELRY && editmap[i][j] < EPLAYER)
			//	mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			////キャラクター
			//if (editmap[i][j] >= EPLAYER){
			//	int temp_setcell = editmap[i][j];
			//	if (editmap[i - 1][j] == temp_setcell && editmap[i + 1][j] != temp_setcell)
			//	mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);
			//	else if (editmap[i + 1][j] == temp_setcell && editmap[i - 1][j] != temp_setcell)
			//		mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);
			//	
			//	else
			//		mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);
			//}

			//カーソル
			if (editmap_cursor[i][j] == CURSOR_NUM && !prtscrIO){
				//オブジェクト
				if (setcell > ENONE && setcell < EPLAYER)
					mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * setcell, CELLSIZE * (setcell - 1), 0.5f);

				//キャラクター
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
		CText::DrawStringW(L"マップエディター", -640, 300, 48, 1.0f, 0);

	CPauseMenu::Update();
	CPauseMenu::Render();
}

void CEditer::MakeTaskList(int *gamemap) {

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

	CRectangle *mapchip;	//Initでしか使用していないので、Initメソッドのローカル変数で宣言
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
			if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::ESIZE){
				MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++)
						gamemap[i * MAP_SIZEX + j] = ECELLNUM::ENONE;
				}
				//				char loadmsg[MAX_PATH + 8];
				//				sprintf(loadmsg, "Load to %s\n", filepath);
				//				printf(loadmsg);
				//				fclose(fp);	//ファイルを閉じる
				return;
			}
			else {
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EGROUND){
					//上 なし, 下 なし
					if (gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND){
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//上 なし, 下 あり
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND)){
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
							mapchip->mRotation = -90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != EGROUND && gamemap[i * MAP_SIZEX + j + 1] == EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//上 あり, 下 なし
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND) || (gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
					}
					//上 あり, 下 あり
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND)){
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = -90;
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
					}
					else {
						mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
					}
				}
				//下から抜ける足場
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
				//ベルトコンベア 左
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
				//ベルトコンベア 右
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
				//宝石 ~ スイッチ
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY)
					//						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EJEWELRY);
					new CMapJewelry(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject);

				else if (gamemap[i * MAP_SIZEX + j] > ECELLNUM::EJEWELRY && gamemap[i * MAP_SIZEX + j] < ECELLNUM::EPLAYER)
					new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EJEWELRY);

				//プレイヤー ~ ボス
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EPLAYER && gamemap[i * MAP_SIZEX + j] < ECELLNUM::EBOX){
					int temp_setcell = gamemap[i * MAP_SIZEX + j];
					if (gamemap[(i - 1) * MAP_SIZEX + j] == temp_setcell && gamemap[(i + 1) * MAP_SIZEX + j] != temp_setcell){
						if (temp_setcell == ECELLNUM::EPLAYER)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexPlayer, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));

						else if (temp_setcell == ECELLNUM::EENEMY1)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexEnemy, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EENEMY1);
					}
				}

				//特殊ギミック
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EBOX && gamemap[i * MAP_SIZEX + j] < ECELLNUM::ESIZE){

				}
			}
		}
	}

}
