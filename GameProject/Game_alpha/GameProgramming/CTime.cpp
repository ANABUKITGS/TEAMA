#include "CTime.h"

int CTime::FrameCount;			//フレーム数 カウント
int CTime::RenderStartTime;		//フレームレート 描画 更新 時間
int CTime::StartIntTime;		//1フレームの開始時間
int CTime::EndIntTime;			//1フレームの終了時間
int CTime::ElapsedStartTime;	//計測開始時間
float CTime::FPS;				//フレームレート

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
	if (clock() >= RenderStartTime + 1000){
		RenderStartTime = clock();
	}
	FrameCount++;

	return FPS;
}