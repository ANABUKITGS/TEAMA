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
		mLife = EFECT_LIFE;
		CTaskManager::Get()->Add(this);
	}

	CEfect(CVector2 pos)
		:CEfect()
	{
		CRectangle(pos, CVector2(32, 32), &mTexkira);
		mPosition.x = pos.x + (float)(rand() % 70 - 60);
		mPosition.y = pos.y + (float)(rand() % 70 - 60);

	}
	void Update();
	void Render();
};
#endif