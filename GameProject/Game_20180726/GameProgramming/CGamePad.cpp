#include "CGamePad.h"

#define LSTICKX	0
#define LSTICKY	1
#define RSTICKX	2
#define RSTICKY	3

CGamePad CGamePad::mGamePad;
const unsigned char* CGamePad::mpButtons;
const float* CGamePad::mpPositions;

bool CGamePad::Push(int button, float amount){
	mGamePad.Update();
	if (button > -1)
		return mpButtons[button];

	if (button < 0){
		if (amount > 0.0f){
			if (button == -1 && mpPositions[LSTICKX] >= amount)
				return true;

			if (button == -2 && mpPositions[LSTICKY] >= amount)
				return true;

			if (button == -3 && mpPositions[RSTICKX] >= amount)
				return true;

			if (button == -4 && mpPositions[RSTICKY] >= amount)
				return true;
		}
		if (amount < 0.0f){
			if (button == -1 && mpPositions[LSTICKX] <= amount)
				return true;

			if (button == -2 && mpPositions[LSTICKY] <= amount)
				return true;

			if (button == -3 && mpPositions[RSTICKX] <= amount)
				return true;

			if (button == -4 && mpPositions[RSTICKY] <= amount)
				return true;
		}
	}
	return false;
}

bool CGamePad::Once(int button, float amount){
	//‚Ü‚¾
	return false;
}