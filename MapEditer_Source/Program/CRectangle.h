#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CTexture.h"

class CRectangle{
public:
	float mRight, mLeft, mTop, mBottom;
	bool mEnabled;
	void SetVertex(float left, float right, float bottom, float top, bool enabled);
	void Render(float r,float g,float b, float a);
};

#endif