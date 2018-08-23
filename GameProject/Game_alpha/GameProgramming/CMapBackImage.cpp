#include "CMapBackImage.h"
#include "CGame2.h"
#include "CMapScroll.h"
#include "CPlayerT.h"
#include "CSE.h"
#include "CBGM.h"
#include "CTime.h"
#include "CScene.h"
#include "CTitle.h"

CMapBackImage::EFADE_NUM CMapBackImage::mFade = CMapBackImage::EFADE_NUM::EFALSE;
CMapBackImage::EGAMEMAP_NUM CMapBackImage::mMapfile = CMapBackImage::EGAMEMAP_NUM::ETUTORIAL;
extern CTitle mTitle;

CTexture CMapBackImage::mTexFade;
float CMapBackImage::mAlpha;
int CMapBackImage::change_scene = CSceneChange::ECSCENECHANGE_NUM::ETITLE;

void CMapBackImage::Update(){
	if ((CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL] || CMapScroll::scroll_flg) && !CMapScroll::scroll_stop){
		switch (texnum){
		case ETEXTURE_LAYER::LAYER1:
			mPosition.x += CMapScroll::add_scroll * 0.8;
			break;

		case ETEXTURE_LAYER::LAYER2:
			mPosition.x += CMapScroll::add_scroll * 0.5;
			break;

		default:
			break;
		}
	}
	mPosition.y = CMapScroll::mScroll->mPosition.y;
}

void CMapBackImage::Render(){
	switch (texnum){
	case ETEXTURE_LAYER::LAYER1:
		mTexLayer1.DrawImage(BACK_UV);
		break;

	case ETEXTURE_LAYER::LAYER2:
		mTexLayer2.DrawImage(BACK_UV);
		break;

	default:
		break;
	}
}

void CMapBackImage::ChangeFade(int scene){
	change_scene = scene;
	mFade = EFADE_NUM::EFADEOUT;
}

void CMapBackImage::RenderFade(){
	extern CGame2 mGame2;

	if (mFade == EFADE_NUM::EFALSE){
		mAlpha = 0.0f;
		return;
	}

	else if (mFade == EFADE_NUM::EFADEOUT){
		if (mAlpha < 1.0f)
			mAlpha += 0.025f;

		if (mAlpha >= 1.0f){
			mFade = EFADE_NUM::ETRUE;
			mAlpha = 1.0f;
			CSE::AllStop();
			CBGM::AllStop();
			switch (change_scene){
			case CSceneChange::ECSCENECHANGE_NUM::ETITLE:
				CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::EGAME:
				if (mMapfile == CMapBackImage::EGAMEMAP_NUM::ETUTORIAL){
					mGame2.Init(TUTORIAL_MAP);	//チュートリアル用 マップを 読み込む
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
				}
				else if (mMapfile == CMapBackImage::EGAMEMAP_NUM::EMAIN){
					mGame2.Init(GAME_MAP);		//本編用 マップを 読み込む
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::EMAIN);
				}
				else if (mMapfile == CMapBackImage::EGAMEMAP_NUM::EEDITER){
					mGame2.Init(EDITER_MAP);	//エディター用 マップを読み込む(仮)
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
				}
				CTime::GetStartTime();
				CSceneChange::changenum = mTitle.cursor_num;
				CMapScroll::mScroll->mPosition.x = 0.0f;
				CMapScroll::mScroll->mPosition.y = 0.0f;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
				CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ERANKING);
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ERANKING;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
				CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::EEDITER;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
				CBGM::AllStop();
				CSE::AllStop();
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::EEXIT;
				_sleep(500);
				exit(0);
				return;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::ERESULT:
				CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ERESULT);
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ERESULT;
				break;

			default:
				break;
			}
		}

		if (CPlayerT::mpPlayer != NULL)
			CPlayerT::mpPlayer->mVelocityX = 0.0f;
	}
	else if (mFade == EFADE_NUM::ETRUE){
		if (mAlpha > 0.0f)
			mAlpha -= 0.025f;

		if (mAlpha <= 0.0f){
			mAlpha = 0.0f;
			mFade = EFADE_NUM::EFALSE;
		}
	}
	mTexFade.DrawImageSetColor(FADE_UV, 0.0f, 0.0f, 0.0f, mAlpha);
	if (mFade != EFADE_NUM::ETRUE && change_scene != CSceneChange::ECSCENECHANGE_NUM::EEXIT)
		CText::DrawStringW(L"ロードちゅう", 0, 0, 32, mAlpha, 0);
}