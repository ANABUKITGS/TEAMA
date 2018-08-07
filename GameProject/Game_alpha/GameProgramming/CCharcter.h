#ifndef CCHARCTER_H
#define CCHARCTER_H

#include "CRectangle.h"
#include "CTexture.h"
#include "CGamePad.h"
#include "CText.h"
#include "CMap.h"

class CCharcter :public CRectangle{
public:
	float mVelocityX;
	float mVelocityY;
	float mSearch;		//íTçıîÕàÕ
	int mJumpTi;
	int mVelocityLimit;
	bool mDirection;
	void Update();
	void Render();
	void Gravity();
	//void Jump();
	void Forward();
	void Scroll();
	
};
#endif