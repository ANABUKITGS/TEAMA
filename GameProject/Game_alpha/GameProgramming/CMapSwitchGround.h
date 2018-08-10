#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#include "CMapChip.h"

class CMapSwitchGround :public CMapChip{
public:
	static ECELLNUM mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, CTexture *texture, float uv0, float uv1, float uv2, float uv3, ECELLNUM number)
		//CMapChipで初期化
		:CMapChip(pos, scale, texture, uv0, uv1, uv2, uv3, ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber==ESWITCH_GROUND1)
			mTag = ESWITCH_GROUND1;
		else
			mTag = ESWITCH_GROUND2;

	}
	void Update();	//動きを処理する
	//bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う

};

class CMapSwitch :public CMapChip{
public:
	bool mCollision;	//true:当たっている false:当たってない
	CMapSwitch(const CVector2& pos, const CVector2& scale, CTexture *texture, float uv0, float uv1, float uv2, float uv3)
		//CMapChipで初期化
		:CMapChip(pos, scale, texture, uv0, uv1, uv2, uv3, ESWITCH)
		, mCollision(false)
	{}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};
#endif