#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"

#define MONITOR_TIME 180
#define WALK_TIME 180
#define ENEMY_VELOCITY 1.5f
#define E_SEARCHRANGE 250	//索敵範囲
#define DOWN_TIME 100

class CEnemy :public CCharcter{
public:
	static CEnemy *mpEnemy;
	float mVelocity;	//移動スピード
	bool mForward;		//移動方向 true:右 false:左
	int mMonitorTime;	//立ち止まる時間
	int mWalkTime;		//歩く時間
	int mDownTime;		//ダウンしてから消えるまでの時間
	//アニメーションの切り替えをタグ付けで行う
	enum AnimationTag{
		EWALK,
		EMONITOR,
	};
	AnimationTag mAnimationTag;
	CEnemy() {
		mpEnemy = this;
		mPriority = 1;
		mTag = EPLAYER;
		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position, const CVector2&scale, CTexture*texture)
		: CEnemy()
	{
		SetRectangle(position, scale, texture);
	}

	void Init();
	void Update();
	bool Collision(CRectangle *p);
};
#endif