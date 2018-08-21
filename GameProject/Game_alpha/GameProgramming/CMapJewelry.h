#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"

//宝石のマッピングデータ
#define JEWELRY_UV mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64, 0
#define JEWELRY2_UV mPosition.x - CELLSIZE / 4, mPosition.x + CELLSIZE / 4, mPosition.y - CELLSIZE / 4, mPosition.y + CELLSIZE / 4, 0, 64, 128, 64
/*
マップチップを継承して
宝石クラスを定義
*/
class CMapJewelry : public CMapChip {
private:
	CTexture mTexJewel;

public:
	CMapJewelry()
		: CMapChip(CVector2(0,0), CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{}
	CMapJewelry(const CVector2& pos) 
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
	}
	void Update();	//動きを処理する
	void Render();	//描画を処理する
	bool Collision(CRectangle *r);	//衝突時の処理
};


/*
マップチップを継承して
ミニ宝石クラスを定義
*/
class CMapMiniJewelry : public CMapChip {
private:
	CTexture mTexJewel;

public:
	CMapMiniJewelry(const CVector2& pos)
		//CMapChipで初期化
		: CMapChip(pos, CVector2(CELLSIZE / 4, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, EJEWELRY2)
	{
		mRender = false;
		mTexJewel.Load(".\\Data\\Images\\Map\\MapJewel.tga");
	}
	void Update();	//動きを処理する
	void Render();	//描画を処理する
	bool Collision(CRectangle *r);	//衝突時の処理
};

#endif
