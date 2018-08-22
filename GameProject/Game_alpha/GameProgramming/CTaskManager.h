#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H

#include "CTask.h"

class CTaskManager{
	//メンバ変数
	CTask*mpHead;	//タスクリストの先頭タスクへのポインタ
	CTask*mpTail;	//タスクリストの最終タスクへのポインタ
	static CTaskManager*mpInstance;	//タスクマネージャへのポインタ(シングルトン)
public:

	//メンバメソッド
	CTaskManager()	//コンストラクタ
		:mpHead(0), mpTail(0)
	{}
	static CTaskManager*Get();	//タスクマネージャを生成して代入する
	void Add(CTask*task);		//taskをタスクマネージャに追加する taskのmPriorityが大きい値程、先頭に近くする
	void Update();				//タスクリストの先頭から順に、タスクの更新処理を呼び出す
	void Collision();			//タスクリストの先頭から順に、タスクの衝突処理を呼び出す
	void Render();				//タスクリストの先頭から順に、タスクの描画処理を呼び出す
	void Remove();				//タスクリストから、無効ならタスクを削除しdeleteする
	CTask* Remove(CTask*task);	//taskに該当するタスクを、タスクリストから削除し、deleteする
	void Destroy();				//タスクリストのタスクを全てdeleteし、タスクマネージャもdeleteする
};

#endif