#ifndef CBOSSLIFEBAR_H
#define CBOSSLIFEBAR_H
#include "CRectangle.h"
#include "CMapScroll.h"
#include "CBoss.h"

#define BOSSLIFEBAR_X	256
#define BOSSLIFEBAR_UV	mPosition.x - mScale.x, mPosition.x + mScale.x, mPosition.y - mScale.y, mPosition.y + mScale.y, 0, 32, 32, 0, 1.0f
#define BOSSLIFE_SPEED	1

class CBossLifeBar : public CRectangle{
private:
	CTexture mTexLifeBar;
	int mBarScale;

public:
	CBossLifeBar(){
		mRender = false;
		mTag = ENONE;
		if (mTexLifeBar.id == NULL)
			mTexLifeBar.Load(".\\Data\\Images\\Boss\\LifeBar.tga");
		SetRectangle(CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y), CVector2(BOSSLIFEBAR_X, 16), NULL);
		CTaskManager::Get()->Add(this);
	}

	void Update();
	void Render();
};
#endif