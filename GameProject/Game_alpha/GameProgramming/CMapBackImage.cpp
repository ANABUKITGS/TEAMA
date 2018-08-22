#include "CMapBackImage.h"
#include "CGame2.h"
#include "CMapScroll.h"
#include "CPlayerT.h"
#include "CMapSign.h"
#include "CSE.h"
#include "CBGM.h"

CTexture CMapBackImage::mTexFade;
float CMapBackImage::mAlpha;

void CMapBackImage::Update(){
	if (CGame2::mCheat[CGame2::CHEAT_NUM::ESCROLL] || CMapScroll::scroll_flg){
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

void CMapBackImage::RenderFade(){
	extern CGame2 mGame2;

	if (CMapEndSign::tutorial_end == CMapEndSign::ETUTORIAL_END_NUM::EFALSE){
		mAlpha = 0.0f;
		return;
	}

	else if (CMapEndSign::tutorial_end == CMapEndSign::ETUTORIAL_END_NUM::EFADEOUT){
		if (mAlpha < 1.0f)
			mAlpha += 0.025f;

		if (mAlpha > 1.0f){
			CMapEndSign::tutorial_end == CMapEndSign::ETUTORIAL_END_NUM::ETRUE;
			mAlpha = 1.0f;
			CSE::AllStop();
			CBGM::AllStop();
			mGame2.Init(GAME_MAP);
			CMapScroll::mScroll->mPosition.x = 0.0f;
			CMapScroll::mScroll->mPosition.y = 0.0f;
		}

		CPlayerT::mpPlayer->mVelocityX = 0.0f;
	}
	else if (CMapEndSign::tutorial_end == CMapEndSign::ETUTORIAL_END_NUM::ETRUE){
		if (mAlpha > 0.0f)
			mAlpha -= 0.025f;
	}
	mTexFade.DrawImage(FADE_UV, mAlpha);
}