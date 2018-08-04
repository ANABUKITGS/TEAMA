#include "CCamera2D.h"

void CCamera2D::Begin(double left, double right, double bottom, double top) {
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glPushMatrix();
	glLoadIdentity();				//行列を初期化
	gluOrtho2D(left, right, bottom, top);	//2Dの画面を設定
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glPushMatrix();
	glLoadIdentity();				//行列を初期化
}

void CCamera2D::End() {
	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glPopMatrix();
}
