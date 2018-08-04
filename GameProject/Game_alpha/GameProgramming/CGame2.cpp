#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CMapChip.h"
#include "CPlayerT.h"
#include "CScene.h"

#define WINDOW_SIZE_W 1280
#define WINDOW_SIZE_H 720

#define POS(Y,X) CVector2(X * CELLSIZE, Y * -CELLSIZE + WINDOW_SIZE_H)
//CVector2(j * CELLSIZE, i * CELLSIZE)

CRectangle *mapchip;

void CGame2::Init() {
	mCamera.SetOrtho(WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);
	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
	mTexPlayer.Load(".\\Data\\Images\\Map\\MapPlayer.tga");
	mTexEnemy.Load(".\\Data\Images\\Map\\MapEnemy.tga");

	char filepath[256];
//	if (map == CMapIO::EGAMEMAP)
	//	sprintf(filepath, "%s", GAME_MAP);
	//else if (map == CMapIO::ETUTORIAL)
		sprintf(filepath, "%s", TUTORIAL_MAP);
	//else if (map == CMapIO::EEDITERMAP)
	//	sprintf(filepath, "%s", EDITER_MAP);
	//else{
	//	MessageBox(NULL, "マップデータの指定がされていません。", "エラー", 0x00040010L);
	//	return;
	//}
	FILE *fp = fopen(filepath, "rb");	//ファイルを開く(読み込み)
	if (fp == NULL){	//NULLが返ってきたらエラー
		MessageBox(NULL, "マップデータの読み込みに失敗しました。", "エラー", 0x00040010L);
		printf("Load : fopen error!\n");
	}
	else {
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		int gamemap[MAP_SIZEY][MAP_SIZEX];
		//		char *buf = new char[size];	//ファイルサイズ+1バイト分の領域を確保
		fseek(fp, 0L, SEEK_SET);
		size = sizeof(gamemap);
		fread(gamemap, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
		//		buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
		fclose(fp);	//ファイルをクローズする

		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
				if (gamemap[i][j] >= ECELLNUM::ESIZE){
					MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
					for (int i = 0; i < MAP_SIZEY; i++){
						for (int j = 0; j < MAP_SIZEX; j++)
							gamemap[i][j] = ECELLNUM::ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//ファイルを閉じる
					return;
				}
				else {
					if (gamemap[i][j] == ECELLNUM::EGROUND){
						//上 なし, 下 なし
						if (gamemap[i - 1][j] != ECELLNUM::EGROUND && gamemap[i + 1][j] != ECELLNUM::EGROUND){
							//左右 なし
							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
							//左 なし, 右 あり
							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
							//左 あり, 右 あり
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
							//左 あり, 右 なし
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
						}
						//上 なし, 下 あり
						else if ((gamemap[i - 1][j] != ECELLNUM::EGROUND && gamemap[i + 1][j] == ECELLNUM::EGROUND) || (i == 0 && gamemap[i + 1][j] != ECELLNUM::EGROUND)){
							//左右 なし
							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
								mapchip->mRotation = -90;
							}
							//左 なし, 右 あり
							else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
							//左 あり, 右 あり
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
							//左 あり, 右 なし
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							}
						}
						//上 あり, 下 なし
						else if ((gamemap[i - 1][j] == ECELLNUM::EGROUND && gamemap[i + 1][j] != ECELLNUM::EGROUND) || (gamemap[i - 1][j] == ECELLNUM::EGROUND) && i == MAP_SIZEY - 1){
							//左右 なし
							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
								mapchip->mRotation = 90;
							}
							//左 なし, 右 あり
							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 3, CELLSIZE * 4, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
							}
							//左 あり, 右 あり
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
							}
							//左 あり, 右 なし
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 3, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
							}
						}
						//上 あり, 下 あり
						else if ((gamemap[i - 1][j] == ECELLNUM::EGROUND && gamemap[i + 1][j] == ECELLNUM::EGROUND)){
							//左右 なし
							if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
								mapchip->mRotation = 90;
							}
							//左 なし, 右 あり
							else if (gamemap[i][j - 1] != ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 4, CELLSIZE * 5, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
								mapchip->mRotation = -90;
							}
							//左 あり, 右 あり
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] == ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 6, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
							}
							//左 あり, 右 なし
							else if (gamemap[i][j - 1] == ECELLNUM::EGROUND && gamemap[i][j + 1] != ECELLNUM::EGROUND){
								mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 5, CELLSIZE * 4, CELLSIZE * (gamemap[i][j] - 1), CELLSIZE * gamemap[i][j]);
								mapchip->mRotation = 90;
							}
						}
						else {
							mapchip = new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
						}
					}
					//下から抜ける足場
					else if (gamemap[i][j] == ECELLNUM::EUNDER){
						if (gamemap[i][j - 1] != ECELLNUM::EUNDER && gamemap[i][j + 1] == ECELLNUM::EUNDER)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);

						else if (gamemap[i][j - 1] == ECELLNUM::EUNDER && gamemap[i][j + 1] == ECELLNUM::EUNDER)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));

						else if (gamemap[i][j - 1] == ECELLNUM::EUNDER && gamemap[i][j + 1] != ECELLNUM::EUNDER)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);

						else
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EUNDER);
					}
					//ベルトコンベア 左
					else if (gamemap[i][j] == EBELTL){
						if (gamemap[i][j - 1] != ECELLNUM::EBELTL && gamemap[i][j + 1] == ECELLNUM::EBELTL)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);

						else if (gamemap[i][j - 1] == ECELLNUM::EBELTL && gamemap[i][j + 1] == ECELLNUM::EBELTL)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);

						else if (gamemap[i][j - 1] == ECELLNUM::EBELTL && gamemap[i][j + 1] != ECELLNUM::EBELTL)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);

						else
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTL);
					}
					//ベルトコンベア 右
					else if (gamemap[i][j] == ECELLNUM::EBELTR){
						if (gamemap[i][j - 1] != ECELLNUM::EBELTR && gamemap[i][j + 1] == ECELLNUM::EBELTR)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);

						else if (gamemap[i][j - 1] == ECELLNUM::EBELTR && gamemap[i][j + 1] == ECELLNUM::EBELTR)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 3, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);

						else if (gamemap[i][j - 1] == ECELLNUM::EBELTR && gamemap[i][j + 1] != ECELLNUM::EBELTR)
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 2, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);

						else
							new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EBELTR);
					}
					//宝石 ~ スイッチ
					else if (gamemap[i][j] >= ECELLNUM::EJEWELRY && gamemap[i][j] < ECELLNUM::EPLAYER)
						new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, CELLSIZE * 0, CELLSIZE * 1, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EJEWELRY);

					//プレイヤー ~ ボス
					if (gamemap[i][j] >= ECELLNUM::EPLAYER && gamemap[i][j] < ECELLNUM::EBOX){
						int temp_setcell = gamemap[i][j];
						if (gamemap[i - 1][j] == temp_setcell && gamemap[i + 1][j] != temp_setcell){
							if (temp_setcell == ECELLNUM::EPLAYER)
								new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexPlayer, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));

							else if (temp_setcell == ECELLNUM::EENEMY1)
								new CMapChip(POS(i, j), CVector2(CELLSIZE / 2, CELLSIZE), &mTexEnemy, CELLSIZE * 1, CELLSIZE * 2, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), ECELLNUM::EENEMY1);
						}
					}

					//特殊ギミック
					if (gamemap[i][j] >= ECELLNUM::EBOX && gamemap[i][j] < ECELLNUM::ESIZE){

					}
				}
			}
		}
		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//ファイルを閉じる

	}
	new CPlayerT(CVector2(64, 264), CVector2(16, 60), NULL);
}

void CGame2::Update() {
	if (CKey::Push('D')) {
		mCamera.x += 5;
	}
	if (CKey::Push('A')) {
		mCamera.x -= 5;
	}
	if (CGamePad::Once(PAD_10))
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
	CTaskManager::Get()->Update();
}

void CGame2::Render() {
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CPlayerT::mpPlayer->mPosition.x;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();
}
