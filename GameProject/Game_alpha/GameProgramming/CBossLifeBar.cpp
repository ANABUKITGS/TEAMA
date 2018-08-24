#include "CBossLifeBar.h"

void CBossLifeBar::Update(){
	if (CBoss::mpBoss != NULL){
		CRectangle::Update();
		mPosition = CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y + 312);

		if (mScale.x > CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X &&
			mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X >= BOSSLIFE_SPEED)
			mScale.x -= BOSSLIFE_SPEED;

		else if (mScale.x < CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X &&
			mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X <= -BOSSLIFE_SPEED)
			mScale.x += BOSSLIFE_SPEED;

		if (CBoss::mpBoss->mBossLifeProportion <= 0.0f &&
			mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X < BOSSLIFE_SPEED)
			mScale.x = 0.0f;

		if (CBoss::mpBoss->mBossLifeProportion >= 1.0f &&
			mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X > -BOSSLIFE_SPEED)
			mScale.x = BOSSLIFEBAR_X;

		//F
		if (CBoss::mpBoss->mBossLifeProportion > 0.5f){
			mRed = (1.0f - CBoss::mpBoss->mBossLifeProportion) * 2;
			mGreen = 1.0f;
		}
		else{
			mGreen = CBoss::mpBoss->mBossLifeProportion * 2;
			mRed = 1.0f;
		}
	}
}

void CBossLifeBar::Render(){
	if (CBoss::mpBoss != NULL){
		mTexLifeBar.DrawImageSetColor(BOSSLIFEBAR_BACK_UV);
		mTexLifeBar.DrawImageSetColor(BOSSLIFEBAR_UV);
		CText::DrawStringW(L"JACK", 0, 0, 64, 1.0f, 0);
	}
}