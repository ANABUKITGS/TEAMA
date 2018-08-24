//ヘッダファイルのインクルード
#include "CMain.h"
#include "glut.h"
#include "CVector2.h"
#include "CMatrix33.h"
#include "CText.h"
#include "CGamePad.h"
#include "CScene.h"
#include "CTime.h"
#include "CSE.h"
#include "CFade.h"

CTexture mtexture;
CSceneChange mChange;
CScene::ESceneTag CMain::mSceneTag = CScene::EROOT;

wchar_t gamepad_name[64];

CFade mFade;

//初めに1回だけ実行する処理の定義
void CMain::Init() {
	CText::Init();
	mChange.Init();
	swprintf(gamepad_name, L"");
	CSE::Init();
	mFade.Init();
}

//繰り返し実行する処理の定義
void CMain::Update() {
	mChange.Update();
	mFade.RenderFade();
	/*１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ*/
#ifdef _DEBUG
	if (CGamePad::Push(PAD_1))
		swprintf(gamepad_name, L"１\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_2))
		swprintf(gamepad_name, L"２\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_3))
		swprintf(gamepad_name, L"３\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_4))
		swprintf(gamepad_name, L"４\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_5))
		swprintf(gamepad_name, L"５\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_6))
		swprintf(gamepad_name, L"６\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_7))
		swprintf(gamepad_name, L"７\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_8))
		swprintf(gamepad_name, L"８\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_9))
		swprintf(gamepad_name, L"９\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_10))
		swprintf(gamepad_name, L"０\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_11))
		swprintf(gamepad_name, L"Ａ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_12))
		swprintf(gamepad_name, L"Ｂ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_UP))
		swprintf(gamepad_name, L"Ｃ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_RIGHT))
		swprintf(gamepad_name, L"Ｄ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_DOWN))
		swprintf(gamepad_name, L"Ｅ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_LEFT))
		swprintf(gamepad_name, L"Ｆ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");
	else if (CGamePad::Push(PAD_LSTICKY, 0.1f))
		swprintf(gamepad_name, L"Ｇ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_LSTICKY));
	else if (CGamePad::Push(PAD_LSTICKX, 0.1f))
		swprintf(gamepad_name, L"Ｈ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_LSTICKX));
	else if (CGamePad::Push(PAD_LSTICKY, -0.1f))
		swprintf(gamepad_name, L"Ｉ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_LSTICKY));
	else if (CGamePad::Push(PAD_LSTICKX, -0.1f))
		swprintf(gamepad_name, L"Ｊ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_LSTICKX));
	else if (CGamePad::Push(PAD_RSTICKY, 0.1f))
		swprintf(gamepad_name, L"Ｋ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_RSTICKY));
	else if (CGamePad::Push(PAD_RSTICKX, 0.1f))
		swprintf(gamepad_name, L"Ｌ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_RSTICKX));
	else if (CGamePad::Push(PAD_RSTICKY, -0.1f))
		swprintf(gamepad_name, L"Ｍ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_RSTICKY));
	else if (CGamePad::Push(PAD_RSTICKX, -0.1f))
		swprintf(gamepad_name, L"Ｎ%.3f\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ", CGamePad::GetStick(PAD_RSTICKX));
	else
		swprintf(gamepad_name, L"おされてないよ\n１２３４５６７８９０ＡＢＣＤＥＦＧＨＩＪＫＬＭＮＯＰＱＲ");

	CText::DrawStringW(gamepad_name, -640, -328, 32, 1.0f, 3);

	//漢字 テスト
	CText::DrawStringW(L"かんじの ひょうじテスト\n[制作チーム]\n前田  拓磨\n長尾  蓮\n小見山 嶺治\n南木  彩希\n石田  萌夏\n\n[先生]\n高橋  忍  先生\n平田  大  先生\n井上  萌美 先生", -640, 328, 32, 1.0f, 0);

	//フレームレート
	char fps_buf[16];
	sprintf(fps_buf, "%4.1fFPS", CTime::FrameRate());
	CText::DrawStringSetColor(fps_buf, -640, 344, 16, 0.0f, 1.0f, 0.0f, 1.0f, 0);
#endif
}