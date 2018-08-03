#include "CScene.h"
#include "CGamePad.h"
#include "CCollision.h"

extern CMapIO mMapIO;
extern CCharcter player;
CCollision mCollision;

void CGame::Init(){
	//マップ 初期化
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

	mTexBack.Load(".\\Data\\Images\\Map\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\Map\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\Map\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\Map\\MapCharacter.tga");
	mMapIO.GameMapLoad(mMapIO.ETUTORIAL);
}

void CGame::Update(){
	if (!pauseflag){
		Scroll();
		//スクロール リセット
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
			//オブジェクト
			//床や壁
			if (gamemap[i][j] == EGROUND){
				if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] == EGROUND){
					//左上 下 あり
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 320, 384, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//左上 下 なし
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 64, 128, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//左中
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 512, 576, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//左下
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 704, 768, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}

				else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] == EGROUND){
					//中上 下 あり
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 384, 448, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中上 下 なし
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 128, 192, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中中
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 576, 640, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中下
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 768, 832, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}

				else if (gamemap[i][j - 1] == EGROUND && gamemap[i][j + 1] != EGROUND){
					//右上 下 あり
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 448, 512, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//右上 下 なし
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 192, 256, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//右中
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 640, 704, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//右下
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 832, 896, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}
				else if (gamemap[i][j - 1] != EGROUND && gamemap[i][j + 1] != EGROUND){
					//中上 下 あり
					if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 256, 320, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中上 下 なし
					else if (gamemap[i - 1][j] != EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中中
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 896, 960, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
					//中下
					else if (gamemap[i - 1][j] == EGROUND && gamemap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 960, 1024, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);
				}
			}

			//下から抜ける足場
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
			//ベルトコンベア
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

			//その他
			if (gamemap[i][j] >= EJEWELRY && gamemap[i][j] < EPLAYER)
				mTexObject.DrawImage(gamemap_rect[i][j].mLeft, gamemap_rect[i][j].mRight, gamemap_rect[i][j].mBottom, gamemap_rect[i][j].mTop, 0, 64, CELLSIZE * gamemap[i][j], CELLSIZE * (gamemap[i][j] - 1), 1.0f);

			//キャラクター
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
	player.Update();
	player.Render();
	CPauseMenu::Update();
	CPauseMenu::Render();
}

void CPauseMenu::Update(){
	if (pauseflag){
		if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::Once('S')) && cursor_num < ESIZE - 1)
			cursor_num++;

		if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::Once('W')) && cursor_num > EBACK)
			cursor_num--;
		if (CGamePad::Once(PAD_10) || CGamePad::Once(PAD_3) || CKey::Once(VK_ESCAPE)){
			cursor_num = EBACK;
			pauseflag = false;
		}

		if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN)){
			switch (cursor_num){
			default:
				break;

			case EBACK:
				pauseflag = false;
				cursor_num = EBACK;
				break;

			case ETITLE:
				pauseflag = false;
				CSceneChange::changenum = CSceneChange::ETITLE;
				cursor_num = EBACK;
				break;
			}
		}

		/*カーソル*/
		switch (cursor_num){
		default:
			break;

		case EBACK:
			swprintf(cursor_buf, L"→");
			break;

		case ETITLE:
			swprintf(cursor_buf, L"\n→");
			break;
		}
	}
}

void CPauseMenu::Render(){
	if (pauseflag){
		CText::DrawStringW(L" ゲームに もどる\n タイトルに もどる", -200, 100, 32, 1.0f, 0);
		CText::DrawStringW(cursor_buf, -200, 100, 32, 1.0f, 0);
	}
}