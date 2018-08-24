#include "CBossLifeBar.h"

void CBossLifeBar::Update(){
	if (CBoss::mpBoss != NULL){
		CRectangle::Update();
		mPosition = CVector2(CMapScroll::mpScroll->mPosition.x, CMapScroll::mpScroll->mPosition.y);

		if (mScale.x > CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X)
			mScale.x -= BOSSLIFE_SPEED;

		else if (mScale.x < CBoss::mpBoss->mBossLifeProportion * BOSSLIFEBAR_X)
			mScale.x += BOSSLIFE_SPEED;
	}
}

void CBossLifeBar::Render(){
	if (CBoss::mpBoss != NULL)
	mTexLifeBar.DrawImage(BOSSLIFEBAR_UV);

}