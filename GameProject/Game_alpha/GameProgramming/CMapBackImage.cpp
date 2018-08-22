#include "CMapBackImage.h"
#include "CGame2.h"
#include "CMapScroll.h"
#include "CPlayerT.h"

void CMapBackImage::Update(){
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