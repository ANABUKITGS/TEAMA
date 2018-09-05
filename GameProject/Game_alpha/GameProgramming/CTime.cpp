#include "CTime.h"

//int CTime::FrameCount = 0;			//フレーム数 カウント
int CTime::RenderStartTime = 0;		//フレームレート 描画 更新 時間
//int CTime::StartIntTime = 0;		//1フレームの開始時間
//int CTime::EndIntTime = 0;			//1フレームの終了時間
int CTime::ElapsedStartTime = 0;	//計測開始時間
float CTime::FPS = 0;				//フレームレート

float CTime::GetTime(){
	return (clock() - ElapsedStartTime)/1000;
}

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

//float CTime::FrameRate(){
//	static float RenderFPS = 0.0f;
//	if (FrameCount <= 0){
//		StartIntTime = clock();
//	}
//	else if (FrameCount >= 15){
//		EndIntTime = clock();
//		FPS = EndIntTime - StartIntTime;
//		FPS = 15000 / FPS;
//		FrameCount = -1;
//	}
//	if (clock() >= RenderStartTime + 500){
//		RenderStartTime = clock();
//		RenderFPS = FPS;
//		return FPS;
//	}
//	FrameCount++;
//	return RenderFPS;
//}

//int CTime::FrameRate(){
//	static int RenderFPS = 0;
//	if (FrameCount <= 0){
//		StartIntTime = clock();
//		EndIntTime = StartIntTime + 1000;
//	}
//	if (clock() < EndIntTime){
//		FrameCount++;
//	}
//	else {
//		FPS = FrameCount;
//		FrameCount = 0;
//	}
//
//	if (clock() >= RenderStartTime + 100){
//		RenderStartTime = clock();
//		RenderFPS = FPS;
//		return FPS;
//	}
//	return RenderFPS;
//}

float CTime::FrameRate(){
	//参考	https://dixq.net/g/52.html
	static int Count = 0;
	static float RenderFPS = 0.0f;
	int i;
	static int t = 0;
	static float ave = 0, f[60];

	f[Count % 60] = clock() - t;
	t = clock();
	if (Count % 60 == 59){
		ave = 0;
		for (i = 0; i < 60; i++)
			ave += f[i];
		ave /= 60;
	}
	if (ave != 0){
		FPS = 1000 / (double)ave;
	}
	Count++;
	

	if (clock() >= RenderStartTime + 10){
		RenderStartTime = clock();
		RenderFPS = FPS;
		return FPS;
	}
	return RenderFPS;
}