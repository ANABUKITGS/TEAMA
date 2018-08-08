#ifndef CMAPBOX_H
#define CMAPBOX_H

#include "CMapChip.h"

#define BOX_UV 0.0f,0.0f,0.0f,0.0f

class CMapBox : public CMapChip {
public:
	float mVelocityY;
	bool mBreak;
	CMapBox(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChipで初期化
		: CMapChip(pos, scale, texture, BOX_UV, EBOX)
	{
		mBreak = false;
	}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	void Gravity();
	//RenderはCMapChipのRenderを使う
};

#endif