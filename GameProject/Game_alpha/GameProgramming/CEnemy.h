#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CCharcter.h"
#include "CPlayerT.h"

#define MONITOR_TIME 180
#define WALK_TIME 180
#define ENEMY_VELOCITY 1.5f
#define E_SEARCHRANGE 250	//���G�͈�

class CEnemy :public CCharcter{
public:
	CWeapon*mpEWeapon;	//�G���o�����[���[�̃C���X�^���X
	//static CEnemy *mpEnemy;
	float mVelocity;	//�ړ��X�s�[�h
	bool mForward;	//�ړ����� true:�E false:��
	int mMonitorTime;
	int mWalkTime;
	//�A�j���[�V�����̐؂�ւ����^�O�t���ōs��
	enum AnimationTag{
		EWALK,
		EMONITOR,
	};
	AnimationTag mAnimationTag;
	CEnemy(){
		mVelocityY = 0;	//�d�͂̏����l��0�ɂ���
		CPlayerT::mpPlayer->mSearch = 40;
		mSearch =  E_SEARCHRANGE;
		mpEWeapon=0;	//�G�̃��[���[�̒l��0�ɂ��Ă���
		//mpEnemy = this;
		mTag = EENEMY1;
		mPriority = mTag;
		mForward = true;
		mAnimationTag = EWALK;
		mVelocity = ENEMY_VELOCITY;
		mMonitorTime = MONITOR_TIME;
		mWalkTime = WALK_TIME;

		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position, const CVector2&scale, CTexture*texture)
		: CEnemy()
	{
		SetRectangle(position, scale, texture);
	}

	void Update();
	void Render();
	bool Collision(CRectangle *p);
	//�G�̍U���F���͈� �w�肵���͈͓��ɓ���ƍU�����J�n����
	bool SearchCollision(CCharcter*, CCharcter*);
};
#endif