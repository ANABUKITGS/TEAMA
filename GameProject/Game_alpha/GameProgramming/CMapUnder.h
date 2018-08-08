#ifndef CMAPUNDER_H
#define CMAPUNDER_H

#include "CMapChip.h"

#define TEXUV 0, 64, 64 * 6, 64 * 5	//テクスチャのマッピングデータ
/*
下から抜ける床
*/
class CMapUnder : public CMapChip{
public:
	/*
	コンストラクタで初期化処理
	pos:位置座標
	scale:コリジョンの大きさ(四角形の大きさがそのままコリジョンになる)
	*/
	CMapUnder(CVector2 pos, CVector2 scale, CTexture*Texture)
		:CMapChip(pos, scale, Texture, TEXUV, ECELLNUM::EUNDER)
	{}

	//更新処理
	void Update();
	//衝突処理
	bool Collision(CRectangle*);
};

#endif