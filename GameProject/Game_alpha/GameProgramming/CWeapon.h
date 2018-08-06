#ifndef CWEAPON_H
#define CWEAPON_H
#include "CRectangle.h"
#include "CTaskManager.h"

#define WEAPOM_VELOCITY 8.0f

class CWeapon : public CRectangle{
public:
	float mVelocity;
	int mLife;
	bool mDirection;
	//CRectangle *player;
	CWeapon() {
		mPriority = 1;
		mLife = 30;
		mVelocity = WEAPOM_VELOCITY;
		mTag = EWEAPON;
		CTaskManager::Get()->Add(this);
	}
	CWeapon::CWeapon(const CVector2&position, const CVector2&scale,const bool direction, CTexture*texture)
		: CWeapon()
	{
		SetRectangle(position, scale, texture);
		mDirection = direction;
		
	}
	void Update();
	void Render();
	//bool Collision(CRectangle *p);
};
#endif