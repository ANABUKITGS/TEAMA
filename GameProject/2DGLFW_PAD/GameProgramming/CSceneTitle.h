#include "CScene.h" //シーンクラスのインクルード
#include "CText.h" //テキストクラスのインクルード
#include "CKey.h" //キークラスのインクルード
#include <Windows.h>
/*
タイトルシーン
*/
//CSceneクラスを継承する
class CSceneTitle : public CScene {
public:
	//次のシーンの取得
	EScene GetNextScene() {
		return mScene;
	}
	//初期化処理のオーバーライド
	void Init() {
		//フォントの設定
		//テクスチャファイルを読み込む
		CText::mFont.Load("font.tga");
		mScene = ETITLE;
	}
	//更新処理のオーバーライド
	void Update() {
		//文字列の描画
		CText::DrawString("TITLE", -200, 0, 50, 50);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME;
		}
	}
};
