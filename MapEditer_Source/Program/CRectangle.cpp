#include "CRectangle.h"
#include "glut.h"
#include "CMain.h"

void CRectangle::Render(float r,float g,float b,float a){
	if (mEnabled == false)
		return;
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLES);
	glVertex2d(mRight,mTop);
	glVertex2d(mLeft,mBottom);
	glVertex2d(mRight,mBottom);
	glVertex2d(mRight,mTop);
	glVertex2d(mLeft,mTop);
	glVertex2d(mLeft,mBottom);
	glEnd();

	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);
	}

void CRectangle::SetVertex(float left, float right, float bottom, float top, bool enabled){
	mLeft = left;
	mRight = right;
	mBottom = bottom;
	mTop = top;
	mEnabled = enabled;
}