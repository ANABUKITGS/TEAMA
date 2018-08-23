#ifndef CTIME_H
#define CTIME_H
#include <time.h>

class CTime {
private:
	static int FrameCount;			//�t���[���� �J�E���g
	static int RenderStartTime;		//�t���[�����[�g �`�� �X�V ����
	static int StartIntTime;		//1�t���[���̊J�n����
	static int EndIntTime;			//1�t���[���̏I������
	static int ElapsedStartTime;	//�v���J�n����
	static float FPS;				//�t���[�����[�g
	static float RenderFPS;			//�o�� �t���[�����[�g

public:
	static void GetStartTime();
	static int ElapsedTimeMin();
	static float ElapsedTimeSec();
	static float FrameRate();
	static float GetTime();
};

#endif