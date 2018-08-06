#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"

class CEnemy :public CRectangle{
public:
	static CEnemy *mpEnemy;
	float mVelocity;	//�ړ��X�s�[�h
	bool mForward;	//�ړ����� true:�E false:��
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