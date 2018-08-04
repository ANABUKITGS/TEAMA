#ifndef CCAMERA2D_H
#define CCAMERA2D_H

#include <Windows.h>
#include "glut.h"


class CCamera2D {
public:
	//x:���S���WX y:���S���WY w:���i���ۂ̔����jh:�����i���ۂ̔����j
	float x, y, w, h;

	void SetOrtho(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	void Update() {
		float asp = w / h;
		if (GetKeyState('A') & 0x8000) {
			x -= 2;
		}
		if (GetKeyState('D') & 0x8000) {
			x += 2;
		}
		if (GetKeyState('W') & 0x8000) {
			y += 2;
		}
		if (GetKeyState('S') & 0x8000) {
			y -= 2;
		}
		if (GetKeyState('I') & 0x8000) {
			w -= asp * 2;
			h -= 2;
		}
		if (GetKeyState('O') & 0x8000) {
			w += asp * 2;
			h += 2;
		}
	}

	void CCamera2D::Begin() {
		glMatrixMode(GL_PROJECTION);	//�s����v���W�F�N�V�������[�h�֕ύX
		glPushMatrix();
		glLoadIdentity();				//�s���������
		gluOrtho2D(x - w, x + w, y - h, y + h);	//2D�̉�ʂ�ݒ�
		glMatrixMode(GL_MODELVIEW);		//�s������f���r���[���[�h�֕ύX
	}

	static void Begin(double left, double right, double bottom, double top);
	static void End();

};


#endif
