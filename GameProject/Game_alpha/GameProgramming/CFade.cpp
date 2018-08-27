#include "CFade.h"
#include "CGame2.h"
#include "CPlayerT.h"
#include "CBoss.h"
#include "CScene.h"
#include "CBGM.h"
#include "CMapScroll.h"
#include "CTime.h"
#include "CTitle.h"
#include "CMapSign.h"

float CFade::mAlpha = 0.0f;
int CFade::change_scene = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
CFade::EGAMEMAP_NUM CFade::mMapfile = CFade::EGAMEMAP_NUM::ETUTORIAL;
CFade::EFADE_NUM CFade::mFade = CFade::EFADE_NUM::EFALSE;		//フェード効果
CTexture CFade::mTexFade;
CRectangle CFade::mRectFade;
extern CTitle mTitle;

void CFade::Init(){
	mAlpha = 0.0f;
	change_scene = CSceneChange::ECSCENECHANGE_NUM::ETITLE;
	mMapfile = EGAMEMAP_NUM::ETUTORIAL;
	mFade = EFADE_NUM::EFALSE;
	mRectFade.SetVertex(-640, 640, -360, 360);
}

bool CFade::ChangeFade(int scene){
	if (mFade == EFADE_NUM::EFALSE){
		change_scene = scene;
		mFade = EFADE_NUM::EFADEOUT;
		return true;
	}
	return false;
}

void CFade::RenderFade(){
	extern CGame2 mGame2;
	mRectFade.Update();

	if (mFade == EFADE_NUM::EFALSE && mAlpha <= 0.0f){
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
				if (mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL){
					mGame2.Init(TUTORIAL_MAP);	//チュートリアル用 マップを 読み込む
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
				}
				else if (mMapfile == CFade::EGAMEMAP_NUM::EMAIN){
					mGame2.Init(GAME_MAP);		//本編用 マップを 読み込む
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::EMAIN);
				}
				else if (mMapfile == CFade::EGAMEMAP_NUM::EEDITER){
					mGame2.Init(EDITER_MAP);	//エディター用 マップを読み込む(仮)
					CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETUTORIAL);
				}
				CTime::GetStartTime();
				CSceneChange::changenum = mTitle.cursor_num;
				CMapScroll::mpScroll->mPosition.x = 0.0f;
				CMapScroll::mpScroll->mPosition.y = 0.0f;
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
				break;

			case CSceneChange::ECSCENECHANGE_NUM::ERESULT:
				CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ERESULT);
				CSceneChange::changenum = CSceneChange::ECSCENECHANGE_NUM::ERESULT;
				break;

			case CSceneChange::ECSCENECHANGE_NUM::EPLAYERDOWN:
				if (CMapBossRoomSign::mpBossRoomSign != NULL){
					CMapScroll::boss_scroll = false;
					CMapBossRoomSign::mpBossRoomSign->mColFlg = false;
				}
				CPlayerT::mpPlayer->mPosition = CPlayerT::mpPlayer->mReSpornPos;
				CMapScroll::mpScroll->Reset();
				CPlayerT::mpPlayer->player_ani_count = 0;
				CPlayerT::mpPlayer->player_ani_count_frame = 0;
				CPlayerT::mpPlayer->player_ani = CPlayerT::EPLAYERANI::EIDOL;
				CPlayerT::mpPlayer->mpWeapon = 0;
				CPlayerT::mpPlayer->mDirection = true;
				if (CBoss::mpBoss != NULL){
					CBoss::mpBoss->mDirection = false;
					CBoss::mpBoss->mBossMaxLife = CBoss::mpBoss->mBossLife;
					CBoss::mpBoss->mBossLifeProportion = static_cast <float> (CBoss::mpBoss->mBossLife) / static_cast <float> (CBoss::mpBoss->mBossMaxLife);
				}

				if (!CGame2::mCheat[CGame2::CHEAT_NUM::EMUTEKI]){
					CPlayerT::mpPlayer->mLife--;
					if (CBoss::mpBoss != NULL)
						CBoss::mpBoss->mBossMaxLife = CBoss::mpBoss->mBossLife;
					CPlayerT::mpPlayer->mJewel = CPlayerT::mpPlayer->mBackupJewel;
				}
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
	mTexFade.DrawImageSetColor(FADE_UV, BLACK, mAlpha);
	//mRectFade.Render(BLACK, mAlpha);
	if (mFade != EFADE_NUM::ETRUE && (change_scene == CSceneChange::ECSCENECHANGE_NUM::EGAME || change_scene == CSceneChange::ECSCENECHANGE_NUM::EEDITER))
		CText::DrawStringW(L"Now Loading...", 192, -360, 32, mAlpha, 0);
}