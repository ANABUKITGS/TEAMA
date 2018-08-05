#ifndef CJEWELRY_H
#define CJEWELRY_H

#include "CMapChip.h"

//宝石のマッピングデータ
#define JEWELRY_UV 0, 64, 64 * 6, 64 * 5
/*
マップチップを継承して
宝石クラスを定義
*/
class CJewelry : public CMapChip {
public:
	CJewelry(const CVector2& pos, const CVector2& scale, CTexture *texture) 
		//CMapChipで初期化
		: CMapChip(pos, scale, texture, JEWELRY_UV, EJEWELRY)
	{}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};

#endif
