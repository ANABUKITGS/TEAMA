#ifndef CWEAPON_H
#define CWEAPON_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMapJewelry.h"

#define WEAPOM_VELOCITY 12.0f
#define WEAPON_LIFE 40

#define YOYO_UV 

class CWeapon : public CRectangle{
public:
	CTexture mTexYoyo;
	float mVelocity;	//武器の動くスピード
	int mLife;			//武器の生存時間
	bool mDirection;	//武器を飛ばす方向
	bool mJewel_flg;	//ジュエル　true:持ってる false:持ってない
	bool mMiniJewel_flg;//ミニジュエル　true:持ってない false:持ってない
	CWeapon() {
		mPriority = 1;
		mJewel_flg = false;
		mMiniJewel_flg = false;
		mLife = WEAPON_LIFE;
		mVelocity = WEAPOM_VELOCITY;
		CTaskManager::Get()->Add(this);
	}
	CWeapon::CWeapon(ECELLNUM tag, const CVector2&position, const bool direction)
		: CWeapon()
	{
		mTexYoyo.Load(".\\Data\\Images\\Player\\YoyoBody.tga");
		SetRectangle(position, CVector2(10, 10), &mTexYoyo);
		mDirection = direction;
		mTag = tag;
		//mRender = false;
		mUv[0] = 0; mUv[1] = 64; mUv[2] = 64; mUv[3] = 0;
	}
	void Update();
	void Render();
	bool Collision(CRectangle *p);
};
#endif