#include "CBossLifeBar.h"
#include "CMapSign.h"

CBossLifeBar *CBossLifeBar::mpBossLifeBar = 0;

void CBossLifeBar::Update(){
	CRectangle::Update();
	if (CBoss::mpBoss != NULL){
		if (CMapBossRoomSign::mpBossRoomSign->mColFlg){
			mPosition = CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y + 312);

			//スケール
			if (mScale.x > CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X &&
				mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X >= BOSSLIFE_SPEED)
				mScale.x -= BOSSLIFE_SPEED;

			else if (mScale.x < CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X &&
				mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X <= -BOSSLIFE_SPEED)
				mScale.x += BOSSLIFE_SPEED;

			if (CBoss::mpBoss->mBossLifeProportion <= 0.0f &&
				mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X < BOSSLIFE_SPEED){
				mScale.x = 0.0f;
				mPosition.x = CMapScroll::mpScroll->mPosition.x - (BOSSLIFEBAR_X / 2);
			}
			if (CBoss::mpBoss->mBossLifeProportion >= 1.0f &&
				mScale.x - CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X > -BOSSLIFE_SPEED){
				mScale.x = BOSSLIFEBAR_X;
				mPosition.x = CMapScroll::mpScroll->mPosition.x;
			}

			//ポジション
			mPosition.x = CMapScroll::mpScroll->mPosition.x - BOSSLIFEBAR_X * (1.0f - mScale.x / BOSSLIFEBAR_X);

			//色
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
		mTexLifeBar.DrawImage(BOSSLIFEBAR_BACK_UV1);
		mTexLifeBar.DrawImageSetColor(BOSSLIFEBAR_UV);
		mTexLifeBar.DrawImage(BOSSLIFEBAR_HIGHLIGHT_UV);
		//CText::DrawStringW(L"JACK", CMapScroll::mpScroll->mPosition.x - 64, mPosition.y + 16, 32, 1.0f, 0);
		mTexBossName.DrawImage(BOSSNAME_UV);
		mTexLifeBar.DrawImage(BOSSLIFEBAR_BACK_UV2);
#ifdef _DEBUG
		wchar_t bosslife_buf[8];
		wchar_t bossmaxlife_buf[8];
		if (CBoss::mpBoss->mBossLife < 999 && CBoss::mpBoss->mBossLife > -999)
			swprintf(bosslife_buf, L"%4d", CBoss::mpBoss->mBossLife);
		else if (CBoss::mpBoss->mBossLife >= 999)
			swprintf(bosslife_buf, L"%4d", 999);
		else if (CBoss::mpBoss->mBossLife <= -999)
			swprintf(bosslife_buf, L"-999");

		if (CBoss::mpBoss->mBossMaxLife < 999 && CBoss::mpBoss->mBossMaxLife > -999)
			swprintf(bossmaxlife_buf, L"%-3d", CBoss::mpBoss->mBossMaxLife);
		else if (CBoss::mpBoss->mBossMaxLife >= 999)
			swprintf(bossmaxlife_buf, L"%3d", 999);
		else if (CBoss::mpBoss->mBossMaxLife <= -999)
			swprintf(bossmaxlife_buf, L"%3d", -999);

		CText::DrawStringW(bosslife_buf, CMapScroll::mpScroll->mPosition.x - 144, mPosition.y - 16, 32, 1.0f, 0);
		CText::DrawStringW(bossmaxlife_buf, CMapScroll::mpScroll->mPosition.x + 16, mPosition.y - 16, 32, 1.0f, 0);
		CText::DrawString("/", CMapScroll::mpScroll->mPosition.x - 16, mPosition.y - 16, 32, 1.0f, 0);
#endif
	}
}