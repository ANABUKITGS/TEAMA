#include "CMapScroll.h"
#include "CPlayerT.h"
#include "CMapSign.h"
#include "CFade.h"
#include "CBoss.h"

float CMapScroll::add_scroll = 0.0f;
bool CMapScroll::scroll_flg = false;
bool CMapScroll::scroll_stop = false;
bool CMapScroll::boss_scroll = false;
bool CMapScroll::sign_scroll = false;
CMapScroll *CMapScroll::mpScroll = 0;

void CMapScroll::Update(){
	if ((CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL &&
		CMapEndSign::mpEndSign != NULL &&CMapEndSign::mpEndSign->mPosition.x <= mPosition.x + 608.0f) ||
		((CFade::mMapfile == CFade::EGAMEMAP_NUM::EMAIN || CFade::mMapfile == CFade::EGAMEMAP_NUM::EEDITER) &&
		CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mPosition.x <= mPosition.x - 608.0f)){
		scroll_stop = true;

		if (CBoss::mpBoss != NULL && !CBoss::mpBoss->mBossBattle){
			CBoss::mpBoss->mBossBattle = true;
			CBoss::mpBoss->mAttackBehavior = CBoss::AttackBehavior::EMANTO;	//アイドル状態
		}
	}

	if (!CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL]){
		if (!scroll_stop){
			if (scroll_flg && !sign_scroll){
				if (!boss_scroll)
					add_scroll = SCROLL_SPEED;
				else{
					if (add_scroll <= BOSSROOM_SCROLL_SPEED)
						add_scroll += ADD_SCROLL_SPEED;
				}

				mPosition.x += add_scroll;
			}
			if (!scroll_flg && CPlayerT::mpPlayer->player_ani != CPlayerT::EPLAYERANI::EDOWN)
				mPosition.x = CPlayerT::mpPlayer->mPosition.x + 544.0f;
		}
		else{
			if (CMapEndSign::mpEndSign != NULL && CFade::mMapfile == CFade::EGAMEMAP_NUM::ETUTORIAL)
				mPosition.x = CMapEndSign::mpEndSign->mPosition.x - 608.0f;

			if (CMapBossRoomSign::mpBossRoomSign != NULL && CFade::mMapfile == CFade::EGAMEMAP_NUM::EMAIN || CFade::mMapfile == CFade::EGAMEMAP_NUM::EEDITER)
				mPosition.x = CMapBossRoomSign::mpBossRoomSign->mPosition.x + 608.0f;
		}
		mPosition.y = 408.0f;
	}
	else{
		scroll_stop = false;
		scroll_flg = false;
		add_scroll = CPlayerT::mpPlayer->mPosition.x - mPosition.x;
		mPosition.x += add_scroll;
		mPosition.y = CPlayerT::mpPlayer->mPosition.y;
	}

	if (CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg){
		boss_scroll = true;
	}
}

void CMapScroll::Reset(){
	mPosition.x = CPlayerT::mpPlayer->mPosition.x + 544.0f;
	scroll_flg = false;
	scroll_stop = false;
}