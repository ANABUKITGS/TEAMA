#ifndef CEFECT_H
#define CEFECT_H

#include "CTexture.h"
#include "CRectangle.h"
#include "CTaskManager.h"
#include <stdlib.h>

#define EFECT_LIFE 30 
#define EFECT_UV mPosition.x - 16 / 2, mPosition.x + 16 / 2, mPosition.y - 16 / 2, mPosition.y + 16 / 2, 0, 32, 32, 0

class CEfect :public CRectangle{
public:
	CTexture mTexkira;
	int mLife;

	CEfect(){
		mTexkira.Load(".\\Data\\Images\\Efect\\kirakira.tga");
		mRender = false;
		mVelocityY = 5.0f;
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
#endif