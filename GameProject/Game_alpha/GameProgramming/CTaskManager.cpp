#include "CTaskManager.h"
#include "CRectangle.h"
#include "CMap.h"
#include "CMapScroll.h"

CTaskManager *CTaskManager::mpInstance = 0;

CTaskManager*CTaskManager::Get(){
	if (!mpInstance)
		mpInstance = new CTaskManager();
	return mpInstance;
}

void CTaskManager::Add(CTask*task){
	if (mpHead){	//2件目以降
		CTask*c = mpHead;	//カレントを作成して先頭に設定
		if (task->mPriority >= c->mPriority){
			task->mpPrev = 0;	//前タスクは見ない
			task->mpNext = c;	//次タスクはカレント(カレントは現在見ている場所を指す)
			c->mpPrev = task;	//カレントの前はタスク(前も見る為)
			mpHead = task;
			return;
		}

		c = c->mpNext;
		
		while (c){
			if (task->mPriority >= c->mPriority){
//				c->mpNext->mpPrev = task;	//カレントの次の前をタスクにする
				c->mpPrev->mpNext = task;	//カレントの次の前をタスクにする
				task->mpPrev = c->mpPrev;	//タスクの前をカレントの前にする
				task->mpNext = c;	//タスクの次をカレントに
				c->mpPrev = task;	//カレントの前をタスクにする
				return;
			}
			c = c->mpNext;
		}
//		c->mpNext = c;

		mpTail->mpNext = task;
		task->mpPrev = mpTail;
		mpTail = task;
		task->mpNext = 0;

	}
	else{
		mpHead = task;
		task->mpNext = 0;
		task->mpPrev = 0;
		mpTail = task;
	}
}

void CTaskManager::Update(){
	CRectangle*p = (CRectangle*)mpHead;	//子クラスのカレントにキャスト変換した先頭タスクを代入
	while (p){	//カレントp
		if (p->mPosition.x + 1280 > CMapScroll::mpScroll->mPosition.x
			&& p->mPosition.x - 1280 < CMapScroll::mpScroll->mPosition.x)
			p->Update();	//現在カレントの更新処理を行う
		p = (CRectangle*)p->mpNext;	//キャスト変換を行ったタスクの次をカレントに代入
	}
	p = (CRectangle*)mpHead;	//子クラスのカレントにキャスト変換した先頭タスクを代入
	while (p && p->mPriority > 0){	//カレントp
		CRectangle *q = (CRectangle*)mpHead;	//子クラスのカレントにキャスト変換した先頭タスクを代入
		while (q) {
			if (p != q) {
				if (p->mEnabled && q->mEnabled) {
					p->Collision(q);
					q->Collision(p);
				}
			}
			q = (CRectangle*)q->mpNext;	//キャスト変換を行ったタスクの次をカレントに代入
		}
		p = (CRectangle*)p->mpNext;	//キャスト変換を行ったタスクの次をカレントに代入
	}
}

void CTaskManager::Render(){
	CRectangle*p = (CRectangle*)mpHead;	//子クラスのカレントにキャスト変換した先頭タスクを代入
	while (p){	//カレントp
		if (p->mPosition.x + 1280 > CMapScroll::mpScroll->mPosition.x
			&& p->mPosition.x - 1280 < CMapScroll::mpScroll->mPosition.x){
			if (p->mEnabled) {
				if (p->mRender)
					p->Render(WHITE, 1.0f);	//現在カレントの描画処理を行う
				p->Render();
			}
		}
		p = (CRectangle*)p->mpNext;	//キャスト変換を行ったタスクの次をカレントに代入
	}
}

void CTaskManager::Remove(){
	CTask*c = (CTask*)mpHead;
	while (c){
		if (c->mEnabled)
			c = c->mpNext;
		else
			c = Remove(c);
	}
}

CTask* CTaskManager::Remove(CTask*task){
	CTask*p = task->mpNext;
	//先頭だった場合
	if (task == mpHead){
		mpHead = task->mpNext;
		mpHead->mpPrev = 0;
	}
	//最後だった場合
	if (task == mpTail){
		mpTail = task->mpPrev;
		mpTail->mpNext = 0;
	}
	//途中だった場合
	if (task->mpPrev != 0){
		task->mpPrev->mpNext = task->mpNext;
	}
	if (task->mpNext != 0){
		task->mpNext->mpPrev = task->mpPrev;
	}
	delete task;
	task = 0;

	return p;
}

void CTaskManager::Destroy(){
	//カレントcを先頭にする
	CTask *c = mpHead;
	//カレントが0になったら終了
	while (c){
		//カレントを次にする
		c = c->mpNext;
		//先頭を削除
		delete mpHead;
		//先頭にカレントを代入する
		mpHead = c;
	}
	//最後を0にする
	mpTail = 0;
	//自分自身を削除
	if (mpInstance)
		delete mpInstance;
	mpInstance = 0;
}
