#ifndef CSCENEGAME2_H
#define CSCENEGAME2_H
//シーンクラス
#include "CScene.h"
//動的配列
#include <vector>
//キャラクタクラス
#include "CCharacter.h"

#include "CSound.h"

#include "CGamePad.h"


//ゲームクラス
class CSceneGame2 : public CScene {
	//vector 動的配列
	std::vector<CCharacter*> mCharacters;
	//使用するテクスチャ
	CTexture mTexImage;
	//カメラの設定
	void SetCamera();
public:
	//サウンドの変数
	CSound mSound;
	void Init();
	void Update();
	EScene GetNextScene();
	//UI画面の表示
	void UI();

	static CGamePad mGamePad;

};

#endif
