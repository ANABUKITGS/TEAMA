#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#define SWITCH_GROUND_POS	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2
#define SWITCH_GROUND_UV1	0, 64, 64, 0
#define SWITCH_GROUND_UV2	0, 64, 128, 64
#define SWITCH_INTERVAL 30

#include "CMapChip.h"

class CMapSwitchGround :public CMapChip{
private:
	CTexture mTexSwitchGround;
public:
	static ECELLNUM mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, ECELLNUM number)
		//CMapChipで初期化
		:CMapChip(pos, scale, NULL, NULL, NULL, NULL, NULL, ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber==ESWITCH_GROUND1)
			mTag = ESWITCH_GROUND1;
		else
			mTag = ESWITCH_GROUND2;

		mTexSwitchGround.Load(".\\Data\\Images\\Map\\MapSwitchGround.tga");
		mRender = false;
	}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();					//描画処理
	//RenderはCMapChipのRenderを使う

};

class CMapSwitch :public CMapChip{
public:
	bool mCollision;	//true:当たっている false:当たってない
	int mCollisionInterval;	//次に衝突できるまでのインターバル
	CMapSwitch(const CVector2& pos, const CVector2& scale, CTexture *texture, float uv0, float uv1, float uv2, float uv3)
		//CMapChipで初期化
		:CMapChip(pos, scale, texture, uv0, uv1, uv2, uv3, ESWITCH)
		, mCollision(false)
	{
		mCollisionInterval = SWITCH_INTERVAL;
	}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	bool Collision();
	//RenderはCMapChipのRenderを使う
};
#endif