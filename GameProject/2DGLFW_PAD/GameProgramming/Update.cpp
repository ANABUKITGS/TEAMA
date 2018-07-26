//GetKeyState関数のヘッダファイル
#include <Windows.h>
#include "CScene.h" //シーンのインクルード
#include "CSceneTitle.h" //シーンタイトルのインクルード
#include "CSceneGame2.h"
#include "glut.h"

/*
シーン管理クラス
*/
class CSceneManager {
public:

	CScene::EScene mScene; //シーンの識別
	CScene *mpScene; //シーンへのポインタ

	//デフォルトコンストラクタ
	CSceneManager()
	: mpScene(0)
	{
	}
	//デストラクタ
	~CSceneManager() {
		//シーンがあれば削除
		if (mpScene)
			//シーンの削除
			delete mpScene;
		mpScene = 0;
	}
	/*
	初期化処理
	*/
	void Init() {
		//シーンの識別を設定する
		mScene = CScene::ETITLE;
		//シーンを生成し、ポインタを設定する
		//変数は親クラス、生成は子クラス
		mpScene = new CSceneTitle();
		//生成したクラスのメソッドが呼ばれる
		mpScene->Init();
	}
	/*
	更新処理
	*/
	void Update() {
		//ポインタのUpdateを呼ぶ
		mpScene->Update();
		//次のシーンを取得し異なるか判定
		if (mScene != mpScene->GetNextScene()) {
			mScene = mpScene->GetNextScene();
			delete mpScene;//今のシーン削除
			//該当するシーンを生成
			switch (mScene) {
			case CScene::EGAME:
				mpScene = new CSceneGame2();
				mpScene->Init();
				break;
			case CScene::ETITLE:
				mpScene = new CSceneTitle();
				mpScene->Init();
				break;
			}
		}
	}
};

//シーンマネージャのインスタンス
CSceneManager SceneManager;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
	//シーンマネージャの初期化
	SceneManager.Init();
}

//Update関数
//プログラムの実行中、繰り返し呼ばれる関数
void Update() {
	//シーンマネージャの更新
	SceneManager.Update();
}
