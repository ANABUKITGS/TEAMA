#include "CEditer.h"
CFileIO mFileIO;

void CEditer::Init(){
	//マップ 初期化
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
			editmap_rect[i][j].SetVertex(j * CELLSIZE - 640, j * CELLSIZE + CELLSIZE - 640, i * - CELLSIZE + 280, i * - CELLSIZE + CELLSIZE + 280, true);
		}
	}

	mTexBack.Load(".\\Data\\Images\\Background.tga");
	mTexUI.Load(".\\Data\\Images\\MapUI.tga");
	mTexObject.Load(".\\Data\\Images\\MapObject.tga");
	mTexCharacter.Load(".\\Data\\Images\\MapCharacter.tga");
}

void CEditer::Update(){
	if (CKey::Once('W') && cursor_posY - 1 >= 0){
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
	if (CKey::Once('S') && cursor_posY + 1 < EDITMAP_SIZEY){
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
	if (CKey::Once('A') && cursor_posX - 1 >= 0){
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
	if (CKey::Once('D') && cursor_posX + 1 < EDITMAP_SIZEX){
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
	if (CKey::Push('I') && cursor_posY - 1 >= 0){
		//for (int i = 0; i < EDITMAP_SIZEY; i++){
		//	for (int j = 0; j < EDITMAP_SIZEX; j++){
		//		editmap_rect[i][j].mBottom -= 16;
		//		editmap_rect[i][j].mTop -= 16;
		//	}
		//}
		if (editmap_rect[cursor_posY][cursor_posX].mTop + CELLSIZE >= 360){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mBottom -= 16;
					editmap_rect[i][j].mTop -= 16;
				}
			}
		}
		editmap_cursor[cursor_posY - 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY - 1;
	}
	if (CKey::Push('K') && cursor_posY + 1 < EDITMAP_SIZEY){
		//for (int i = 0; i < EDITMAP_SIZEY; i++){
		//	for (int j = 0; j < EDITMAP_SIZEX; j++){
		//		editmap_rect[i][j].mBottom += 16;
		//		editmap_rect[i][j].mTop += 16;
		//	}
		//}
		if (editmap_rect[cursor_posY][cursor_posX].mBottom - CELLSIZE <= -360){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++){
					editmap_rect[i][j].mBottom += 16;
					editmap_rect[i][j].mTop += 16;
				}
			}
		}
		editmap_cursor[cursor_posY + 1][cursor_posX] = CURSOR_NUM;
		editmap_cursor[cursor_posY][cursor_posX] = ENONE;
		cursor_posY = cursor_posY + 1;
	}
	if (CKey::Push('J') && cursor_posX - 1 >= 0){
		//for (int i = 0; i < EDITMAP_SIZEY; i++){
		//	for (int j = 0; j < EDITMAP_SIZEX; j++){
		//		editmap_rect[i][j].mLeft += 32;
		//		editmap_rect[i][j].mRight += 32;
		//	}
		//}
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
	if (CKey::Push('L') && cursor_posX + 1 < EDITMAP_SIZEX){
		//for (int i = 0; i < EDITMAP_SIZEY; i++){
		//	for (int j = 0; j < EDITMAP_SIZEX; j++){
		//		editmap_rect[i][j].mLeft -= 32;
		//		editmap_rect[i][j].mRight -= 32;
		//	}
		//}
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
	if (CKey::Once(VK_LEFT)){
		if (setcell <= EGROUND)
			setcell = ESIZE - 1;
		else
			setcell--;
	}
	if (CKey::Once(VK_RIGHT)){
		if (setcell >= ESIZE - 1)
			setcell = EGROUND;
		else
			setcell++;
	}
	if (CKey::Push(VK_RETURN))
		editmap[cursor_posY][cursor_posX] = setcell;

	if (CKey::Push(VK_BACK) || CKey::Push(VK_DELETE))
		editmap[cursor_posY][cursor_posX] = ENONE;

	if (CKey::Once('R')){
		int msg_button;
		msg_button = MessageBox(NULL, "マップをリセットしますか?\n保存していないマップは失われます", "マップのリセット", 0x00040031L);
		if (msg_button == IDYES || msg_button == IDOK){
			for (int i = 0; i < EDITMAP_SIZEY; i++){
				for (int j = 0; j < EDITMAP_SIZEX; j++)
					editmap[i][j] = ENONE;
			}
		}
	}

	if (CKey::Once('G')){
		if (guideIO)
			guideIO = false;
		else
			guideIO = true;
	}

	//マップデータを開く
	if (CKey::Once('O')){
		mFileIO.LoadDialog(NULL);
	}
	//マップデータを保存
	if (CKey::Once('P')){
		mFileIO.SaveDialog(NULL);
	}
	if (CKey::Push('M'))
		prtscrIO = true;
	else
		prtscrIO = false;

	/*------ カーソル 外面外 防止 ------*/
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
	mTexBack.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);

	cursor_anime++;
	for (int i = 0; i < EDITMAP_SIZEY; i++){
		for (int j = 0; j < EDITMAP_SIZEX; j++){
			//ガイド
			if (guideIO)
				mTexUI.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, 0, 64, 1.0f);

			//オブジェクト
			//床や壁
			if (editmap[i][j] == EGROUND){
				if (editmap[i][j - 1] != EGROUND && editmap[i][j + 1] == EGROUND){
					//左上 下 あり
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 320, 384, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//左上 下 なし
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 64, 128, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//左中
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 512, 576, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//左下
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 704, 768, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}

				else if (editmap[i][j - 1] == EGROUND && editmap[i][j + 1] == EGROUND){
					//中上 下 あり
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 384, 448, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中上 下 なし
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 128, 192, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中中
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 576, 640, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中下
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 768, 832, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}

				else if (editmap[i][j - 1] == EGROUND && editmap[i][j + 1] != EGROUND){
					//右上 下 あり
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 448, 512, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//右上 下 なし
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 192, 256, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//右中
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 640, 704, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//右下
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 832, 896, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}
				else if (editmap[i][j - 1] != EGROUND && editmap[i][j + 1] != EGROUND){
					//中上 下 あり
					if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 256, 320, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中上 下 なし
					else if (editmap[i - 1][j] != EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中中
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] == EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 896, 960, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
					//中下
					else if (editmap[i - 1][j] == EGROUND && editmap[i + 1][j] != EGROUND)
						mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 960, 1024, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
				}

				//else
				//	mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);
			}
			//下から抜ける足場
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
			//ベルトコンベア
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
			//その他
			if (editmap[i][j] >= EJEWELRY && editmap[i][j] < EPLAYER)
				mTexObject.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * editmap[i][j], CELLSIZE * (editmap[i][j] - 1), 1.0f);

			//キャラクター
			if (editmap[i][j] >= EPLAYER)
				mTexCharacter.DrawImage(editmap_rect[i][j].mLeft, editmap_rect[i][j].mRight, editmap_rect[i][j].mBottom, editmap_rect[i][j].mTop, 0, 64, CELLSIZE * (editmap[i][j] - EPLAYER + 1), CELLSIZE * (editmap[i][j] - EPLAYER), 1.0f);

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
}