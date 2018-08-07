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
	int mJumpTi;
	int mVelocityLimit;
	bool mDirection;
	void Update();
	void Render();
	void Gravity();
	void Forward();
	void Scroll();
	
};
#endif