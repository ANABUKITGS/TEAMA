#ifndef CMAPSTEEL_H
#define CMAPSTEEL_H
#include "CMapChip.h"

#define STEEL_UV mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 256, 64 , 0

class CMapSteel : public CMapChip{
private:
	CTexture mTexSteel;

public:
	float mVelocityY;
	bool mBreak;
	CMapSteel(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE * 2, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ESTEEL)
		, mVelocityY(0.0f)
	{
		mVelocityX = 0.0f;
		mRender = false;
		mBreak = false;
		mTexSteel.Load(".\\Data\\Images\\Map\\MapSteel.tga");
	}
	void Update();	//動きを処理する
	void Render();	//描画を処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	void Gravity();
	//RenderはCMapChipのRenderを使う
};
#endif