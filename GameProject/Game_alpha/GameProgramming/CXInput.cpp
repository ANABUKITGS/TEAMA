#include "CXInput.h"

#pragma comment (lib, "xinput.lib")

/*�{�^���ɂ���
#define XINPUT_GAMEPAD_DPAD_UP			�p�b�h��
#define XINPUT_GAMEPAD_DPAD_DOWN		�p�b�h��
#define XINPUT_GAMEPAD_DPAD_LEFT		�p�b�h��
#define XINPUT_GAMEPAD_DPAD_RIGHT		�p�b�h�E
#define XINPUT_GAMEPAD_START			�X�^�[�g
#define XINPUT_GAMEPAD_BACK				�o�b�N
#define XINPUT_GAMEPAD_LEFT_THUMB		���X�e�B�b�N ��������
#define XINPUT_GAMEPAD_RIGHT_THUMB		�E�X�e�B�b�N ��������
#define XINPUT_GAMEPAD_LEFT_SHOULDER	���{�^��
#define XINPUT_GAMEPAD_RIGHT_SHOULDER	�E�{�^��
#define XINPUT_GAMEPAD_A				A�{�^��
#define XINPUT_GAMEPAD_B				B�{�^��
#define XINPUT_GAMEPAD_X				X�{�^��
#define XINPUT_GAMEPAD_Y				Y�{�^��
*/


XINPUT_STATE CXIn::state;

//�f�W�^�� �{�^����������Ă��邩�̃t���O
//true�̂Ƃ���̃f�W�^�� �{�^���͉�����Ă���
bool CXIn::flgbutton[XINPUT_GAMEPAD_Y + 1];

//�X�e�B�b�N�̓��͂�����Ă��邩�̃t���O
//true�̂Ƃ���̃X�e�B�b�N�͓��͂���Ă���
bool CXIn::flgLstickX[65536];
bool CXIn::flgLstickY[65536];
bool CXIn::flgRstickX[65536];
bool CXIn::flgRstickY[65536];

//�g���K�[�̓��͂�����Ă��邩�̃t���O
bool CXIn::flgLtrigger[256];
bool CXIn::flgRtrigger[256];

/*
PushButton
�f�W�^�� �{�^����������Ă����true
������Ă��Ȃ����false
-�g����-
A�{�^����������Ă��邩�H
if(CKey::PushButton(XINPUT_GAMEPAD_A))
*/
bool CXIn::PushButton(int button) {
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState
	return BUTTONS button;
}
/*
OnceButton
�f�W�^�� �{�^���������ꂽ�ŏ���true
�������܂܂��ƁA���̌��false
�g����
A�{�^����������Ă��邩�H
if(CKey::OnceButton(XINPUT_GAMEPAD_A))
*/
bool CXIn::OnceButton(int button) {
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState
	//�f�W�^�� �{�^����������Ă��邩�H
	if (BUTTONS button) {
		//���łɉ�����Ă��邩�H
		if (flgbutton[button]) {
			//������Ă�����false
			return false;
		}
		else {
			//������Ă��Ȃ����
			//flgbutton��true��ݒ�
			flgbutton[button] = true;
			return true;
		}
	}
	else {
		//���̃f�W�^�� �{�^����������ĂȂ����
		//flgbutton��false�ɐݒ�
		flgbutton[button] = false;
	}
	return false;
}

//�X�e�B�b�N�����͗ʂ����������͂���Ă����true��Ԃ�
bool CXIn::PushStick(SHORT stick, float amount){
	int intamount = 128;
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	if (amount >= -1.0f && amount != 0.0f && amount <= 1.0f){
		if (intamount = 128 + (amount * 32766)){
			if (intamount < 128){
				if (stick <= intamount)
					return true;
			}
			if (intamount > 128){
				if (stick >= intamount)
					return true;
			}
		}
	}
	return false;
}

bool CXIn::OnceLStickX(int amount){
	int temp_amount = amount + 32766;
	int hoge = LSTICKX;
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	if (amount < 128){
		//�X�e�B�b�N�����͂���Ă��邩�H
		if (LSTICKX <= amount){
			//���łɓ��͂���Ă��邩�H
			if (flgLstickX[temp_amount]) {
				//���͂���Ă�����false
				return false;
			}
			else {
				//���͂���Ă��Ȃ����
				//flgLstickX��true��ݒ�
				flgLstickX[temp_amount] = true;
				return true;
			}
		}
		else {
			//���̃X�e�B�b�N�����͂���ĂȂ����
			//flgLstickX��false�ɐݒ�
			flgLstickX[temp_amount] = false;
		}
	}
	if (amount > 128){
		//�X�e�B�b�N�����͂���Ă��邩�H
		if (LSTICKX >= amount){
			//���łɓ��͂���Ă��邩�H
			if (flgLstickX[temp_amount]) {
				//���͂���Ă�����false
				return false;
			}
			else {
				//���͂���Ă��Ȃ����
				//flgLstickX��true��ݒ�
				flgLstickX[temp_amount] = true;
				return true;
			}
		}
		else {
			//���̃X�e�B�b�N�����͂���ĂȂ����
			//flgLstickX��false�ɐݒ�
			flgLstickX[temp_amount] = false;
		}
	}
}

