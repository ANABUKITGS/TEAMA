#ifndef CMAPBOX_H
#define CMAPBOX_H
#include "CMapChip.h"

#define BOX_UV mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 256, 256 , 0

class CMapBox : public CMapChip {
private:
	CTexture mTexBox;
	CVector2 mDefaultPos;

public:
	float mVelocityY;
	CMapBox(const CVector2& pos, bool Break = false)
		//CMapChipで初期化
		: CMapChip(pos + CVector2(0.0f, CELLSIZE / 2), CVector2(CELLSIZE, CELLSIZE), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EBOX)
		, mVelocityY(0.0f)
	{
		mVelocityX = 0.0f;
		mRender = false;
		mBreak = Break;
		mTexBox.Load(".\\Data\\Images\\Map\\MapBox.tga");
		mDefaultPos = pos + CVector2(0.0f, CELLSIZE / 2);
		mAlpha = 1.0f;
	}
	void Update();	//動きを処理する
	void Render();	//描画を処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	void Gravity();
	//RenderはCMapChipのRenderを使う
};

#endif