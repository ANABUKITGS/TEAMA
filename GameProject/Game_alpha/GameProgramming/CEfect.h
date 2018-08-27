#ifndef CEFECT_H
#define CEFECT_H

#include "CTexture.h"
#include "CRectangle.h"
#include "CTaskManager.h"
#include <stdlib.h>

#define EFECT_LIFE 30 
#define EFECT_UV mPosition.x - 16 / 2, mPosition.x + 16 / 2, mPosition.y - 16 / 2, mPosition.y + 16 / 2, 0, 32, 32, 0
#define DAMAGEFEECT_LIFE 30
#define DAMAGEEFECT_UV mPosition.x - 16 / 2, mPosition.x + 16 / 2, mPosition.y - 16 / 2, mPosition.y + 16 / 2, 0, 32, 32, 0

class CEfect :public CRectangle{
public:
	CTexture mTexkira;
	int mLife;

	CEfect(){
		mTexkira.Load(".\\Data\\Images\\Efect\\kirakira.tga");
		mRender = false;
		mVelocityY = 10.0f;
		mAlpha = 1.0f;
		mTag = ENONE;
		mLife = EFECT_LIFE;
		mPriority = -2;
		CTaskManager::Get()->Add(this);
	}

	CEfect(CVector2 pos)
		:CEfect()
	{
		CRectangle(pos, CVector2(32, 32), &mTexkira);
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
#endif