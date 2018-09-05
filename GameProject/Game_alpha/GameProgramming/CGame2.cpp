#include "CGame2.h"
#include "CFileIO.h"
#include "CMap.h"
#include "CCamera2D.h"
#include "CMapChip.h"
#include "CPlayerT.h"
#include "CScene.h"
#include "CScore.h"
#include "CTime.h"
#include "CBGM.h"
#include "CMapBackImage.h"
#include "CFade.h"
#include "CMapSwitchGround.h"
#include "CMapSign.h"
#include "CMapScroll.h"
#include "CBoss.h"

bool CGame2::mCheat[CHEAT_NUM::ESIZE];
int CGame2::mTime;
int CGame2::mTimeMin;
float CGame2::mTimeSec;
CMapBackImage *mBackImage[4];

CCamera2D CGame2::mCamera;

void CGame2::Init(const char *map) {
	CMapScroll::scroll_flg = false;
	mCamera.SetOrtho(WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2, WINDOW_SIZE_W / 2, WINDOW_SIZE_H / 2);
	MapLoad(map);
	//背景
	mBackImage[0] = new CMapBackImage(CVector2(mCamera.x, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	mBackImage[1] = new CMapBackImage(CVector2(mCamera.x + 1280, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER1);
	mBackImage[2] = new CMapBackImage(CVector2(mCamera.x, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER2);
	mBackImage[3] = new CMapBackImage(CVector2(mCamera.x + 1280, mCamera.y), CMapBackImage::ETEXTURE_LAYER::LAYER2);


	//カメラ基点
	CMapScroll::mpScroll = new CMapScroll();

	//スイッチ足場 青 有効化
	CMapSwitchGround::mNumber = ESWITCH_GROUND1;

	//チート初期化
	for (int i = CHEAT_NUM::EFLAG; i < CHEAT_NUM::ESIZE; i++)
		mCheat[i] = false;

	//スクロール 停止 解除
	CMapScroll::scroll_stop = false;
}

void CGame2::MapLoad(const char *map){
	char filepath[256];
	//	if (map == CMapIO::EGAMEMAP)
	//	sprintf(filepath, "%s", GAME_MAP);
	//else if (map == CMapIO::ETUTORIAL)
	sprintf(filepath, "%s", map);
	//else if (map == CMapIO::EEDITERMAP)
	//	sprintf(filepath, "%s", EDITER_MAP);
	//else{
	//	MessageBox(NULL, "マップデータの指定がされていません。", "エラー", 0x00040010L);
	//	return;
	//}
	FILE *fp = fopen(filepath, "rb");	//ファイルを開く(読み込み)
	if (fp == NULL){	//NULLが返ってきたらエラー
		MessageBox(NULL, "マップデータの読み込みに失敗しました。", "エラー", 0x00040010L);
		printf("Load : fopen error!\n");
	}
	else {
		fseek(fp, 0L, SEEK_END);
		int size = ftell(fp);
		int gamemap[MAP_SIZEY][MAP_SIZEX];
		//		char *buf = new char[size];	//ファイルサイズ+1バイト分の領域を確保
		fseek(fp, 0L, SEEK_SET);
		size = sizeof(gamemap);
		fread(gamemap, size, 1, fp);	//確保した領域にファイルサイズ分データを読み込む
		//		buf[size] = '\0';	//最後に\0を設定する（文字列の終端）
		fclose(fp);	//ファイルをクローズする

		CEditer::MakeTaskList((int*)gamemap);

		char loadmsg[MAX_PATH + 8];
		sprintf(loadmsg, "Load to %s\n", filepath);
		printf(loadmsg);
		fclose(fp);	//ファイルを閉じる
	}
}

void CGame2::Update() {
	//レイヤー1
	if (CGame2::mCamera.x < mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[0]->mPosition.x)
		mBackImage[1]->mPosition.x = mBackImage[0]->mPosition.x + 1280;

	if (CGame2::mCamera.x < mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[1]->mPosition.x)
		mBackImage[0]->mPosition.x = mBackImage[1]->mPosition.x + 1280;

	//レイヤー2
	if (CGame2::mCamera.x < mBackImage[2]->mPosition.x)
		mBackImage[3]->mPosition.x = mBackImage[2]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[2]->mPosition.x)
		mBackImage[3]->mPosition.x = mBackImage[2]->mPosition.x + 1280;

	if (CGame2::mCamera.x < mBackImage[3]->mPosition.x)
		mBackImage[2]->mPosition.x = mBackImage[3]->mPosition.x - 1280;

	if (CGame2::mCamera.x > mBackImage[3]->mPosition.x)
		mBackImage[2]->mPosition.x = mBackImage[3]->mPosition.x + 1280;

	if (CKey::Push('D')) {
		mCamera.x += 5;
	}
	if (CKey::Push('A')) {
		mCamera.x -= 5;
	}
#ifndef _DEBUG
	if (CKey::Push('P')) {
		mTimeMin = CTime::ElapsedTimeMin();
		mTimeSec = CTime::ElapsedTimeSec();
		CScore::GetScore();
		CSceneResult::mResultTag = CSceneResult::ESCORE;
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERESULT);
		
	}
#endif
	if (CGamePad::Once(PAD_10) || CKey::Once(VK_ESCAPE)){
		CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ETITLE);
		//CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
		//CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
	}
	if (CGamePad::Once(PAD_9) || CKey::Once(VK_RETURN)){
		if (CFade::mMapfile != CFade::EGAMEMAP_NUM::EMAIN && CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::EGAME)){
			if (CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
				CFade::mMapfile = CFade::EGAMEMAP_NUM::EMAIN;
			}
		}
	}

#ifdef _DEBUG
	if (CGamePad::Push(PAD_11) || CKey::Push(LVKF_CONTROL)){
		if (CGamePad::Once(PAD_1) || CKey::Once('1')){	//無敵
			if (!mCheat[CHEAT_NUM::EMUTEKI])
				mCheat[CHEAT_NUM::EMUTEKI] = true;
			else
				mCheat[CHEAT_NUM::EMUTEKI] = false;
		}
		if (CGamePad::Once(PAD_2) || CKey::Once('2')){	//上下のエリア制限 解除
			if (!mCheat[CHEAT_NUM::EAREA])
				mCheat[CHEAT_NUM::EAREA] = true;
			else
				mCheat[CHEAT_NUM::EAREA] = false;
		}
		if (CGamePad::Once(PAD_3) || CKey::Once('3')){	//強制スクロール 解除
			if (!mCheat[CHEAT_NUM::ESCROLL])
				mCheat[CHEAT_NUM::ESCROLL] = true;
			else
				mCheat[CHEAT_NUM::ESCROLL] = false;
		}
	}
#endif
	CTaskManager::Get()->Update();
	CTaskManager::Get()->Remove();
}

