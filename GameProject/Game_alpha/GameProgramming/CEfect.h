#ifndef CEFECT_H
#define CEFECT_H

#include "CTexture.h"
#include "CRectangle.h"
#include "CTaskManager.h"
#include <stdlib.h>

//#define EFECT_LIFE 30 
#define EFECT_UV mPosition.x - 16 / 2, mPosition.x + 16 / 2, mPosition.y - 16 / 2, mPosition.y + 16 / 2, 0, 32, 32, 0
#define DAMAGEFEECT_LIFE 30
#define DAMAGEEFECT_UV mPosition.x - 16 / 2, mPosition.x + 16 / 2, mPosition.y - 16 / 2, mPosition.y + 16 / 2, 0, 32, 32, 0
#define BOSSEFECT_UV mPosition.x - 128 , mPosition.x + 128 , mPosition.y - 90 , mPosition.y +166 , 0+ani_num*512, 512+ani_num*512, 512, 0
#define BOXEFECT_UV mPosition.x - 64, mPosition.x + 64, mPosition.y - 64, mPosition.y + 64, 0 + ani_num * 256, 256 + ani_num * 256, 256 , 0

class CEfect :public CRectangle{
public:
	CTexture mTexkira;
	//int mLife;

	CEfect(){
		mTexkira.Load(".\\Data\\Images\\Efect\\kirakira.tga");
		mRender = false;
		mVelocityY = 10.0f;
		mAlpha = 1.0f;
		mTag = ENONE;
		//mLife = EFECT_LIFE;
		mPriority = -2;
		CTaskManager::Get()->Add(this);
	}

	CEfect(CVector2 pos)
		:CEfect()
	{
		CRectangle(pos, CVector2(32, 32), &mTexkira);
		SetRectangle(pos, CVector2(32, 32), &mTexkira);
		mPosition.x = pos.x + (float)(rand() % 80 - 40);
		mPosition.y = pos.y + (float)(rand() % 80 - 40);

	}
	void Update();
	void Render();
};

class CDamageEfect :public CRectangle{
public:
	float mRotationAdd;
	int mLife;
	CTexture mTexture;

	CDamageEfect(){
		mTag = ENONE;
		mTexture.Load(".\\Data\\Images\\Map\\MapJewel.tga");
		mLife = DAMAGEFEECT_LIFE;
		mVelocityX = rand() % 8 - 4;
		mVelocityY = rand() % 5 + 16;
		mRotationAdd = (float)(rand() % 8 - 4);
		mPriority = -2;
		CTaskManager::Get()->Add(this);
	}

	CDamageEfect(CVector2 pos)
		:CDamageEfect()
	{
		CRectangle(pos, CVector2(32,32), &mTexture);
		SetRectangle(pos, CVector2(32,32), &mTexture);
		mUv[0] = 0;
		mUv[1] = 64;
		mUv[2] = 64;
		mUv[3] = 0;
	}
	void Update();
	void Gravity();
	void Render();
};
class CBossEfect :public CRectangle{
public:
	int ani_num;
	int ani_count;
	CTexture mTexture;
	CRectangle *mpRect;
	CBossEfect(){
		ani_num = 0;
		ani_count = 5;
		mTag = ENONE;
		mRender = false;
		mTexture.Load(".\\Data\\Images\\Efect\\boss_effect.tga");
		CTaskManager::Get()->Add(this);

	}
	CBossEfect(CRectangle *p)
		:CBossEfect()
	{
		mAlpha = 1.0f;
		SetRectangle(p->mPosition, CVector2(32, 90), NULL);
		mpRect = p;
	}
	void Update();
	void Render();
};
class CBoxEfect :public CRectangle{
public:
	int ani_num;
	int ani_count;
	CTexture mTexture;
	CBoxEfect(){
		ani_num = 0;
		ani_count = 8;
		mTag = ENONE;
		mRender = false;
		mTexture.Load(".\\Data\\Images\\Efect\\hako_effect.tga");
		CTaskManager::Get()->Add(this);

	}
	CBoxEfect(CVector2 pos)
		:CBoxEfect()
	{
		mPosition = pos;
	}
	void Update();
	void Render();
};
#endif