#include "CFrameRate.h"

SYSTEMTIME CFrameRate::Time;	//�v���O�����J�n������v������ �~���b
int CFrameRate::FrameCount;	//�t���[���� �J�E���g
float CFrameRate::FPS;	//�t���[�����[�g
float CFrameRate::FPSRender;	//�`��p �t���[�����[�g
int CFrameRate::RenderStartTime;	//�t���[�����[�g �`�� �X�V ����
int CFrameRate::StartIntTime;	//1�t���[���̊J�n����
int CFrameRate::EndIntTime;	//1�t���[���̏I������
CRectangle CFrameRate::TextBack;	//�e�L�X�g �w�i

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
	/*------ �E�B���h�E�� �^�C�g���o�[�� �\�� ------*/
	char wintitle_buf[256];
	float time = clock();
	time = time / 1000;
	int timemin = time / 60;
	sprintf(wintitle_buf, "�}�b�v�G�f�B�^�[ | %0.1fFPS | %02d:%06.3f", FPSRender, timemin, time - (timemin * 60));
	glutSetWindowTitle(wintitle_buf);	//�E�B���h�E�^�C�g�� �ύX
}