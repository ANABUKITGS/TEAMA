#ifndef CMAPUNDER_H
#define CMAPUNDER_H

#include "CMapChip.h"

#define TEXUV 0, 64, 64 * 6, 64 * 5	//テクスチャのマッピングデータ
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
	CMapUnder(CVector2 pos, CVector2 scale, CTexture*Texture)
		:CMapChip(pos, scale, Texture, TEXUV, ECELLNUM::EUNDER)
	{
		mTexUnder.Load(".\\Data\\Images\\Map\\Under.tga");
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