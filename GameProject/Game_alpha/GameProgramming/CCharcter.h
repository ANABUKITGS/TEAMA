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
	float mVelocityJ;
	float mVelocityG;
	int mJumpTime;
	int mVelocityLimit;
	bool mDirection;
	void Init();
	void Update();
	void Render();
	void Gravity();
	void Jump();
	void Forward();
	void Scroll();
};
#endif