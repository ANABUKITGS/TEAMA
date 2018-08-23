#include "CScene.h"
#include "CScore.h"
#include "CGame2.h"
#include "CTime.h"
#include "CBGM.h"
#include "CMapBackImage.h"

extern CEditer mEditer;
extern CGame mGame;
extern CGame2 mGame2;
extern CCharcter player;
extern CTitle mTitle;
extern CGetScore mScore;

void CTitle::Init(){
	cursor_num = CSceneChange::EGAME;
	//テクスチャを読み込む
	mTexTitle.Load(".//Data//Images//Title//Title.tga");
}

void CTitle::Update(){
	mTexTitle.DrawImage(-640, 640, -360, 360, 0, 1280, 720, 0, 1.0f);
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush(VK_DOWN) || CKey::OncePush('S')) && cursor_num < CSceneChange::ESIZE - 1)
		cursor_num++;

	if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::OncePush(VK_UP) || CKey::OncePush('W')) && cursor_num > CSceneChange::EGAME)
		cursor_num--;
	
	if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN) || CKey::Once(VK_SPACE)){
		switch (cursor_num){
		case CSceneChange::ECSCENECHANGE_NUM::EGAME:
			CMapBackImage::mMapfile = CMapBackImage::EGAMEMAP_NUM::ETUTORIAL;
			CMapBackImage::mFade = CMapBackImage::EFADE_NUM::EFADEOUT;
			break;

		case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
			CSceneChange::changenum = cursor_num;
			CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ERANKING);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::ERESULT:
			CSceneChange::changenum = cursor_num;
			CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ERESULT);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
			mEditer.Init();
			CSceneChange::changenum = cursor_num;
			CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
			break;

		case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
			_sleep(500);
			exit(0);
			break;

		default:
			break;
		}
	}
	if (CGamePad::Once(PAD_9))
		CText::DrawSppedReset();

	/*カーソル*/
	switch (cursor_num){
	case CSceneChange::ECSCENECHANGE_NUM::EGAME:
		swprintf(cursor_buf, L"→");
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
		swprintf(cursor_buf, L"\n→");
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERESULT:
		swprintf(cursor_buf, L"\n\n→");
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
		swprintf(cursor_buf, L"\n\n\n→");
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
		swprintf(cursor_buf, L"\n\n\n\n→");
		break;

	default:
		break;
	}
}

void CTitle::Render(){
	CText::DrawStringWSetColor(L" ゲームスタート\n ランキング\n スコア\n エディター(かり)\n ゲームしゅうりょう", -200, 0, 32, WHITE, 1.0f, 0);
	CText::DrawStringWSetColor(cursor_buf, -200, 0, 32, WHITE, 1.0f, 0);

	CMapBackImage::RenderFade();
}