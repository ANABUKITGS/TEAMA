#pragma once

#include "glut.h"

#define W_H		800 //Windowïù
#define W_V		600 //WindowçÇÇ≥

class CMain {
	int		mState;
public:
	CMain() : mState(0) {}

	void MainLoop() {
		switch (mState)
		{
		case 0:
			Init();
			mState = 1;
			break;
		default:
			Update();
			break;
		}
	}
	void Init();
	void Update();

};

