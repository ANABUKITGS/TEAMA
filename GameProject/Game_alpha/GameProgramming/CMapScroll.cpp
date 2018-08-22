#include "CMapScroll.h"
#include "CPlayerT.h"

float CMapScroll::add_scroll = 0.0f;
bool CMapScroll::scroll_flg = false;
CMapScroll *CMapScroll::mScroll = 0;

void CMapScroll::Update(){
		if (!CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL]){
			if (scroll_flg){
				add_scroll = SCROLL_SPEED;
				mPosition.x += add_scroll;
			}
			mPosition.y = 408.0f;
		}
		else{
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