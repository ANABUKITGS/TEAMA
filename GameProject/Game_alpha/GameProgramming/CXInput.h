#ifndef CXINPUT_H
#define CXINPUT_H
#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>

#define BUTTONS		state.Gamepad.wButtons &			//�f�W�^�� �{�^�� | �߂�l : 0�`1
#define LTRIGGER	CXIn::state.Gamepad.bLeftTrigger	//�E �g���K�[ | �߂�l : 0�`255
#define RTRIGGER	CXIn::state.Gamepad.bRightTrigger	//�E �g���K�[ | �߂�l : 0�`255
#define LSTICKX		CXIn::state.Gamepad.sThumbLX		//�� �X�e�B�b�N �� | �߂�l : -32768�`32767
#define LSTICKY		CXIn::state.Gamepad.sThumbLY		//�� �X�e�B�b�N �c | �߂�l : -32768�`32767
#define RSTICKX		CXIn::state.Gamepad.sThumbRX		//�E �X�e�B�b�N �� | �߂�l : -32768�`32767
#define RSTICKY		CXIn::state.Gamepad.sThumbRY		//�E �X�e�B�b�N �c | �߂�l : -32768�`32767

class CXIn{
	//�f�W�^�� �{�^����������Ă��邩�̃t���O
	static bool flgbutton[XINPUT_GAMEPAD_Y + 1];

	//L�X�e�B�b�N��X�����ɓ��͂�����Ă��邩�̃t���O
	static bool flgLstickX[65536];

	//L�X�e�B�b�N��Y�����ɓ��͂�����Ă��邩�̃t���O
	static bool flgLstickY[65536];

	//R�X�e�B�b�N��X�����ɓ��͂�����Ă��邩�̃t���O
	static bool flgRstickX[65536];

	//R�X�e�B�b�N��Y�����ɓ��͂�����Ă��邩�̃t���O
	static bool flgRstickY[65536];

	static bool OnceLStickX(int);

	static bool OnceLStickY(int);

	static bool OnceRStickX(int);

	static bool OnceRStickY(int);

	//L�g���K�[�̓��͂�����Ă��邩�̃t���O
	static bool flgLtrigger[256];

	//R�g���K�[�̓��͂�����Ă��邩�̃t���O
	static bool flgRtrigger[256];

	static bool OnceLTrigger(int);

	static bool OnceRTrigger(int);
public:
	//XInput�p
	static XINPUT_STATE state;

	//�f�W�^�� �{�^����������Ă����true��Ԃ�
	static bool PushButton(int);

	//�f�W�^�� �{�^���������ꂽ���Ɉ�x����true��Ԃ�
	static bool OnceButton(int);

	//�X�e�B�b�N�����͗ʂ����������͂���Ă����true��Ԃ�
	static bool PushStick(SHORT, float);

	//�X�e�B�b�N�����͗ʂ����������͂��ꂽ���Ɉ�x����true��Ԃ�
	static bool OnceStick(SHORT, float);

	//�g���K�[�����͗ʂ����������͂���Ă����true��Ԃ�
	static bool PushTrigger(BYTE, float);

	//�g���K�[�����͗ʂ����������͂���Ă����true��Ԃ�
	static bool OnceTrigger(BYTE, float);
};
#endif