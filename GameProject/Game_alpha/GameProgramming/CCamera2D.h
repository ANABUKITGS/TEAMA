#ifndef CCAMERA2D_H
#define CCAMERA2D_H

#include <Windows.h>
#include "glut.h"


class CCamera2D {
public:
	//x:中心座標X y:中心座標Y w:幅（実際の半分）h:高さ（実際の半分）
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
		glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
		glPushMatrix();
		glLoadIdentity();				//行列を初期化
		gluOrtho2D(x - w, x + w, y - h, y + h);	//2Dの画面を設定
		glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	}

	static void Begin(double left, double right, double bottom, double top);
	static void End();

};


#endif
