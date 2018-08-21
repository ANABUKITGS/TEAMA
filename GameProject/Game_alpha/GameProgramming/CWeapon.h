#ifndef CWEAPON_H
#define CWEAPON_H
#include "CRectangle.h"
#include "CTaskManager.h"

#define WEAPOM_VELOCITY	12.0f
#define WEAPON_LIFE		40

#define PSTRING_UV_L		mPosition.x, CPlayerT::mpPlayer->mPosition.x, mPosition.y - 10, mPosition.y + 10, 0, 64, 128, 64
#define PSTRING_UV_R		CPlayerT::mpPlayer->mPosition.x, mPosition.x, mPosition.y - 10, mPosition.y + 10, 0, 64, 128, 64

#define ESTRING_UV_L		mpEWeapon->mPosition.x, mPosition.x, mpEWeapon->mPosition.y - 10, mpEWeapon->mPosition.y + 10, 0, 64, 128, 64
#define ESTRING_UV_R		mPosition.x, mpEWeapon->mPosition.x, mpEWeapon->mPosition.y - 10, mpEWeapon->mPosition.y + 10, 0, 64, 128, 64

class CWeapon : public CRectangle{
public:
	CTexture mTexYoyo;
	float mVelocity;	//����̓����X�s�[�h
	int mLife;			//����̐�������
	bool mDirection;	//������΂�����
	CWeapon() {
		mPriority = 1;
		mLife = WEAPON_LIFE;
		mVelocity = WEAPOM_VELOCITY;
		CTaskManager::Get()->Add(this);
	}
	CWeapon::CWeapon(ECELLNUM tag, const CVector2&position, const bool direction)
		: CWeapon()
	{
		mTexYoyo.Load(".\\Data\\Images\\Player\\Yoyo.tga");
		SetRectangle(position, CVector2(10, 10), &mTexYoyo);
		mDirection = direction;
		mTag = tag;
		//mRender = false;
		mUv[0] = 0; mUv[1] = 64; mUv[2] = 64; mUv[3] = 0;
	}
	void Update();
	void Render();
	//bool Collision(CRectangle *p);
};
#endif