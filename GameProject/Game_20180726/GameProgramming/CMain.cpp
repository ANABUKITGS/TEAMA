//ヘッダファイルのインクルード
#include "CMain.h"
#include "glut.h"
#include "CVector2.h"
#include "CMatrix33.h"
#include "CText.h"
#include "CGamePad.h"

wchar_t gamepad_name[11];

//初めに1回だけ実行する処理の定義
void CMain::Init() {
	CText::Init();
	swprintf(gamepad_name, L"");
}

//繰り返し実行する処理の定義
void CMain::Update() {
	if (CGamePad::Push(PAD_1))
		swprintf(gamepad_name, L"1");
	else if (CGamePad::Push(PAD_2))
		swprintf(gamepad_name,L"2");
	else if (CGamePad::Push(PAD_3))
		swprintf(gamepad_name, L"3");
	else if (CGamePad::Push(PAD_4))
		swprintf(gamepad_name, L"4");
	else if (CGamePad::Push(PAD_5))
		swprintf(gamepad_name, L"5");
	else if (CGamePad::Push(PAD_6))
		swprintf(gamepad_name, L"6");
	else if (CGamePad::Push(PAD_7))
		swprintf(gamepad_name, L"7");
	else if (CGamePad::Push(PAD_8))
		swprintf(gamepad_name, L"8");
	else if (CGamePad::Push(PAD_9))
		swprintf(gamepad_name, L"9");
	else if (CGamePad::Push(PAD_10))
		swprintf(gamepad_name, L"10");
	else if (CGamePad::Push(PAD_11))
		swprintf(gamepad_name, L"11");
	else if (CGamePad::Push(PAD_12))
		swprintf(gamepad_name, L"12");
	else if (CGamePad::Push(PAD_UP))
		swprintf(gamepad_name, L"↑");
	else if (CGamePad::Push(PAD_RIGHT))
		swprintf(gamepad_name, L"→");
	else if (CGamePad::Push(PAD_DOWN))
		swprintf(gamepad_name, L"↓");
	else if (CGamePad::Push(PAD_LEFT))
		swprintf(gamepad_name, L"←");
	else if (CGamePad::Push(PAD_LSTICKX, 0.5f))
		swprintf(gamepad_name, L"ひだり スティック X0.5");
	else if (CGamePad::Push(PAD_LSTICKX, -0.5f))
		swprintf(gamepad_name, L"ひだり スティック X-0.5");
	else if (CGamePad::Push(PAD_LSTICKY, 0.5f))
		swprintf(gamepad_name, L"ひだり スティック Y0.5");
	else if (CGamePad::Push(PAD_LSTICKY, -0.5f))
		swprintf(gamepad_name, L"ひだり スティック Y-0.5");
	else if (CGamePad::Push(PAD_RSTICKX, 0.5f))
		swprintf(gamepad_name, L"みぎ スティック X0.5");
	else if (CGamePad::Push(PAD_RSTICKX, -0.5f))
		swprintf(gamepad_name, L"みぎ スティック X-0.5");
	else if (CGamePad::Push(PAD_RSTICKY, 0.5f))
		swprintf(gamepad_name, L"みぎ スティック Y0.5");
	else if (CGamePad::Push(PAD_RSTICKY, -0.5f))
		swprintf(gamepad_name, L"みぎ スティック Y-0.5");

	else
		swprintf(gamepad_name, L"おされていよ");
	CText::DrawStringW(gamepad_name, -350, 250, 32, 1.0f, 3);
}
