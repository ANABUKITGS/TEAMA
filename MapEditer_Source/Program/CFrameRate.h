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
	static SYSTEMTIME Time;	//�v���O�����J�n������v������ �~���b
	static int FrameCount;	//�t���[���� �J�E���g
	static float FPS;	//�t���[�����[�g
	static float FPSRender;	//�`��p �t���[�����[�g
	static int RenderStartTime;	//�t���[�����[�g �`�� �X�V ����
	static int StartIntTime;	//1�t���[���̊J�n����
	static int EndIntTime;	//1�t���[���̏I������
	static CRectangle TextBack;	//�e�L�X�g �w�i

	static void Update();
	static void Render();
};

#endif