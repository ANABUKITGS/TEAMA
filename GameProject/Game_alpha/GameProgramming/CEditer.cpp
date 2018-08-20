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

#include "CBGM.h"

CEnemy *CEnemy::mpEnemy = 0;
CMapIO mMapIO;

void CEditer::Init(){
	//マップ 初期化
	for (int i = 0; i < MAP_SIZEY; i++){
		for (int j = 0; j < MAP_SIZEX; j++){
			editmap[i][j] = ENONE;
			editmap_cursor[i][j] = ENONE;
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
			if (editmap[cursor_posY][cursor_posX] != ENONE && editmap[cursor_posY][cursor_posX] == setcell)
				return;

			if (setcell >= ECELLNUM::ECHECKPOINT && setcell <= EBOSS){
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
				if (editmap[cursor_posY][cursor_posX] >= EPLAYER && editmap[cursor_posY][cursor_posX] <= EBOSS){
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
			MakeTaskList((int *)editmap);
		}

		if (CGamePad::Push(PAD_3)){	//削除
			if (editmap[cursor_posY][cursor_posX] == ENONE)
				return;
			if (editmap[cursor_posY][cursor_posX] >= EPLAYER && editmap[cursor_posY][cursor_posX] <= EBOSS){
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
			MakeTaskList((int *)editmap);
		}

		if (CGamePad::Once(PAD_10)){
			pauseflag = true;
		}

		if (CGamePad::Once(PAD_9)){
			if (guideIO)
				guideIO = false;
			else
				guideIO = true;
		}

		if (CGamePad::Once(PAD_4)){
			int msg_button;
			msg_button = MessageBox(NULL, "マップをリセットしますか?\n保存していないマップは失われます", "マップのリセット", 0x00040031L);
			if (msg_button == IDYES || msg_button == IDOK){
				for (int i = 0; i < MAP_SIZEY; i++){
					for (int j = 0; j < MAP_SIZEX; j++)
						editmap[i][j] = ENONE;
				}
				MakeTaskList((int *)editmap);
			}
		}

		//マップデータを開く
		if (CKey::Once('O')) {
			mMapIO.LoadDialog(NULL);
			MakeTaskList((int *)editmap);
		}

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

			//カーソル
			if (editmap_cursor[i][j] == CURSOR_NUM && !prtscrIO){
				//オブジェクト
				//if (setcell > ENONE && setcell < EPLAYER)
				mTexSetCell.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * setcell, CELLSIZE * (setcell - 1), 0.5f);

				//キャラクター
				//if (setcell >= EPLAYER)
				//	mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * (setcell - EPLAYER + 1), CELLSIZE * (setcell - EPLAYER), 0.5f);
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
				char colFlg = 0;
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EGROUND){
					//上 なし, 下 なし
					if (gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND){
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//上 なし, 下 あり
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND)){
						colFlg |= EDT_BOTTOM;
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
							mapchip->mRotation = -90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != EGROUND && gamemap[i * MAP_SIZEX + j + 1] == EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
						}
					}
					//上 あり, 下 なし
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] != ECELLNUM::EGROUND) || (gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
						colFlg |= EDT_TOP;
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
					}
					//上 あり, 下 あり
					else if ((gamemap[(i - 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND && gamemap[(i + 1) * MAP_SIZEX + j] == ECELLNUM::EGROUND)){
						colFlg |= EDT_TOP | EDT_BOTTOM;
						//左右 なし
						if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
						//左 なし, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = -90;
						}
						//左 あり, 右 あり
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EGROUND){
							colFlg |= EDT_RIGHT | EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
						}
						//左 あり, 右 なし
						else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EGROUND && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EGROUND){
							colFlg |= EDT_LEFT;
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), CELLSIZE * gamemap[i * MAP_SIZEX + j]);
							mapchip->mRotation = 90;
						}
					}
					else {
						mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));
					}
					mapchip->mColFlg = colFlg;
				}
				//下から抜ける足場
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
				//ベルトコンベア 左
				else if (gamemap[i * MAP_SIZEX + j] == EBELTL){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, 1);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, 2);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTL && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTL)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, 3);

					else
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTL, 4);
				}
				//ベルトコンベア 右
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EBELTR){
					if (gamemap[i*MAP_SIZEX + j - 1] != ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, 1);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] == ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, 2);

					else if (gamemap[i*MAP_SIZEX + j - 1] == ECELLNUM::EBELTR && gamemap[i * MAP_SIZEX + j + 1] != ECELLNUM::EBELTR)
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, 3);

					else
						new CMapBelt(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::EBELTR, 4);
				}
				
				//宝石
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY)
					new CMapJewelry(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject);

				//宝石
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EJEWELRY2)
					new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1), ECELLNUM::EJEWELRY2);

				//落ちる床
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ECHIKUWA)
					new CMapChikuwa(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

				//スイッチ床1
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH_GROUND1)
					new CMapSwitchGround(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::ESWITCH_GROUND1);

				//スイッチ床2
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH_GROUND2)
					new CMapSwitchGround(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), ECELLNUM::ESWITCH_GROUND2);

				//スイッチ
				else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESWITCH)
					new CMapSwitch(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i * MAP_SIZEX + j], CELLSIZE * (gamemap[i * MAP_SIZEX + j] - 1));

				//プレイヤー ~ ボス
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EPLAYER && gamemap[i * MAP_SIZEX + j] <= ECELLNUM::EBOSS){
					if (gamemap[i * MAP_SIZEX + j] == gamemap[(i - 1) * MAP_SIZEX + j]){
						if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EPLAYER)
							new CPlayerT(POS(i, j), CVector2(16, 60), NULL);

						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY1)
							new CEnemy(POS(i, j), CVector2(32, 64), NULL);

						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY2)
							new CEnemy(POS(i, j), CVector2(32, 64), NULL);

						else if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::EENEMY3)
							new CEnemy(POS(i, j), CVector2(32, 64), NULL);
					}
				}

				//特殊ギミック
				if (gamemap[i * MAP_SIZEX + j] >= ECELLNUM::EBOX && gamemap[i * MAP_SIZEX + j] < ECELLNUM::ESIGN){

				}

				//チュートリアル用 看板
				if (gamemap[i * MAP_SIZEX + j] == ECELLNUM::ESIGN){
					new CMapSign(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2));

				}
			}
		}
	}

}
