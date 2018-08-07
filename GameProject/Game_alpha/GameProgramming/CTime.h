#ifndef CTIME_H
#define CTIME_H
#include <time.h>

class CTime {
private:
	static int FrameCount;			//フレーム数 カウント
	static int RenderStartTime;		//フレームレート 描画 更新 時間
	static int StartIntTime;		//1フレームの開始時間
	static int EndIntTime;			//1フレームの終了時間
	static int ElapsedStartTime;	//計測開始時間
	static float FPS;				//フレームレート

public:
	static void GetStartTime();
	static int ElapsedTimeMin();
	static float ElapsedTimeSec();
	static float FrameRate();
};

#endif