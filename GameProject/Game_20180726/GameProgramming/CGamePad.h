#ifndef CGAMEPAD_H
#define CGAMEPAD_H

#include "GLFW/glfw3.h"
#include <stdio.h>

#define PAD_1		0, 0
#define PAD_2		1, 0
#define PAD_3		2, 0
#define PAD_4		3, 0
#define PAD_5		4, 0
#define PAD_6		5, 0
#define PAD_7		6, 0
#define PAD_8		7, 0
#define PAD_9		8, 0
#define PAD_10		9, 0
#define PAD_11		10, 0
#define PAD_12		11, 0
#define PAD_UP		12, 0
#define PAD_RIGHT	13, 0
#define PAD_DOWN	14, 0
#define PAD_LEFT	15, 0
#define PAD_LSTICKX	-1
#define PAD_LSTICKY -2
#define PAD_RSTICKX	-3
#define PAD_RSTICKY -4

class CGamePad {
private:
	static CGamePad mGamePad;
public:
	int mButtonNum;
	int mAxisNum;
	static const unsigned char* mpButtons;
	static const float* mpPositions;

	CGamePad() {
		mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
		mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);
	}

	void Update() {
		mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
		mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);
	}
	static bool Push(int, float);
	static bool Once(int, float);
};
#endif