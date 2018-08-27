#include "CBossLifeBar.h"
#include "CMapSign.h"

CBossLifeBar *CBossLifeBar::mpBossLifeBar = 0;

void CBossLifeBar::Update(){
	CRectangle::Update();
	if (CBoss::mpBoss != NULL){
		if (CMapBossRoomSign::mpBossRoomSign->mColFlg){
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
		else{
			mScale.x = 0.0f;
			CBoss::mpBoss->mBossMaxLife = CBoss::mpBoss->mBossLife;
		}
	}
}

void CBossLifeBar::Render(){
	if (CBoss::mpBoss != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg){
		mTexLifeBar.DrawImage(BOSSLIFEBAR_BACK_UV);
		mTexLifeBar.DrawImageSetColor(BOSSLIFEBAR_UV);
		mTexLifeBar.DrawImage(BOSSLIFEBAR_HIGHLIGHT_UV);
		CText::DrawStringW(L"JACK", 0, 0, 64, 1.0f, 0);
	}
}