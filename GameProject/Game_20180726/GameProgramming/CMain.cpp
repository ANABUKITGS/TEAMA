//ヘッダファイルのインクルード
#include "CMain.h"
#include "glut.h"
#include "CVector2.h"
#include "CMatrix33.h"
#include "CText.h"
#include "CFrameRate.h"


//初めに1回だけ実行する処理の定義
void CMain::Init() {
	CText::Init();
	
}

//繰り返し実行する処理の定義
void CMain::Update() {
	CText::DrawStringW(L"TEST", -350, 250, 32, 1.0f, 3);
	//フレームレートをタイトルバーに表示
	CFrameRate::Render();
}
