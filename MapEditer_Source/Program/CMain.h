#pragma once

#ifndef CMAIN_H
#define CMAIN_H

class CMain {
public:
	CMain(){
		mState = 0;
	}

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
	int mState;
};

#endif