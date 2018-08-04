#include "CCamera2D.h"

void CCamera2D::Begin(double left, double right, double bottom, double top) {
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glPushMatrix();
	glLoadIdentity();				//�s���������
	gluOrtho2D(left, right, bottom, top);	//2D�̉�ʂ�ݒ�
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glPushMatrix();
	glLoadIdentity();				//�s���������
}

void CCamera2D::End() {
	glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	glPopMatrix();
}
