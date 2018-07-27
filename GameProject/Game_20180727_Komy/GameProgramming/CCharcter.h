#ifndef CCHARCTER_H
#define CCHARCTER_H

#include "CRectangle.h"
#include "CTexture.h"

class CCharcter :public CRectangle{
public:
	float mVelocityX;
	float mVelocityJ;
	float mVelocityG;
	int mJumpTime;
	int mVelocityLimit;
	void Init();
	void Update();
	void Gravity();
	void Jump();
	void Forward();
};
#endif