#ifndef CXINPUT_H
#define CXINPUT_H
#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>

#define BUTTONS		state.Gamepad.wButtons &			//デジタル ボタン | 戻り値 : 0～1
#define LTRIGGER	CXIn::state.Gamepad.bLeftTrigger	//右 トリガー | 戻り値 : 0～255
#define RTRIGGER	CXIn::state.Gamepad.bRightTrigger	//右 トリガー | 戻り値 : 0～255
#define LSTICKX		CXIn::state.Gamepad.sThumbLX		//左 スティック 横 | 戻り値 : -32768～32767
#define LSTICKY		CXIn::state.Gamepad.sThumbLY		//左 スティック 縦 | 戻り値 : -32768～32767
#define RSTICKX		CXIn::state.Gamepad.sThumbRX		//右 スティック 横 | 戻り値 : -32768～32767
#define RSTICKY		CXIn::state.Gamepad.sThumbRY		//右 スティック 縦 | 戻り値 : -32768～32767

class CXIn{
	//デジタル ボタンが押されているかのフラグ
	static bool flgbutton[XINPUT_GAMEPAD_Y + 1];

	//LスティックのX方向に入力がされているかのフラグ
	static bool flgLstickX[65536];

	//LスティックのY方向に入力がされているかのフラグ
	static bool flgLstickY[65536];

	//RスティックのX方向に入力がされているかのフラグ
	static bool flgRstickX[65536];

	//RスティックのY方向に入力がされているかのフラグ
	static bool flgRstickY[65536];

	static bool OnceLStickX(int);

	static bool OnceLStickY(int);

	static bool OnceRStickX(int);

	static bool OnceRStickY(int);

	//Lトリガーの入力がされているかのフラグ
	static bool flgLtrigger[256];

	//Rトリガーの入力がされているかのフラグ
	static bool flgRtrigger[256];

	static bool OnceLTrigger(int);

	static bool OnceRTrigger(int);
public:
	//XInput用
	static XINPUT_STATE state;

	//デジタル ボタンが押されている間trueを返す
	static bool PushButton(int);

	//デジタル ボタンが押された時に一度だけtrueを返す
	static bool OnceButton(int);

	//スティックが入力量よりも多く入力されている間trueを返す
	static bool PushStick(SHORT, float);

	//スティックが入力量よりも多く入力された時に一度だけtrueを返す
	static bool OnceStick(SHORT, float);

	//トリガーが入力量よりも多く入力されている間trueを返す
	static bool PushTrigger(BYTE, float);

	//トリガーが入力量よりも多く入力されている間trueを返す
	static bool OnceTrigger(BYTE, float);
};
#endif