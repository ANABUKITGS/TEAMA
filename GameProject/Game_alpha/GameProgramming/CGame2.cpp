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
		fread(gamemap, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
		//		buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
		fclose(fp);	//ファイルをクローズする

		for (int i = 0; i < MAP_SIZEY; i++){
			for (int j = 0; j < MAP_SIZEX; j++){
				//				fread(&mGame.gamemap[i][j], sizeof(int), 1, fp);
				if (gamemap[i][j] >= CEditer::ESIZE){
					MessageBox(NULL, "マップデータが破損しているか、違うファイルです。", "エラー", 0x00040010L);
					for (int i = 0; i < MAP_SIZEY; i++){
						for (int j = 0; j < MAP_SIZEX; j++)
							gamemap[i][j] = CEditer::ENONE;
					}
					char loadmsg[MAX_PATH + 8];
					sprintf(loadmsg, "Load to %s\n", filepath);
					printf(loadmsg);
					fclose(fp);	//ファイルを閉じる
					return;
				}
				else {
					if (gamemap[i][j] == EGROUND){
						if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
							//左上 下 あり
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//左上 下 なし
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//左中
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//左下
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}

						else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] == EGROUND){
							//中上 下 あり
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中上 下 なし
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中中
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中下
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}

						else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] != EGROUND){
							//右上 下 あり
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//右上 下 なし
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//右中
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//右下
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}
						else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] != EGROUND){
							//中上 下 あり
							if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中上 下 なし
							else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中中
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
							//中下
							else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
								new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
							// mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
						}
					}

					//下から抜ける足場
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
					//ベルトコンベア
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

					//その他
					if (gamemap[i][j] >= EJEWELRY && gamemap[i][j] < EPLAYER)
						new CMapChip(CVector2(j * CELLSIZE, i * CELLSIZE), CVector2(CELLSIZE / 2, CELLSIZE / 2), &mTexObject, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1));
					//	mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

					//キャラクター
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
		fclose(fp);	//ファイルを閉じる

	}
}

void CGame2::Update() {
	CTaskManager::Get()->Update();
}

void CGame2::Render() {
	CTaskManager::Get()->Render();
}
