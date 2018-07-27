#ifndef CTASK_H
#define CTASK_H

class CTask{
protected:
	//メンバ変数
	CTask*mpPrev;	//前ポインタ(自分の前のタスクポインタ)
	CTask*mpNext;	//次ポインタ(自分の後のタスクポインタ)
	bool mEnabled;	//有効フラグ(true:有効、false:無効)
	int mPriority;	//タスクの優先度 大きい値程優先度が高く、リストの先頭に並ぶ

	//メンバメソッド
	CTask()	//コンストラクタ
		:mpPrev(0), mpNext(0), mEnabled(true)
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

};

#endif