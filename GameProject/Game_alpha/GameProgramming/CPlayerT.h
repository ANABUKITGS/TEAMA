#ifndef CPLAYERT_H
#define CPLAYERT_H

#include "CCharcter.h"
#include "CTaskManager.h"

#define PLAYER_VELOCITY_X 5.0f
#define PLAYER_VELOCITY_Y 15.0f
#define JUMP_TIME_LIMIT 15
#define VELOCITYX_LIMIT 5.0f


class CPlayerT : public CCharcter {
public:

	CPlayerT() {
		mPriority = 1;
		CTaskManager::Get()->Add(this);
	}

	CPlayerT::CPlayerT(const CVector2&position, const CVector2&scale, CTexture*texture)
		: CPlayerT()
	{
		SetRectangle(position, scale, texture);
		mVelocityG = 0;
		mJumpTime = 0;
		mVelocityX = 0;
		mVelocityJ = PLAYER_VELOCITY_Y;
	}

	void Update();
	void Gravity();
	void Jump();
	void Forward();

	bool Collision(CRectangle *p);

};

#endif
