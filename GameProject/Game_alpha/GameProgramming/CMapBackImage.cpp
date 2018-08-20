#include "CMapBackImage.h"
#include "CGame2.h"

void CMapBackImage::Update(){

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