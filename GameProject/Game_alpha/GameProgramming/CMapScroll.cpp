#include "CMapScroll.h"
#include "CPlayerT.h"

float CMapScroll::add_scroll = 0.0f;
CMapScroll *CMapScroll::mScroll = 0;

void CMapScroll::Update(){
	if (!CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL]){
		add_scroll = SCROLL_SPEED;
		mPosition.x += add_scroll;
		mPosition.y = 360.0f;
	}
	else{
		add_scroll = CPlayerT::mpPlayer->mPosition.x - mPosition.x;
		mPosition.x += add_scroll;
		mPosition.y = CPlayerT::mpPlayer->mPosition.y;
	}
}

void CMapScroll::Reset(){
	mPosition.x = CPlayerT::mpPlayer->mPosition.x;
}