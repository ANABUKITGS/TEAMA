#ifndef CBOSSLIFEBAR_H
#define CBOSSLIFEBAR_H
#include "CRectangle.h"
#include "CMapScroll.h"
#include "CBoss.h"

#define BOSSLIFEBAR_X		256
#define BOSSLIFEBAR_Y		16
#define BOSSLIFEBAR_UV		mPosition.x - mScale.x, mPosition.x + mScale.x, mPosition.y - mScale.y, mPosition.y + mScale.y, 0, 32, 32, 0,  mRed, mGreen, 0.0f, 1.0f
#define BOSSLIFEBAR_BACK_UV	mPosition.x - BOSSLIFEBAR_X, mPosition.x + BOSSLIFEBAR_X, mPosition.y - BOSSLIFEBAR_Y, mPosition.y + BOSSLIFEBAR_Y, 0, 32, 32, 0,  BLACK, 0.75f
#define BOSSLIFE_SPEED	2

class CBossLifeBar : public CRectangle{
private:
	CTexture mTexLifeBar;
	float mRed;
	float mGreen;
	//float mBlue;

public:
	CBossLifeBar(){
		mRed = 0.0f;
		mGreen = 1.0f;
		//mBlue = 0.0f;
		mRender = false;
		mTag = ENONE;
		mPriority = -16;
		if (mTexLifeBar.id == NULL)
			mTexLifeBar.Load(".\\Data\\Images\\Boss\\LifeBar.tga");
		SetRectangle(CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y + 312), CVector2(0, BOSSLIFEBAR_Y), NULL);
		CTaskManager::Get()->Add(this);

		CBoss::mpBoss->mBossMaxLife = CBoss::mpBoss->mBossLife = BOSS_LIFE - CPlayerT::mpPlayer->mJewel;
	}

	void Update();
	void Render();
};
#endif