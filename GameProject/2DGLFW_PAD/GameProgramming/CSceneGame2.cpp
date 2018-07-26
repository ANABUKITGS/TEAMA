#include "CSceneGame2.h"
#include "CText.h"

CGamePad CSceneGame2::mGamePad;


//配列の要素数を求める
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
//マップ配列の横の長さ
#define MAPSIZE_V 10
//チップサイズ
#define CHIPSIZE 16
//画像のマッピング 左,右,下,上
//ブロック地上
#define UVBLOCKG 48, 95, 191, 144
//プレイヤー
#define UVPLAYER 136, 156, 158, 130
//敵のテクスチャ
#define UVENEMY 136, 156, 190, 161

#define DISP_XS CHIPSIZE * 8 //画面の開始X相対位置
#define DISP_W CHIPSIZE * 4 * 6 //画面の幅
#define DISP_H CHIPSIZE * 3 * 6 //画面の高さ

//初期化処理のオーバーライド
void CSceneGame2::Init() {
	//サウンドファイルのロード
	mSound.Load("bgm.mp3");
	//リピート再生
	mSound.Repeat();
	mScene = EGAME;
	mTexImage.Load("Image.tga");
	CText::mFont.Load("Font.tga");
	int map[] = {
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 2, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 3, 0, 0, 0, 0, 0, //敵の追加
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, //段の追加
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	};
	for (int i = 0; i < ARRAY_SIZE(map); i++) {
		int x = i / MAPSIZE_V; //横方向の値
		int y = i % MAPSIZE_V; //縦方向の値
		CCharacter *c;
		switch (map[i]) {
		case 1:
			c = new CBlock(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVBLOCKG);
			mCharacters.push_back(c);
			break;
		case 3: //敵の生成
			c = new CEnemy2(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVENEMY);
			mCharacters.push_back(c);
			break;
		}
	}
	for (int i = 0; i < ARRAY_SIZE(map); i++) {
		int x = i / MAPSIZE_V; //横方向の値
		int y = i % MAPSIZE_V; //縦方向の値
		CCharacter *c;
		switch (map[i]) {
		case 2:
			c = new CPlayer2(&mTexImage, x*CHIPSIZE * 2, y*CHIPSIZE * 2, CHIPSIZE, CHIPSIZE, UVPLAYER);
			mCharacters.push_back(c);
			break;
		}
	}
}

//更新処理のオーバーライド
void CSceneGame2::Update() {
	mGamePad.Update();

	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Update();
	}
	//衝突処理
	for (int i = 0; i < mCharacters.size() - 1; i++) {
		for (int j = i + 1; j < mCharacters.size(); j++) {
			mCharacters[i]->Collision(mCharacters[i], mCharacters[j]);
			mCharacters[j]->Collision(mCharacters[j], mCharacters[i]);
		}
	}
	//カメラの設定を行う
	SetCamera();
	for (int i = 0; i < mCharacters.size(); i++) {
		mCharacters[i]->Render();
	}
	//ユーザーインタフェースの描画
	UI();
}

//次のシーンの取得
CScene::EScene CSceneGame2::GetNextScene() {
	return mScene;
}
/*
カメラの設定
*/
void CSceneGame2::SetCamera() {
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	//2D画面表示領域を設定
	//画面の左座標，画面の右座標，画面の下座標，画面の上座標
	gluOrtho2D(CPlayer2::spInstance->x - DISP_XS
		, CPlayer2::spInstance->x - DISP_XS + DISP_W
		, 0, DISP_H);	//2Dの画面を設定
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
}
/*
ユーザーインタフェースの実装
*/
void CSceneGame2::UI() {
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	//現在のプロジェクション行列を退避
	glPushMatrix();
	//行列を初期化
	glLoadIdentity();
	//2D画面表示領域を設定
	//画面の左座標，画面の右座標，画面の下座標，画面の上座標
	gluOrtho2D( -400, 400, -300, 300);	//2Dの画面座標を設定
	//文字列表示
	CText::DrawString("SCORE", -320, 240, 20, 20);
	//退避した行列に戻す
	glPopMatrix();
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
}
