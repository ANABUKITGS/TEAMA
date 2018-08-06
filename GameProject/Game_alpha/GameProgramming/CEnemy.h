#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"

class CEnemy :public CRectangle{
public:
	static CEnemy *mpEnemy;
	float mVelocity;	//移動スピード
	bool mForward;	//移動方向 true:右 false:左
	int mMonitorTime;
	int mWalkTime;
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