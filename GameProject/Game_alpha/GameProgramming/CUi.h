#ifndef CUI_H
#define CUI_H

#include "CText.h"

#define UI_POSITION1 -588.0f,258.0f		//�_�C�������h���UI�̈ʒu���W
#define UI_POSITION2 -588.0f,218.0f		//�_�C�������h����UI�̈ʒu���W
//#define UI_SIZE_MAX1
//#define UI_SIZE_MAX2
//#define UI_SIZE_MIN1
//#define UI_SIZE_MIN2
#define ANIMATION_TIME 30

class CUi{
public:
	//float mUi_PosX;		//X���W
	//float mUi_PosY;		//Y���W
	float mSize;		//�����T�C�Y
	wchar_t buf[64];	//2�o�C�g������p�z��
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