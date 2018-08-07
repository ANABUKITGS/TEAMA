#include "CTime.h"

int CTime::FrameCount = 0;			//�t���[���� �J�E���g
int CTime::RenderStartTime = 0;		//�t���[�����[�g �`�� �X�V ����
int CTime::StartIntTime = 0;		//1�t���[���̊J�n����
int CTime::EndIntTime = 0;			//1�t���[���̏I������
int CTime::ElapsedStartTime = 0;	//�v���J�n����
float CTime::FPS = 0;				//�t���[�����[�g
float CTime::RenderFPS = 0;			//�o�� �t���[�����[�g

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