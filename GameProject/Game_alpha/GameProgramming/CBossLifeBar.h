#ifndef CBOSSLIFEBAR_H
#define CBOSSLIFEBAR_H
#include "CRectangle.h"
#include "CMapScroll.h"
#include "CBoss.h"

#define BOSSLIFEBAR_X				210.5
#define BOSSLIFEBAR_Y				16
#define BOSSLIFEBAR_BACK_X			256
#define BOSSLIFEBAR_BACK_Y			32
#define BOSSLIFEBAR_UV				mPosition.x - mScale.x, mPosition.x + mScale.x, mPosition.y - mScale.y, mPosition.y + mScale.y, 0, 512, 32, 0,  mRed, mGreen, 0.0f, 1.0f
#define BOSSLIFEBAR_BACK_UV1		mPosition.x - mScale.x - 57, CMapScroll::mpScroll->mPosition.x + BOSSLIFEBAR_BACK_X - 15, mPosition.y - BOSSLIFEBAR_BACK_Y + 6, mPosition.y + BOSSLIFEBAR_BACK_Y + 6, 0, 512, 224, 160, 1.0f
#define BOSSLIFEBAR_BACK_UV2		mPosition.x - mScale.x - 57, CMapScroll::mpScroll->mPosition.x + BOSSLIFEBAR_BACK_X - 15, mPosition.y - BOSSLIFEBAR_BACK_Y + 6, mPosition.y + BOSSLIFEBAR_BACK_Y + 6, 0, 512, 160, 96, 1.0f
#define BOSSLIFEBAR_HIGHLIGHT_UV	mPosition.x - mScale.x, mPosition.x + mScale.x, mPosition.y - mScale.y, mPosition.y + mScale.y, 0, 512, 96, 64, 1.0f
#define BOSSLIFE_SPEED				2
#define BOSSNAME_UV					CMapScroll::mpScroll->mPosition.x - 45, CMapScroll::mpScroll->mPosition.x + 45, mPosition.y + 16, mPosition.y + 48, 0, 180, 64, 0, 1.0f

class CBossLifeBar : public CRectangle{
private:
	CTexture mTexLifeBar;
	CTexture mTexBossName;
	float mRed;
	float mGreen;
	//float mBlue;

public:
	static CBossLifeBar *mpBossLifeBar;
	CBossLifeBar(){
		mRed = 0.0f;
		mGreen = 1.0f;
		//mBlue = 0.0f;
		mRender = false;
		mTag = ENONE;
		mPriority = -16;
		if (mTexLifeBar.id == NULL)
			mTexLifeBar.Load(".\\Data\\Images\\Boss\\LifeBar.tga");
		if (mTexBossName.id == NULL)
			mTexBossName.Load(".\\Data\\Images\\Boss\\Jack.tga");
		SetRectangle(CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y + 312), CVector2(0, BOSSLIFEBAR_Y), NULL);
		CTaskManager::Get()->Add(this);

		CBoss::mpBoss->mBossMaxLife = CBoss::mpBoss->mBossLife = BOSS_LIFE - CPlayerT::mpPlayer->mJewel;
		CPlayerT::mpPlayer->mMaxJewel = CPlayerT::mpPlayer->mJewel;
	}

	~CBossLifeBar(){
		mpBossLifeBar = 0;
	}

	void Update();
	void Render();
	void Remove();
};
#endif