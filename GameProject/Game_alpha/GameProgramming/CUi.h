#ifndef CUI_H
#define CUI_H

#include "CText.h"

#define UI_POSITION1 -588.0f,258.0f		//ダイヤモンド大のUIの位置座標
#define UI_POSITION2 -588.0f,218.0f		//ダイヤモンド小のUIの位置座標
//#define UI_SIZE_MAX1
//#define UI_SIZE_MAX2
//#define UI_SIZE_MIN1
//#define UI_SIZE_MIN2
#define ANIMATION_TIME 30

class CUi{
public:
	//float mUi_PosX;		//X座標
	//float mUi_PosY;		//Y座標
	float mSize;		//文字サイズ
	wchar_t buf[64];	//2バイト文字列用配列
	CUi(){
		/*mUi_PosX = 0;
		mUi_PosY = 0;*/
		mSize = 0;
	}
};

class CJewelUi :public CUi{
public:
	static bool mAnimation;
	int mAnimationTime;
	CJewelUi(){
		mSize = 24;
		mAnimationTime = ANIMATION_TIME;
	}
	void Animation();
	void Render();
};

class CMiniJewelUi :public CUi{
public:
	static bool mAnimation;
	int mAnimationTime;
	CMiniJewelUi(){
		mSize = 24;
		mAnimationTime = ANIMATION_TIME;
	}
	void Animation();
	void Render();
};

#endif