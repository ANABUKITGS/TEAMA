#include "CGamePad.h"

#define LSTICKX	0
#define LSTICKY	1
#define RSTICKX	2
#define RSTICKY	3

#define ONCEPUSH_LIMIT 30

//デジタル ボタンが押されているかのフラグ
bool CGamePad::flgbutton[16];

//LスティックのX方向に入力がされているかのフラグ
bool CGamePad::flgLstickX[256];

//LスティックのY方向に入力がされているかのフラグ
bool CGamePad::flgLstickY[256];

//RスティックのX方向に入力がされているかのフラグ
bool CGamePad::flgRstickX[256];

//RスティックのY方向に入力がされているかのフラグ
bool CGamePad::flgRstickY[256];

//OncePush用 Onceの時間
unsigned int CGamePad::oncetimebutton[16];

unsigned int CGamePad::oncetimeLstickX[256];

unsigned int CGamePad::oncetimeLstickY[256];

unsigned int CGamePad::oncetimeRstickX[256];

unsigned int CGamePad::oncetimeRstickY[256];

CGamePad CGamePad::mGamePad;
const unsigned char* CGamePad::mpButtons = 0;
const float* CGamePad::mpPositions = 0;

bool CGamePad::Push(int button, float amount){
	mGamePad.Update();
//	if (!mpButtons || !mpPositions) return false;
	if (button > -1)
		return mpButtons[button];

	if (button < 0){
		if (amount > 0.0f){
			if (button == -1 && mpPositions[LSTICKX] >= amount)
				return true;

			if (button == -2 && -mpPositions[LSTICKY] >= amount)
				return true;

			if (button == -3 && mpPositions[RSTICKX] >= amount)
				return true;

			if (button == -4 && -mpPositions[RSTICKY] >= amount)
				return true;
		}
		if (amount < 0.0f){
			if (button == -1 && mpPositions[LSTICKX] <= amount)
				return true;

			if (button == -2 && -mpPositions[LSTICKY] <= amount)
				return true;

			if (button == -3 && mpPositions[RSTICKX] <= amount)
				return true;

			if (button == -4 && -mpPositions[RSTICKY] <= amount)
				return true;
		}
	}
	return false;
}

