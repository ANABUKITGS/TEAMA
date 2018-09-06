#include "CUi.h"
#include "CEfect.h"
#include "CVector2.h"
#include "CPlayerT.h"

bool CJewelUi::mAnimation = false;
bool CMiniJewelUi::mAnimation = false;

void CJewelUi::Animation(){
	if (mAnimation){
		mAnimationTime--;
		
		if (mAnimationTime > 15)
			/*mUi_PosY+=0.5;*/
			mSize ++;
		else if (mAnimationTime > 1)
			/*mUi_PosY -= 0.5;*/
			mSize --;
		else{
			mAnimation = false;
			mAnimationTime = ANIMATION_TIME;
		}
	}
}

void CJewelUi::Render(){
	//ダイヤモンド
	swprintf(buf, L"宝");
	CText::DrawStringImpact(buf, -620, 250, 40, 1.0f, 0);
	swprintf(buf, L" × ");
	CText::DrawStringImpact(buf, -588.0f, 258.0f, 24, 1.0f, 0);
	swprintf(buf, L"%02d", CPlayerT::mpPlayer->mJewel);
	CText::DrawStringImpact(buf, -516.0f, 258.0f, mSize, 1.0f, 0);
}

void CMiniJewelUi::Animation(){
	if (mAnimation){
		mAnimationTime--;
		if (mAnimationTime > 15)
			/*mUi_PosY += 0.5;*/
			mSize ++;
		else if (mAnimationTime > 1)
			/*mUi_PosY -= 0.5;*/
			mSize --;
		else{
			mAnimation = false;
			mAnimationTime = ANIMATION_TIME;
		}
	}
}

void CMiniJewelUi::Render(){
	//ミニダイヤモンド
	swprintf(buf, L"片");
	CText::DrawStringImpact(buf, -612, 218, 24, 1.0f, 0);
	swprintf(buf, L" × ");
	CText::DrawStringImpact(buf, -588.0f, 218.0f, 24, 1.0f, 0);
	swprintf(buf, L"%02d", CPlayerT::mpPlayer->mMiniJewel);
	CText::DrawStringImpact(buf, -516.0f, 218.0f, mSize, 1.0f, 0);
}