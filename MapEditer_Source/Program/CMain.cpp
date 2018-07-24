#include "CMain.h"
#include <Windows.h>
#include "CText.h"
#include "CFrameRate.h"
#include "CEditer.h"

CEditer mEditer;

void CMain::Init() {
	//glutFullScreen();	//フルスクリーン
	CText::Init();	//テキストのテクスチャーの読み込みなど
	mEditer.Init();
}

//繰り返し実行する処理の定義
void CMain::Update() {
	CFrameRate::Render();
	mEditer.Update();
	mEditer.Render();
}