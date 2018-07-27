#include "CGamePad.h"

#define LSTICKX	0
#define LSTICKY	1
#define RSTICKX	2
#define RSTICKY	3

#define ONCEPUSH_LIMIT 30

//�f�W�^�� �{�^����������Ă��邩�̃t���O
bool CGamePad::flgbutton[16];

//L�X�e�B�b�N��X�����ɓ��͂�����Ă��邩�̃t���O
bool CGamePad::flgLstickX[256];

//L�X�e�B�b�N��Y�����ɓ��͂�����Ă��邩�̃t���O
bool CGamePad::flgLstickY[256];

//R�X�e�B�b�N��X�����ɓ��͂�����Ă��邩�̃t���O
bool CGamePad::flgRstickX[256];

//R�X�e�B�b�N��Y�����ɓ��͂�����Ă��邩�̃t���O
bool CGamePad::flgRstickY[256];

//OncePush�p Once�̎���
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
		//�f�W�^�� �{�^����������Ă��邩�H
		if (mpButtons[button]) {
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
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] <= amount) {
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
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] >= amount) {
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
		}

		if (sticknum == LSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] <= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgLstickY[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgLstickY��true��ݒ�
							flgLstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickY��false�ɐݒ�
						flgLstickY[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] >= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgLstickY[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgLstickY��true��ݒ�
							flgLstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickY��false�ɐݒ�
						flgLstickY[temp_amount] = false;
					}
				}
			}
		}

		if (sticknum == RSTICKX){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (mpPositions[sticknum] < 0.0f && mpPositions[sticknum] >= -1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] <= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgRstickX[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgRstickX��true��ݒ�
							flgRstickX[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickX��false�ɐݒ�
						flgRstickX[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] >= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgRstickX[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgRstickX��true��ݒ�
							flgRstickX[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickX��false�ɐݒ�
						flgRstickX[temp_amount] = false;
					}
				}
			}
		}

		if (sticknum == RSTICKY){
			if (amount < 0.0f){
				temp_amount = temp_amount * -1;
				if (-mpPositions[sticknum] < 0.0f && -mpPositions[sticknum] >= -1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] <= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgRstickY[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgRstickY��true��ݒ�
							flgRstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickY��false�ɐݒ�
						flgRstickY[temp_amount] = false;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] >= amount) {
						//���łɓ��͂���Ă��邩�H
						if (flgRstickY[temp_amount]) {
							//���͂���Ă�����false
							return false;
						}
						else {
							//���͂���Ă��Ȃ����
							//flgRstickY��true��ݒ�
							flgRstickY[temp_amount] = true;
							return true;
						}
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickY��false�ɐݒ�
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
			//�f�W�^�� �{�^����������Ă��邩�H
			if (mpButtons[button]) {
				if (oncetimebutton[button] < ONCEPUSH_LIMIT){
					oncetimebutton[button]++;
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
				else
					return mpButtons[button];
			}
			else {
				//���̃f�W�^�� �{�^����������ĂȂ����
				//flgbutton��false�ɐݒ�
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
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] <= amount) {
						if (oncetimeLstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickX[temp_amount]++;
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
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickX��false�ɐݒ�
						flgLstickX[temp_amount] = false;
						oncetimeLstickX[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] >= amount) {
						if (oncetimeLstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickX[temp_amount]++;
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
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickX��false�ɐݒ�
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
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] <= amount) {
						if (oncetimeLstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickY[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgLstickY[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgLstickY��true��ݒ�
								flgLstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickY��false�ɐݒ�
						flgLstickY[temp_amount] = false;
						oncetimeLstickY[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] >= amount) {
						if (oncetimeLstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeLstickY[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgLstickY[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgLstickY��true��ݒ�
								flgLstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgLstickY��false�ɐݒ�
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
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] <= amount) {
						if (oncetimeRstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickX[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgRstickX[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgRstickX��true��ݒ�
								flgRstickX[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickX��false�ɐݒ�
						flgRstickX[temp_amount] = false;
						oncetimeRstickX[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (mpPositions[sticknum] >= 0.0f && mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (mpPositions[sticknum] >= amount) {
						if (oncetimeRstickX[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickX[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgRstickX[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgRstickX��true��ݒ�
								flgRstickX[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickX��false�ɐݒ�
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
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] <= amount) {
						if (oncetimeRstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickY[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgRstickY[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgRstickY��true��ݒ�
								flgRstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickY��false�ɐݒ�
						flgRstickY[temp_amount] = false;
						oncetimeRstickY[temp_amount] = 0;
					}
				}
			}
			if (amount > 0.0f){
				temp_amount = temp_amount + 127;
				if (-mpPositions[sticknum] >= 0.0f && -mpPositions[sticknum] <= 1.0f){
					//�X�e�B�b�N�����͂���Ă��邩�H
					if (-mpPositions[sticknum] >= amount) {
						if (oncetimeRstickY[temp_amount] < ONCEPUSH_LIMIT){
							oncetimeRstickY[temp_amount]++;
							//���łɓ��͂���Ă��邩�H
							if (flgRstickY[temp_amount]) {
								//���͂���Ă�����false
								return false;
							}
							else {
								//���͂���Ă��Ȃ����
								//flgRstickY��true��ݒ�
								flgRstickY[temp_amount] = true;
								return true;
							}
						}
						else
							return true;
					}
					else {
						//���̃X�e�B�b�N�����͂���ĂȂ����
						//flgRstickY��false�ɐݒ�
						flgRstickY[temp_amount] = false;
						oncetimeRstickY[temp_amount] = 0;
					}
				}
			}
		}
	}
	return false;
}