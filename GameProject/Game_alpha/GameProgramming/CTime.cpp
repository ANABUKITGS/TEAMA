#include "CTime.h"

int CTime::FrameCount = 0;			//フレーム数 カウント
int CTime::RenderStartTime = 0;		//フレームレート 描画 更新 時間
int CTime::StartIntTime = 0;		//1フレームの開始時間
int CTime::EndIntTime = 0;			//1フレームの終了時間
int CTime::ElapsedStartTime = 0;	//計測開始時間
float CTime::FPS = 0;				//フレームレート
float CTime::RenderFPS = 0;			//出力 フレームレート

void CTime::GetStartTime(){
	ElapsedStartTime = clock();
}

int CTime::ElapsedTimeMin(){
	float timems = clock() - ElapsedStartTime;
	timems = timems / 1000;
	int timemin = timems / 60;

	return timemin;
}

float CTime::ElapsedTimeSec(){
	float timems = clock() - ElapsedStartTime;
	timems = timems / 1000;
	int timemin = timems / 60;

	return timems - (timemin * 60);
}

float CTime::FrameRate(){
	if (FrameCount <= 0){
		StartIntTime = clock();
	}
	else if (FrameCount >= 15){
		EndIntTime = clock();
		FPS = EndIntTime - StartIntTime;
		FPS = 15000 / FPS;
		FrameCount = -1;
	}
	if (clock() >= RenderStartTime + 500){
		RenderStartTime = clock();
		RenderFPS = FPS;
		return FPS;
	}
	FrameCount++;
	return RenderFPS;
}