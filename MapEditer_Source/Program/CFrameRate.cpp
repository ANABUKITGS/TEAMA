#include "CFrameRate.h"

SYSTEMTIME CFrameRate::Time;	//プログラム開始時から計測した ミリ秒
int CFrameRate::FrameCount;	//フレーム数 カウント
float CFrameRate::FPS;	//フレームレート
float CFrameRate::FPSRender;	//描画用 フレームレート
int CFrameRate::RenderStartTime;	//フレームレート 描画 更新 時間
int CFrameRate::StartIntTime;	//1フレームの開始時間
int CFrameRate::EndIntTime;	//1フレームの終了時間
CRectangle CFrameRate::TextBack;	//テキスト 背景

void CFrameRate::Update(){
	if (FrameCount <= 0){
		StartIntTime = clock();
	}
	else if (FrameCount >= 15){
		EndIntTime = clock();
		FPS = EndIntTime - StartIntTime;
		FPS = 15000 / FPS;
		FrameCount = -1;
	}
	if (clock() >= RenderStartTime + 1000){
		FPSRender = FPS;
		RenderStartTime = clock();
	}
	FrameCount++;
}

void CFrameRate::Render(){
	Update();
	/*------ ウィンドウの タイトルバーに 表示 ------*/
	char wintitle_buf[256];
	float time = clock();
	time = time / 1000;
	int timemin = time / 60;
	sprintf(wintitle_buf, "マップエディター | %0.1fFPS | %02d:%06.3f", FPSRender, timemin, time - (timemin * 60));
	glutSetWindowTitle(wintitle_buf);	//ウィンドウタイトル 変更
}