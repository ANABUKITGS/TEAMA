#include "CRectangle.h"
#include "glut.h"
#include "CMain.h"

void CRectangle::Render(float r,float g,float b,float a){
	if (mEnabled == false)
		return;
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
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

	//�A���t�@�u�����h�𖳌�
	glDisable(GL_BLEND);
	//�e�N�X�`���𖳌�
	glDisable(GL_TEXTURE_2D);
	}

void CRectangle::SetVertex(float left, float right, float bottom, float top, bool enabled){
	mLeft = left;
	mRight = right;
	mBottom = bottom;
	mTop = top;
	mEnabled = enabled;
}