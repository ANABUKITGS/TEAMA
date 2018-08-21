#ifndef CMAPJEWELRY_H
#define CMAPJEWELRY_H

#include "CMapChip.h"

//宝石のマッピングデータ
#define JEWELRY_UV 0, 64, 64 * 6, 64 * 5
#define JEWELRY2_UV 0, 64, 64 * 7, 64 * 6
/*
マップチップを継承して
宝石クラスを定義
*/
class CMapJewelry : public CMapChip {
public:
	CMapJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture) 
		//CMapChipで初期化
		: CMapChip(pos, scale, texture, JEWELRY_UV, EJEWELRY)
	{}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};

class CMapMiniJewelry : public CMapChip {
public:
	CMapMiniJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChipで初期化
		: CMapChip(pos, scale, texture, JEWELRY2_UV, EJEWELRY2)
	{}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};

#endif
