#include <Windows.h>
#include "glew.h"
#include "glut.h"
#define _USE_MATH_DEFINES //数学ライブラリのM_PIを有効にする
#include <math.h> //数学ライブラリのインクルード

#define W_H		1280 //Window幅
#define W_V		720 //Window高さ

#include "CMain.h"

CMain Main;

/* display関数
1秒間に60回実行される
*/
void display() {
	//各バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	//モデルビューの行列を単位行列にする
	glLoadIdentity();

	Main.MainLoop();

	//画面に表示
	glutSwapBuffers();
}

//関数のプロトタイプ宣言
void reshape(int, int);
void idle();

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);	//ディスプレイモード設定
	//ウィンドウの設定
	glutInitWindowSize(W_H, W_V);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("マップエディター | 0.0FPS | 00:00.000");	//ウィンドウ作成
	system("TITLE conhost.exe");
	glClearColor(0.5f, 0.5f, 0.5f, 1.f);	//クリア色をグレーに設定

	glewInit();

//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

//ライトの設定
	//固定シェーダー用
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//メッシュシェーダー用
//	CLight::getLight(0)->setDir(CVector3D(0, -1, 1).GetNormalize());
//	CLight::getLight(0)->setColor(CVector3D(0.9f, 0.9f, 0.9f), CVector3D(1.0f, 1.0f, 1.0f));

	//各種関数設定
	glutDisplayFunc(display);	//描画時の関数を指定
	glutReshapeFunc(reshape);	//ウィンドウ変形時の関数を指定
	glutIdleFunc(idle);			//待機時の関数を指定

	//メインループ
	glutMainLoop();

	return;
}

/*ウィンドウサイズ変更時の処理
void reshape(int width, int height)
width:画面幅
height:画面高さ
*/
void reshape(int width, int height) {
	glViewport(0, 0, width, height);	//画面の描画エリアの指定
//3D Setting
	//CCamera::getCamera()->SetSize(width, height);
	//glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	//glLoadIdentity();
	//gluPerspective(75.0, (double)width / (double)height, 1.0, 1000.0);
	//gluLookAt(0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//2D Setting
	glMatrixMode(GL_PROJECTION);		//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	gluOrtho2D(-W_H / 2, W_H / 2, -W_V / 2, W_V / 2);	//画面の座標系を設定
	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化

}

LARGE_INTEGER last_time;	//前回のカウンタ値
//１秒間に６０回描画するように調節する
void idle() {
	LARGE_INTEGER freq;		//一秒当たりのカウンタ数
	LARGE_INTEGER time;		//今回のカウンタ値

	//一秒間のカウンタ数を取得
	QueryPerformanceFrequency(&freq);

	if (last_time.QuadPart == 0) {
		QueryPerformanceCounter(&last_time);
	}
	do{
		//現在のシステムのカウント数を取得
		QueryPerformanceCounter(&time);

		//今のカウント-前回のカウント < 1秒当たりのカウント数を60で割る(1/60秒当たりのカウント数)
	} while (time.QuadPart - last_time.QuadPart < freq.QuadPart / 60);
	last_time = time;

	//描画する関数を呼ぶ
	display();
}