bool CXIn::OnceLStickY(int amount){
	//int temp_amount = amount;
	//XInputGetState(
	//	0,			// DWORD	dwUserIndex
	//	&state);	// XINPUT_STATE* pState

	//if (amount < 128){
	//	//�X�e�B�b�N�����͂���Ă��邩�H
	//	if (LSTICKY <= amount){
	//		//���łɓ��͂���Ă��邩�H
	//		if (flgLstickY[temp_amount]) {
	//			//���͂���Ă�����false
	//			return false;
	//		}
	//		else {
	//			//���͂���Ă��Ȃ����
	//			//flgLstickY��true��ݒ�
	//			flgLstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//���̃X�e�B�b�N�����͂���ĂȂ����
	//		//flgLstickY��false�ɐݒ�
	//		flgLstickY[temp_amount] = false;
	//	}
	//}
	//if (amount > 128){
	//	//�X�e�B�b�N�����͂���Ă��邩�H
	//	if (LSTICKY >= amount){
	//		//���łɓ��͂���Ă��邩�H
	//		if (flgLstickY[temp_amount]) {
	//			//���͂���Ă�����false
	//			return false;
	//		}
	//		else {
	//			//���͂���Ă��Ȃ����
	//			//flgLstickY��true��ݒ�
	//			flgLstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//���̃X�e�B�b�N�����͂���ĂȂ����
	//		//flgLstickY��false�ɐݒ�
	//		flgLstickY[temp_amount] = false;
	//	}
	//}
	return false;
}

bool CXIn::OnceRStickX(int amount){
	//int temp_amount = amount;
	//XInputGetState(
	//	0,			// DWORD	dwUserIndex
	//	&state);	// XINPUT_STATE* pState

	//if (amount < 128){
	//	//�X�e�B�b�N�����͂���Ă��邩�H
	//	if (LSTICKX <= amount){
	//		//���łɓ��͂���Ă��邩�H
	//		if (flgRstickX[temp_amount]) {
	//			//���͂���Ă�����false
	//			return false;
	//		}
	//		else {
	//			//���͂���Ă��Ȃ����
	//			//flgRstickX��true��ݒ�
	//			flgRstickX[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//���̃X�e�B�b�N�����͂���ĂȂ����
	//		//flgRstickX��false�ɐݒ�
	//		flgRstickX[temp_amount] = false;
	//	}
	//}
	return false;
}

bool CXIn::OnceRStickY(int amount){
	//int temp_amount = amount;
	//XInputGetState(
	//	0,			// DWORD	dwUserIndex
	//	&state);	// XINPUT_STATE* pState

	//if (amount < 128){
	//	//�X�e�B�b�N�����͂���Ă��邩�H
	//	if (LSTICKY <= amount){
	//		//���łɓ��͂���Ă��邩�H
	//		if (flgRstickY[temp_amount]) {
	//			//���͂���Ă�����false
	//			return false;
	//		}
	//		else {
	//			//���͂���Ă��Ȃ����
	//			//flgRstickY��true��ݒ�
	//			flgRstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//���̃X�e�B�b�N�����͂���ĂȂ����
	//		//flgRstickY��false�ɐݒ�
	//		flgRstickY[temp_amount] = false;
	//	}
	//}
	return false;
}

//�X�e�B�b�N�����͗ʂ����������͂��ꂽ���Ɉ�x����true��Ԃ�
bool CXIn::OnceStick(SHORT stick, float amount){
	int intamount = 128;
	if (amount >= -1.0f && amount != 0.0f && amount <= 1.0f){
		if (stick == LSTICKX){
			intamount = 128 + (amount * 32766);
			OnceLStickX(intamount);
		}
		if (stick == LSTICKY){
			intamount = 128 + (amount * 32766);
			OnceLStickY(intamount);
		}
		if (stick == RSTICKX){
			intamount = 128 + (amount * 32766);
			OnceLStickX(intamount);
		}
		if (stick == RSTICKY){
			intamount = 128 + (amount * 32766);
			OnceLStickY(intamount);
		}
	}
	return false;
}

//�g���K�[�����͗ʂ����������͂���Ă����true��Ԃ�
bool CXIn::PushTrigger(BYTE trigger, float amount){
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	if (amount > 0.0f && amount <= 1.0f){
		int intamount = amount * 255;
		if (trigger >= intamount)
			return true;
	}
	return false;
}

bool CXIn::OnceLTrigger(int amount){
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	//�g���K�[�����͂���Ă��邩�H
	if (LTRIGGER >= amount){
		//���łɓ��͂���Ă��邩�H
		if (flgLtrigger[amount]) {
			//���͂���Ă�����false
			return false;
		}
		else {
			//���͂���Ă��Ȃ����
			//flgLtrigger��true��ݒ�
			flgLtrigger[amount] = true;
			return true;
		}
	}
	else {
		//���̃g���K�[��������ĂȂ����
		//flgtrigger��false�ɐݒ�
		flgLtrigger[amount] = false;
	}
	return false;
}

bool CXIn::OnceRTrigger(int amount){
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	//�g���K�[�����͂���Ă��邩�H
	if (RTRIGGER >= amount){
		//���łɓ��͂���Ă��邩�H
		if (flgRtrigger[amount]) {
			//���͂���Ă�����false
			return false;
		}
		else {
			//���͂���Ă��Ȃ����
			//flgRtrigger��true��ݒ�
			flgRtrigger[amount] = true;
			return true;
		}
	}
	else {
		//���̃g���K�[��������ĂȂ����
		//flgRtrigger��false�ɐݒ�
		flgRtrigger[amount] = false;
	}
	return false;
}


bool CXIn::OnceTrigger(BYTE trigger, float amount){
	if (amount > 0.0f && amount <= 1.0f){
		int intamount = amount * 255;
		if (trigger == LTRIGGER)
			return OnceLTrigger(intamount);

		if (trigger == RTRIGGER)
			return OnceRTrigger(intamount);
	}
	return false;
}