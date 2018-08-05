#ifndef CTASK_H
#define CTASK_H

//マップ 配列 中身
enum ECELLNUM{
	/*------ マップ 形状 など ------*/
	ENONE = 1,			//空白 | 0は使用禁止
	EGROUND,			//床や壁
	EUNDER,				//下から抜ける足場
	EBELTL,				//ベルトコンベア左
	EBELTR,				//ベルトコンベア右
	EJEWELRY,			//宝石
	EJEWELRY2,			//宝石の欠片
	ECHIKUWA,			//ちくわブロック
	ESWITCH_GROUND1,	//スイッチで 切り替わる足場 1
	ESWITCH_GROUND2,	//スイッチで 切り替わる足場 2
	ESWITCH,			//スイッチで 切り替わる足場の スイッチ

	/*------ キャラクター など ------*/
	ECHECKPOINT,		//チェックポイント
	EPLAYER,			//プレイヤー
	EENEMY1,			//敵1
	EENEMY2,			//敵2
	EENEMY3,			//敵3
	EBOSS,				//ボス

	/*------ 特殊ギミック ------*/
	EBOX,				//木箱
	ESTEEL,				//鉄骨
	ESIZE,				//ECELLNUM サイズ

	EBELT,
};


class CTask{
protected:
	ECELLNUM mTag;
	//メンバ変数
	CTask*mpPrev;	//前ポインタ(自分の前のタスクポインタ)
	CTask*mpNext;	//次ポインタ(自分の後のタスクポインタ)
	bool mEnabled;	//有効フラグ(true:有効、false:無効)
	int mPriority;	//タスクの優先度 大きい値程優先度が高く、リストの先頭に並ぶ

	//メンバメソッド
	CTask()	//コンストラクタ
		:mpPrev(0), mpNext(0), mEnabled(true), mPriority(0)
	{}

	CTask(bool enabled, int priority)	//引数有コンストラクタ
		:mpPrev(0), mpNext(0), mEnabled(enabled), mPriority(priority)
	{}

	virtual ~CTask(){	//仮想関数のデストラクタ
	}
	virtual void Update(){}	//1フレームで実行する処理を定義
	virtual void Render(){}	//1フレームで描画する処理を定義
	virtual bool Collision(CTask*m, CTask*y){ return false; }	//衝突処理を定義する

	friend class CTaskManager;	//タスクマネージャーで使う
public:

	bool GetEnabled() { return mEnabled; }

};

#endif