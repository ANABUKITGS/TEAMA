#pragma once

#include "CScene.h"
#include "glut.h"

#define W_H		1280 //Windowïù
#define W_V		720 //WindowçÇÇ≥

class CMain {
	int		mState;
public:
	CMain() : mState(0) {}
	static CScene::ESceneTag mSceneTag;
	static int mDisplayMode;
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

