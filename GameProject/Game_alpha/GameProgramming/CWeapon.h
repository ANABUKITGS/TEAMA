#ifndef CWEAPON_H
#define CWEAPON_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMapJewelry.h"

#define WEAPOM_VELOCITY	12.0f
#define WEAPON_LIFE		20

#define PSTRING_UV_L		mPosition.x, CPlayerT::mpPlayer->mPosition.x - 51, mPosition.y - 10, mPosition.y + 10, 0, 64, 128, 64
#define PSTRING_UV_R		CPlayerT::mpPlayer->mPosition.x + 51, mPosition.x, mPosition.y - 10, mPosition.y + 10, 0, 64, 128, 64

#define ESTRING_UV_L		mpEWeapon->mPosition.x, mpEWeapon->mPosInit.x, mpEWeapon->mPosition.y - 10, mpEWeapon->mPosition.y + 10, 0, 64, 128, 64
#define ESTRING_UV_R		mpEWeapon->mPosInit.x, mpEWeapon->mPosition.x, mpEWeapon->mPosition.y - 10, mpEWeapon->mPosition.y + 10, 0, 64, 128, 64

#define BSTRING_UV_L		mpBWeapon->mPosition.x, mpBWeapon->mPosInit.x, mpBWeapon->mPosition.y - 10, mpBWeapon->mPosition.y + 10, 0, 64, 128, 64
#define BSTRING_UV_R		mpBWeapon->mPosInit.x, mpBWeapon->mPosition.x, mpBWeapon->mPosition.y - 10, mpBWeapon->mPosition.y + 10, 0, 64, 128, 64

class CWeapon : public CRectangle{
public:
	CTexture mTexYoyo;
	float mVelocity;	//武器の動くスピード
	int mLife;			//武器の生存時間
	bool mReturn;
	bool mDirection;	//武器を飛ばす方向
	CVector2 mPosInit;	//投げたときの初期位置
	bool mJewel_flg;	//ジュエル　true:持ってる false:持ってない
	bool mMiniJewel_flg;//ミニジュエル　true:持ってない false:持ってない
	CCharcter *mpCharcter;
	CWeapon() {
		mPriority = 1;
		mJewel_flg = false;
		mMiniJewel_flg = false;
		mLife = WEAPON_LIFE;
		mReturn = false;
		mVelocity = WEAPOM_VELOCITY;
		CTaskManager::Get()->Add(this);
	}
	CWeapon::CWeapon(CCharcter*p,ECELLNUM tag, const CVector2&position, const bool direction)
		: CWeapon()
	{
		mpCharcter = p;
		switch (tag){
		case EPWEAPON:
			mTexYoyo.Load(".\\Data\\Images\\Player\\Yoyo.tga");
			SetRectangle(position, CVector2(10, 10), &mTexYoyo);
			break;
		case EEWEAPON:
			mTexYoyo.Load(".\\Data\\Images\\Enemy\\Yoyo.tga");
			SetRectangle(position, CVector2(10, 10), &mTexYoyo);
			break;
		case EBWEAPON:
			mTexYoyo.Load(".\\Data\\Images\\Enemy\\Yoyo.tga");
			SetRectangle(position, CVector2(20, 20), &mTexYoyo);
			break;
		default:
			break;
		}	
		mPosInit = position;
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