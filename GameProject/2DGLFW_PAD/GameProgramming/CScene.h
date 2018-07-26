#ifndef CSCENE_H //インクルードガード
#define CSCENE_H //インクルードガード

/*
シーンの基底クラス
*/
class CScene {
public:
	//シーンの識別子
	enum EScene {
		EGAME,	//ゲーム
		ETITLE, //タイトル
	};
	//次のシーン
	EScene mScene;
	//virtual 仮想関数
	//ポリモーフィズムの実装
	//=0 純粋
	virtual void Init() = 0;	//純粋仮想関数 初期化処理
	virtual void Update() = 0; //純粋仮想関数 更新処理
	//次のシーンの取得
	virtual EScene GetNextScene() = 0;
};

#endif //インクルードガード