void CGame2::Render() {
	if (CPlayerT::mpPlayer == NULL){
		CBGM::AllStop();
		CSE::AllStop();
		MessageBox(NULL, "マップにプレイヤーが設置されていません。", "エラー", 0x00040010L);
		CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
		CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
		return;
	}
//	CCamera2D::Begin(0.0, WINDOW_SIZE_W, 0.0, WINDOW_SIZE_H);
	mCamera.x = CMapScroll::mpScroll->mPosition.x;
	mCamera.y = CMapScroll::mpScroll->mPosition.y;
	mCamera.Begin();
	CTaskManager::Get()->Render();
	CCamera2D::End();
#ifdef _DEBUG
	wchar_t jumptime_buf[256];
	swprintf(jumptime_buf, L"プレイヤー\nmVelocityX\n%6.2f\nmVelocityY\n%6.2f\nmPosition.x\n%.2f\nmPosition.y\n%.2f", CPlayerT::mpPlayer->mVelocityX, CPlayerT::mpPlayer->mVelocityY, CPlayerT::mpPlayer->mPosition.x, CPlayerT::mpPlayer->mPosition.y);
	CText::DrawStringW(jumptime_buf, 0, 0, 16, 1.0f, 0);
	CheatText();
#endif

	//チュートリアル メッセージ
	if (CMapSign::mView && CMapTextView::mpTextView == NULL){
		CMapTextView::mpTextView = new CMapTextView();
		CText::DrawSppedReset();
	}

	//経過時間
	wchar_t time_buf[64];
	for (int i = 0; i < 16; i++)
		time_buf[i] = '\0';
	swprintf(time_buf, L"%03d", (int)(CTime::GetTime()));
	CText::DrawStringImpact(time_buf, -620, 300, 32, 1.0f, 0);

	//ダイヤモンド
	swprintf(time_buf, L"宝");
	CText::DrawStringImpact(time_buf, -620, 250, 40, 1.0f, 0);
	swprintf(time_buf, L" × %02d", CPlayerT::mpPlayer->mJewel);
	CText::DrawStringImpact(time_buf, -588, 258, 24, 1.0f, 0);

	//ミニダイヤモンド
	swprintf(time_buf, L"片");
	CText::DrawStringImpact(time_buf, -612, 218, 24, 1.0f, 0);
	swprintf(time_buf, L" × %02d", CPlayerT::mpPlayer->mMiniJewel);
	CText::DrawStringImpact(time_buf, -588, 218, 24, 1.0f, 0);

	//残機
	swprintf(time_buf, L"命×%1d", CPlayerT::mpPlayer->mLife);
	CText::DrawStringImpact(time_buf, -620, -350, 48, 1.0f, 0);

	if (CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
		CText::DrawStringW(L"チュートリアル", -111, 328, 32, 1.0f, 0);
		CText::DrawStringW(L"９で スキップすることが できます。", -216, 304, 24, 1.0f, 0);
	}

	static float mTextAlpha = 0.0f;
	if (CPlayerT::mpPlayer->mLife < 1){
		mTextAlpha += 0.1f;
		CText::DrawStringW(L"ゲームオーバー", -224, -32, 64, mTextAlpha, 0);
		CText::DrawStringW(L"２で タイトルに もどる", -192, -64, 24, mTextAlpha, 0);
	}
	else
		mTextAlpha = 0.0f;
}

void CGame2::CheatText(){
#ifdef _DEBUG
	for (int i = CHEAT_NUM::EMUTEKI; i < CHEAT_NUM::ESIZE; i++){
		if (mCheat[i])
			mCheat[CHEAT_NUM::EFLAG] = true;	//このセッションでチートを使ったか
	}

	if (mCheat[CHEAT_NUM::EFLAG]){
		wchar_t cheat_buf[13];
		swprintf(cheat_buf, L"チートしよう セッション");
		CText::DrawStringW(cheat_buf, -640, 328, 16, 1.0f, 0);

		if (mCheat[CHEAT_NUM::EMUTEKI]){
			wchar_t cheatname_buf[5];
			swprintf(cheatname_buf, L"・むてき");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
		if (mCheat[CHEAT_NUM::EAREA]){
			wchar_t cheatname_buf[13];
			swprintf(cheatname_buf, L"\n・エリアせいげん なし");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
		if (mCheat[CHEAT_NUM::ESCROLL]){
			wchar_t cheatname_buf[17];
			swprintf(cheatname_buf, L"\n\n・きょうせいスクロール なし");
			CText::DrawStringW(cheatname_buf, -640, 312, 16, 1.0f, 0);
		}
	}
#endif
}