bool CGamePad::Once(int button, float amount){
//	if (!mpButtons || !mpPositions) return false;
	if (button > -1){
		//デジタル ボタンが押されているか？
		if (mpButtons[button]) {
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
	}
	if (button < 0){
		int temp_amount = amount * 127;
		int sticknum;

		if (button == -1)
			sticknum = LSTICKX;

		else if (button == -2)
			sticknum = LSTICKY;

		else if (button == -3)
			sticknum = RSTICKX;

		else if (button == -4)
			sticknum = RSTICKY;

		if (sticknum == LSTICKX){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (mpPositions[sticknum] < 0.0f && mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] <= amount) {
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
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] >= amount) {
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
		}

		if (sticknum == LSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] <= amount) {
						//すでに入力されているか？
						if (flgLstickY[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgLstickYにtrueを設定
							flgLstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickYをfalseに設定
						flgLstickY[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] >= amount) {
						//すでに入力されているか？
						if (flgLstickY[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgLstickYにtrueを設定
							flgLstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickYをfalseに設定
						flgLstickY[temp_amount] = false;
					}
				}
			}
		}

		if (sticknum == RSTICKX){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (mpPositions[sticknum] < 0.0f && mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] <= amount) {
						//すでに入力されているか？
						if (flgRstickX[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgRstickXにtrueを設定
							flgRstickX[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickXをfalseに設定
						flgRstickX[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] >= amount) {
						//すでに入力されているか？
						if (flgRstickX[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgRstickXにtrueを設定
							flgRstickX[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickXをfalseに設定
						flgRstickX[temp_amount] = false;
					}
				}
			}
		}

		if (sticknum == RSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] <= amount) {
						//すでに入力されているか？
						if (flgRstickY[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgRstickYにtrueを設定
							flgRstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickYをfalseに設定
						flgRstickY[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] >= amount) {
						//すでに入力されているか？
						if (flgRstickY[temp_amount]) {
							//入力されていたらfalse
							return false;
						}
						else {
							//入力されていなければ
							//flgRstickYにtrueを設定
							flgRstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickYをfalseに設定
						flgRstickY[temp_amount] = false;
					}
				}
			}
		}
	}
	return false;
}

bool CGamePad::OncePush(int button, float amount){
//	if (!mpButtons || !mpPositions) return false;
	if (button > -1){
			//デジタル ボタンが押されているか？
			if (mpButtons[button]) {
				if (oncetimebutton[button] < ONCEPUSH_LIMIT){
					oncetimebutton[button]++;
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
				else
					return mpButtons[button];
			}
			else {
				//そのデジタル ボタンが押されてなければ
				//flgbuttonをfalseに設定
				flgbutton[button] = false;
				oncetimebutton[button] = 0;
			}
	}
	if (button < 0){
		int temp_amount = amount * 127;
		int sticknum;

		if (button == -1)
			sticknum = LSTICKX;

		else if (button == -2)
			sticknum = LSTICKY;

		else if (button == -3)
			sticknum = RSTICKX;

		else if (button == -4)
			sticknum = RSTICKY;

		if (sticknum == LSTICKX){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (mpPositions[sticknum] < 0.0f && mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] <= amount) {
						if (oncetimeLstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickX[temp_amount]++;
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
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickXをfalseに設定
						flgLstickX[temp_amount] = false;
						oncetimeLstickX[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] >= amount) {
						if (oncetimeLstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickX[temp_amount]++;
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
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickXをfalseに設定
						flgLstickX[temp_amount] = false;
						oncetimeLstickX[temp_amount] = 0;
					}
				}
			}
		}

		if (sticknum == LSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] <= amount) {
						if (oncetimeLstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickY[temp_amount]++;
							//すでに入力されているか？
							if (flgLstickY[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgLstickYにtrueを設定
								flgLstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickYをfalseに設定
						flgLstickY[temp_amount] = false;
						oncetimeLstickY[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] >= amount) {
						if (oncetimeLstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickY[temp_amount]++;
							//すでに入力されているか？
							if (flgLstickY[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgLstickYにtrueを設定
								flgLstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgLstickYをfalseに設定
						flgLstickY[temp_amount] = false;
						oncetimeLstickY[temp_amount] = 0;
					}
				}
			}
		}

		if (sticknum == RSTICKX){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (mpPositions[sticknum] < 0.0f && mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] <= amount) {
						if (oncetimeRstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickX[temp_amount]++;
							//すでに入力されているか？
							if (flgRstickX[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgRstickXにtrueを設定
								flgRstickX[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickXをfalseに設定
						flgRstickX[temp_amount] = false;
						oncetimeRstickX[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (mpPositions[sticknum] >= amount) {
						if (oncetimeRstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickX[temp_amount]++;
							//すでに入力されているか？
							if (flgRstickX[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgRstickXにtrueを設定
								flgRstickX[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickXをfalseに設定
						flgRstickX[temp_amount] = false;
						oncetimeRstickX[temp_amount] = 0;
					}
				}
			}
		}

		if (sticknum == RSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] <= amount) {
						if (oncetimeRstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickY[temp_amount]++;
							//すでに入力されているか？
							if (flgRstickY[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgRstickYにtrueを設定
								flgRstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickYをfalseに設定
						flgRstickY[temp_amount] = false;
						oncetimeRstickY[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//スティックが入力されているか？
					if (-mpPositions[sticknum] >= amount) {
						if (oncetimeRstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickY[temp_amount]++;
							//すでに入力されているか？
							if (flgRstickY[temp_amount]) {
								//入力されていたらfalse
								return false;
							}
							else {
								//入力されていなければ
								//flgRstickYにtrueを設定
								flgRstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//そのスティックが入力されてなければ
						//flgRstickYをfalseに設定
						flgRstickY[temp_amount] = false;
						oncetimeRstickY[temp_amount] = 0;
					}
				}
			}
		}
	}
	return false;
}