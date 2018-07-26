#ifndef CGAMEPAD_H
#define CGAMEPAD_H

#include "GLFW/glfw3.h"
#include <stdio.h>

#define PAD_UP		12
#define PAD_RIGHT	13
#define PAD_DOWN	14
#define PAD_LEFT	15
#define PAD_1	0
#define PAD_2	1
#define PAD_3	2
#define PAD_4	3

class CGamePad {
public:
	int mButtonNum;
	int mAxisNum;
	const unsigned char* mpButtons;
	const float* mpPositions;

	CGamePad() {
		mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
		mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);
	}

	void Update() {
		mpButtons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &mButtonNum);
		mpPositions = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &mAxisNum);

#ifdef _DEBUG
		for (int i = 0; i < mButtonNum; i++) {
			printf(" %d ", mpButtons[i]);
		}
		printf("\n");
		for (int i = 0; i < mAxisNum; i++) {
			printf(" %f ", mpPositions[i]);
		}
		printf("\n");
#endif

	}

};


#endif
