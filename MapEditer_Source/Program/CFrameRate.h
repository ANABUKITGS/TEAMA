#ifndef CCLOCK_H
#define CCLOCK_H
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include "CRectangle.h"
#include "CText.h"

class CFrameRate {
public:
	static SYSTEMTIME Time;	//プログラム開始時から計測した ミリ秒
	static int FrameCount;	//フレーム数 カウント
	static float FPS;	//フレームレート
	static float FPSRender;	//描画用 フレームレート
	static int RenderStartTime;	//フレームレート 描画 更新 時間
	static int StartIntTime;	//1フレームの開始時間
	static int EndIntTime;	//1フレームの終了時間
	static CRectangle TextBack;	//テキスト 背景

	static void Update();
	static void Render();
};

#endif