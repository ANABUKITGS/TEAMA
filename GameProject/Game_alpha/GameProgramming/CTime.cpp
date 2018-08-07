#include "CTime.h"

int CTime::FrameCount;			//�t���[���� �J�E���g
int CTime::RenderStartTime;		//�t���[�����[�g �`�� �X�V ����
int CTime::StartIntTime;		//1�t���[���̊J�n����
int CTime::EndIntTime;			//1�t���[���̏I������
int CTime::ElapsedStartTime;	//�v���J�n����
float CTime::FPS;				//�t���[�����[�g

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