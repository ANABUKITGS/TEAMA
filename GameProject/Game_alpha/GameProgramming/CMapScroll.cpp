#include "CMapScroll.h"
#include "CPlayerT.h"
#include "CMapSign.h"
#include "CMapBackImage.h"

float CMapScroll::add_scroll = 0.0f;
bool CMapScroll::scroll_flg = false;
bool CMapScroll::scroll_stop = false;
CMapScroll *CMapScroll::mScroll = 0;

void CMapScroll::Update(){
	if (CMapBackImage::mMapfile == CMapBackImage::EGAMEMAP_NUM::ETUTORIAL && CMapEndSign::mpEndSign != NULL && CMapEndSign::mpEndSign->mPosition.x <= mPosition.x + 608.0f)
		scroll_stop = true;

		if (!CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL]){
			if (CMapBackImage::mMapfile != CMapBackImage::EGAMEMAP_NUM::ETUTORIAL || !scroll_stop){
				if (scroll_flg){
					add_scroll = SCROLL_SPEED;
					mPosition.x += add_scroll;
				}
			}
			else{
				mPosition.x = CMapEndSign::mpEndSign->mPosition.x - 608.0f;
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
}

void CMapScroll::Reset(){
	mPosition.x = CPlayerT::mpPlayer->mPosition.x;
	scroll_flg = false;
}