#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"

#define MONITOR_TIME 180
#define WALK_TIME 180
#define ENEMY_VELOCITY 1.5f
#define E_SEARCHRANGE 250	//���G�͈�
#define DOWN_TIME 100

class CEnemy :public CCharcter{
public:
	static CEnemy *mpEnemy;
	float mVelocity;	//�ړ��X�s�[�h
	bool mForward;		//�ړ����� true:�E false:��
	int mMonitorTime;	//�����~�܂鎞��
	int mWalkTime;		//��������
	int mDownTime;		//�_�E�����Ă��������܂ł̎���
	//�A�j���[�V�����̐؂�ւ����^�O�t���ōs��
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