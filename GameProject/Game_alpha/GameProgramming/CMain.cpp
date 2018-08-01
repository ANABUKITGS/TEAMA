//ヘッダファイルのインクルード
#include "CMain.h"
#include "glut.h"
#include "CVector2.h"
#include "CMatrix33.h"
#include "CText.h"
#include "CGamePad.h"
#include "CCharcter.h"
#include "CMap.h"
#include "CScore.h"

CTexture mtexture;
CCharcter player;
CEditer mEditer;
CGame mGame;
CName mScore;
CScene::ESceneTag CMain::mSceneTag = CScene::EROOT;

wchar_t gamepad_name[64];

float move_x;
float move_y;

//初めに1回だけ実行する処理の定義
void CMain::Init() {
	CText::Init();
	/*player.Init();
	mEditer.Init();
	mGame.Init();*/
	mScore.Init();
	swprintf(gamepad_name, L"");
	move_x = 0.0f;
	move_x = 0.0f;
}

//繰り返し実行する処理の定義
void CMain::Update() {
	/*１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ*/
	//mEditer.Update();
	//mEditer.Render();
	/*mGame.Update();
	mGame.Render();
	player.Update();*/
	mScore.Update();
	if (CGamePad::Push(PAD_1))
		swprintf(gamepad_name, L"１");
	else if (CGamePad::Push(PAD_2))
		swprintf(gamepad_name,L"２");
	else if (CGamePad::Push(PAD_3))
		swprintf(gamepad_name, L"３");
	else if (CGamePad::Push(PAD_4))
		swprintf(gamepad_name, L"４");
	else if (CGamePad::Push(PAD_5))
		swprintf(gamepad_name, L"５");
	else if (CGamePad::Push(PAD_6))
		swprintf(gamepad_name, L"６");
	else if (CGamePad::Push(PAD_7))
		swprintf(gamepad_name, L"７");
	else if (CGamePad::Push(PAD_8))
		swprintf(gamepad_name, L"８");
	else if (CGamePad::Push(PAD_9))
		swprintf(gamepad_name, L"９");
	else if (CGamePad::Push(PAD_10))
		swprintf(gamepad_name, L"０");
	else if (CGamePad::Push(PAD_11))
		swprintf(gamepad_name, L"Ａ");
	else if (CGamePad::Push(PAD_12))
		swprintf(gamepad_name, L"Ｂ");
	else if (CGamePad::Push(PAD_UP))
		swprintf(gamepad_name, L"Ｃ");
	else if (CGamePad::Push(PAD_RIGHT))
		swprintf(gamepad_name, L"Ｄ");
	else if (CGamePad::Push(PAD_DOWN))
		swprintf(gamepad_name, L"Ｅ");
	else if (CGamePad::Push(PAD_LEFT))
		swprintf(gamepad_name, L"Ｆ");
	else if (CGamePad::Push(PAD_LSTICKY, 0.5f))
		swprintf(gamepad_name, L"Ｇ");
	else if (CGamePad::Push(PAD_LSTICKX, 0.5f))
		swprintf(gamepad_name, L"Ｈ");
	else if (CGamePad::Push(PAD_LSTICKY, -0.5f))
		swprintf(gamepad_name, L"Ｉ");
	else if (CGamePad::Push(PAD_LSTICKX, -0.5f))
		swprintf(gamepad_name, L"Ｊ");
	else if (CGamePad::Push(PAD_RSTICKY, 0.5f))
		swprintf(gamepad_name, L"Ｋ");
	else if (CGamePad::Push(PAD_RSTICKX, 0.5f))
		swprintf(gamepad_name, L"Ｌ");
	else if (CGamePad::Push(PAD_RSTICKY, -0.5f))
		swprintf(gamepad_name, L"Ｍ");
	else if (CGamePad::Push(PAD_RSTICKX, -0.5f))
		swprintf(gamepad_name, L"Ｎ");

	else
		swprintf(gamepad_name, L"おされてないよ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	CText::DrawStringW(gamepad_name, -350 + move_x, 250 + move_y, 32, 1.0f, 3);

	//if (CGamePad::OncePush(PAD_RIGHT) || CGamePad::OncePush(PAD_LSTICKX, 0.5f))
	//	move_x++;
	//if (CGamePad::OncePush(PAD_LEFT) || CGamePad::OncePush(PAD_LSTICKX, -0.5f))
	//	move_x--;
	//if (CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f))
	//	move_y++;
	//if (CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f))
	//	move_y--;
}
