#ifndef CTITLE_H
#define CTITLE_H
#include "CText.h"
#include "CGamePad.h"
//hoge
class CTitle{
private:
	wchar_t cursor_buf[32];

public:
	int cursor_num;
	struct  STitleNum{
		float mPositionX;
		float mPositionY;
		bool mAnimation;
		int mAnimationTime;
		float mColor[3];
	};
	STitleNum mTitleNum[4];
	
	CTexture mTexTitle;
	void Init();
	void Update();
	void Render();
	void Animation();
};
#endif