#ifndef CWEAPON_H
#define CWEAPON_H
#include "CRectangle.h"
#include "CTaskManager.h"

#define WEAPOM_VELOCITY 8.0f
#define WEAPON_LIFE 30

class CWeapon : public CRectangle{
public:
	float mVelocity;	//����̓����X�s�[�h
	int mLife;			//����̐�������
	bool mDirection;	//������΂�����
	CWeapon() {
		mPriority = 1;
		mLife = WEAPON_LIFE;
		mVelocity = WEAPOM_VELOCITY;
		CTaskManager::Get()->Add(this);
	}
	CWeapon::CWeapon(ECELLNUM tag ,const CVector2&position, const CVector2&scale,const bool direction, CTexture*texture)
		: CWeapon()
	{
		SetRectangle(position, scale, texture);
		mDirection = direction;
		mTag = tag;
		
	}
	void Update();
	void Render();
	//bool Collision(CRectangle *p);
};
#endif