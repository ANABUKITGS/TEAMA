#ifndef CGAME2_H
#define CGAME2_H

#include "CMap.h"
#include "CTaskManager.h"
#include "CCamera2D.h"


#define TUTORIAL_MAP	".\\Data\\Map\\MAP0.BIN"	//チュートリアルマップ ファイルパス
#define GAME_MAP		".\\Data\\Map\\MAP1.BIN"	//ゲームマップ ファイルパス
#define EDITER_MAP		".\\Data\\Map\\MAP2.BIN"	//エディットマップ ファイルパス


class CGame2 : public CEditer {
public:
	CCamera2D mCamera;

	CTexture mTexBack;								//背景
	CTexture mTexUI;								//UI テクスチャー
	CTexture mTexObject;							//UI オブジェクト
	CTexture mTexCharacter;							//UI キャラクター

//	bool mapsctoll_flag;							//スクロール 開始

	void Init();
	void Update();
	void Scroll();
	void Render();
};

#endif
