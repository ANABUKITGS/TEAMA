#ifndef CMAPUNDER_H
#define CMAPUNDER_H

#include "CMapChip.h"

#define UNDER_UV mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0	//テクスチャのマッピングデータ
/*
下から抜ける床
*/
class CMapUnder : public CMapChip{
private:
	CTexture mTexUnder;

public:
	/*
	コンストラクタで初期化処理
	pos:位置座標
	scale:コリジョンの大きさ(四角形の大きさがそのままコリジョンになる)
	*/
	CMapUnder(CVector2 pos, CVector2 scale)
		:CMapChip(pos, scale, NULL, NULL, NULL, NULL, NULL, ECELLNUM::EUNDER)
	{
		mTexUnder.Load(".\\Data\\Images\\Map\\MapUnder.tga");
		mPriority = 9;
		mRender = false;
	}

	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	bool Collision(CRectangle*);
};

#endif