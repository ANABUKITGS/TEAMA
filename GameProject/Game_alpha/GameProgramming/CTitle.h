#ifndef CTITLE_H
#define CTITLE_H
#include "CText.h"
#include "CGamePad.h"
//hoge
class CTitle{
private:
	wchar_t cursor_buf[32];
	int mEditerMode;	//1 : —LŒø | 2 : –³Œø

public:
	int cursor_num;
	int mTexsize[5];
	struct  STitleNum{
		float mSize[4];
		bool mAnimation;
		int mAnimationTime;
		CVector2 mTextSize;
	};
	STitleNum mTitleNum[5];
	
	CTexture mTexTitle;
	CTexture mTexStart;
	CTexture mTexCredit;
	CTexture mTexRanking;
	CTexture mTexEnd;
	CTexture mTexEdit;

	void Init();
	void Update();
	void Render();
	void Animation();
};
#endif