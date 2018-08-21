#include "CMapScroll.h"
#include "CPlayerT.h"

CMapScroll *CMapScroll::mScroll = 0;

void CMapScroll::Update(){
	if (!CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL]){
		mPosition.x++;
		mPosition.y = 360.0f;
	}
	else{
		mPosition.x = CPlayerT::mpPlayer->mPosition.x;
		mPosition.y = CPlayerT::mpPlayer->mPosition.y;
	}
}

void CMapScroll::Reset(){
	mPosition.x = CPlayerT::mpPlayer->mPosition.x;
}