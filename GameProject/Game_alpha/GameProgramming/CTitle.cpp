#include "CScene.h"
#include "CScore.h"
//hoge
extern CEditer mEditer;
extern CGame mGame;
extern CCharcter player;
extern CTitle mTitle;
extern CGetScore mScore;

void CTitle::Init(){
	cursor_num = CSceneChange::EGAME;
}

void CTitle::Update(){
	if ((CGamePad::OncePush(PAD_DOWN) || CGamePad::OncePush(PAD_LSTICKY, -0.5f) || CKey::OncePush(VK_DOWN) || CKey::OncePush('S')) && cursor_num < CSceneChange::ESIZE - 1)
		cursor_num++;

	if ((CGamePad::OncePush(PAD_UP) || CGamePad::OncePush(PAD_LSTICKY, 0.5f) || CKey::OncePush(VK_UP) || CKey::OncePush('W')) && cursor_num > CSceneChange::EGAME)
		cursor_num--;
	
	if (CGamePad::Once(PAD_2) || CKey::Once(VK_RETURN) || CKey::Once(VK_SPACE)){
		switch (cursor_num){
		default:
			break;

		case CSceneChange::EGAME:
			mGame.Init();
			player.Init();
			CSceneChange::changenum = cursor_num;
			break;

		case CSceneChange::ERANKING:
			CSceneChange::changenum = cursor_num;
			break;

		case CSceneChange::ESCORE:
			CSceneChange::changenum = cursor_num;
			break;

		case CSceneChange::EEDITER:
			mEditer.Init();
			CSceneChange::changenum = cursor_num;
			break;

		case CSceneChange::EEXIT:
			_sleep(500);
			exit(0);
			break;
		}
	}

	/*カーソル*/
	switch (cursor_num){
	default:
		break;

	case CSceneChange::EGAME:
		swprintf(cursor_buf, L"→");
		break;

	case CSceneChange::ERANKING:
		swprintf(cursor_buf, L"\n→");
		break;

	case CSceneChange::ESCORE:
		swprintf(cursor_buf, L"\n\n→");
		break;

	case CSceneChange::EEDITER:
		swprintf(cursor_buf, L"\n\n\n→");
		break;

	case CSceneChange::EEXIT:
		swprintf(cursor_buf, L"\n\n\n\n→");
		break;
	}
}

void CTitle::Render(){
	CText::DrawStringW(L"No Title!",-200, 200, 64, 1.0f, 0);
	CText::DrawStringW(L" ゲームスタート\n ランキング\n スコア\n エディター(かり)\n ゲームしゅうりょう", -200, 0, 32, 1.0f, 0);
	CText::DrawStringW(cursor_buf, -200, 0, 32, 1.0f, 0);
}