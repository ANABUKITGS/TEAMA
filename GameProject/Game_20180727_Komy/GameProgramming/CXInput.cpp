#include "CXInput.h"

#pragma comment (lib, "xinput.lib")

/*ボタンについて
#define XINPUT_GAMEPAD_DPAD_UP			パッド上
#define XINPUT_GAMEPAD_DPAD_DOWN		パッド下
#define XINPUT_GAMEPAD_DPAD_LEFT		パッド左
#define XINPUT_GAMEPAD_DPAD_RIGHT		パッド右
#define XINPUT_GAMEPAD_START			スタート
#define XINPUT_GAMEPAD_BACK				バック
#define XINPUT_GAMEPAD_LEFT_THUMB		左スティック 押し込み
#define XINPUT_GAMEPAD_RIGHT_THUMB		右スティック 押し込み
#define XINPUT_GAMEPAD_LEFT_SHOULDER	左ボタン
#define XINPUT_GAMEPAD_RIGHT_SHOULDER	右ボタン
#define XINPUT_GAMEPAD_A				Aボタン
#define XINPUT_GAMEPAD_B				Bボタン
#define XINPUT_GAMEPAD_X				Xボタン
#define XINPUT_GAMEPAD_Y				Yボタン
*/


XINPUT_STATE CXIn::state;

//デジタル ボタンが押されているかのフラグ
//trueのところのデジタル ボタンは押されている
bool CXIn::flgbutton[XINPUT_GAMEPAD_Y + 1];

//スティックの入力がされているかのフラグ
//trueのところのスティックは入力されている
bool CXIn::flgLstickX[65536];
bool CXIn::flgLstickY[65536];
bool CXIn::flgRstickX[65536];
bool CXIn::flgRstickY[65536];

//トリガーの入力がされているかのフラグ
bool CXIn::flgLtrigger[256];
bool CXIn::flgRtrigger[256];

/*
PushButton
デジタル ボタンが押されていればtrue
押されていなければfalse
-使い方-
Aボタンが押されているか？
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
デジタル ボタンが押された最初はtrue
押したままだと、その後はfalse
使い方
Aボタンが押されているか？
if(CKey::OnceButton(XINPUT_GAMEPAD_A))
*/
bool CXIn::OnceButton(int button) {
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState
	//デジタル ボタンが押されているか？
	if (BUTTONS button) {
		//すでに押されているか？
		if (flgbutton[button]) {
			//押されていたらfalse
			return false;
		}
		else {
			//押されていなければ
			//flgbuttonにtrueを設定
			flgbutton[button] = true;
			return true;
		}
	}
	else {
		//そのデジタル ボタンが押されてなければ
		//flgbuttonをfalseに設定
		flgbutton[button] = false;
	}
	return false;
}

//スティックが入力量よりも多く入力されている間trueを返す
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
		//スティックが入力されているか？
		if (LSTICKX <= amount){
			//すでに入力されているか？
			if (flgLstickX[temp_amount]) {
				//入力されていたらfalse
				return false;
			}
			else {
				//入力されていなければ
				//flgLstickXにtrueを設定
				flgLstickX[temp_amount] = true;
				return true;
			}
		}
		else {
			//そのスティックが入力されてなければ
			//flgLstickXをfalseに設定
			flgLstickX[temp_amount] = false;
		}
	}
	if (amount > 128){
		//スティックが入力されているか？
		if (LSTICKX >= amount){
			//すでに入力されているか？
			if (flgLstickX[temp_amount]) {
				//入力されていたらfalse
				return false;
			}
			else {
				//入力されていなければ
				//flgLstickXにtrueを設定
				flgLstickX[temp_amount] = true;
				return true;
			}
		}
		else {
			//そのスティックが入力されてなければ
			//flgLstickXをfalseに設定
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
	//	//スティックが入力されているか？
	//	if (LSTICKY <= amount){
	//		//すでに入力されているか？
	//		if (flgLstickY[temp_amount]) {
	//			//入力されていたらfalse
	//			return false;
	//		}
	//		else {
	//			//入力されていなければ
	//			//flgLstickYにtrueを設定
	//			flgLstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//そのスティックが入力されてなければ
	//		//flgLstickYをfalseに設定
	//		flgLstickY[temp_amount] = false;
	//	}
	//}
	//if (amount > 128){
	//	//スティックが入力されているか？
	//	if (LSTICKY >= amount){
	//		//すでに入力されているか？
	//		if (flgLstickY[temp_amount]) {
	//			//入力されていたらfalse
	//			return false;
	//		}
	//		else {
	//			//入力されていなければ
	//			//flgLstickYにtrueを設定
	//			flgLstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//そのスティックが入力されてなければ
	//		//flgLstickYをfalseに設定
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
	//	//スティックが入力されているか？
	//	if (LSTICKX <= amount){
	//		//すでに入力されているか？
	//		if (flgRstickX[temp_amount]) {
	//			//入力されていたらfalse
	//			return false;
	//		}
	//		else {
	//			//入力されていなければ
	//			//flgRstickXにtrueを設定
	//			flgRstickX[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//そのスティックが入力されてなければ
	//		//flgRstickXをfalseに設定
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
	//	//スティックが入力されているか？
	//	if (LSTICKY <= amount){
	//		//すでに入力されているか？
	//		if (flgRstickY[temp_amount]) {
	//			//入力されていたらfalse
	//			return false;
	//		}
	//		else {
	//			//入力されていなければ
	//			//flgRstickYにtrueを設定
	//			flgRstickY[temp_amount] = true;
	//			return true;
	//		}
	//	}
	//	else {
	//		//そのスティックが入力されてなければ
	//		//flgRstickYをfalseに設定
	//		flgRstickY[temp_amount] = false;
	//	}
	//}
	return false;
}

//スティックが入力量よりも多く入力された時に一度だけtrueを返す
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

//トリガーが入力量よりも多く入力されている間trueを返す
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

	//トリガーが入力されているか？
	if (LTRIGGER >= amount){
		//すでに入力されているか？
		if (flgLtrigger[amount]) {
			//入力されていたらfalse
			return false;
		}
		else {
			//入力されていなければ
			//flgLtriggerにtrueを設定
			flgLtrigger[amount] = true;
			return true;
		}
	}
	else {
		//そのトリガーが押されてなければ
		//flgtriggerをfalseに設定
		flgLtrigger[amount] = false;
	}
	return false;
}

bool CXIn::OnceRTrigger(int amount){
	XInputGetState(
		0,			// DWORD	dwUserIndex
		&state);	// XINPUT_STATE* pState

	//トリガーが入力されているか？
	if (RTRIGGER >= amount){
		//すでに入力されているか？
		if (flgRtrigger[amount]) {
			//入力されていたらfalse
			return false;
		}
		else {
			//入力されていなければ
			//flgRtriggerにtrueを設定
			flgRtrigger[amount] = true;
			return true;
		}
	}
	else {
		//そのトリガーが押されてなければ
		//flgRtriggerをfalseに設定
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