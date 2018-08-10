#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#include "CMapChip.h"

//スイッチで切り替わる足場のマッピングデータ
#define SWITCHGROUND_UV 0, 64, 64 * 6, 64 * 5
//スイッチで切り替わる足場のマッピングデータ
#define SWITCH_UV 0, 64, 64 * 6, 64 * 5

class CMapSwitchGround :public CMapChip{
public:
	static int mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, CTexture *texture, int number)
		//CMapChipで初期化
		:CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber == 0)
			CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND1);
		else
			CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH_GROUND2);
	}
	void Update();	//動きを処理する
	//bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};

class CMapSwitch :public CMapChip{
public:
	bool mCollision;	//true:当たっている false:当たってない
	CMapSwitch(const CVector2& pos, const CVector2& scale, CTexture *texture)
		//CMapChipで初期化
		:CMapChip(pos, scale, texture, SWITCHGROUND_UV, ESWITCH)
		, mCollision(false)
	{}
	void Update();	//動きを処理する
	bool Collision(CRectangle *r);	//衝突時の処理
	//RenderはCMapChipのRenderを使う
};
#endif