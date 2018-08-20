#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#define SWITCH_GROUND_POS	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2
#define SWITCH_GROUND_UV1	0, 64, 64, 0
#define SWITCH_GROUND_UV2	0, 64, 128, 64

#include "CMapChip.h"

class CMapSwitchGround :public CMapChip{
private:
	CTexture mTexSwitchGround;
public:
	static ECELLNUM mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, ECELLNUM number)
		//CMapChip‚Å‰Šú‰»
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
	void Update();	//“®‚«‚ğˆ—‚·‚é
	bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
	void Render();					//•`‰æˆ—
	//Render‚ÍCMapChip‚ÌRender‚ğg‚¤

};

class CMapSwitch :public CMapChip{
public:
	bool mCollision;	//true:“–‚½‚Á‚Ä‚¢‚é false:“–‚½‚Á‚Ä‚È‚¢
	CMapSwitch(const CVector2& pos, const CVector2& scale, CTexture *texture, float uv0, float uv1, float uv2, float uv3)
		//CMapChip‚Å‰Šú‰»
		:CMapChip(pos, scale, texture, uv0, uv1, uv2, uv3, ESWITCH)
		, mCollision(false)
	{}
	void Update();	//“®‚«‚ğˆ—‚·‚é
	bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
	//Render‚ÍCMapChip‚ÌRender‚ğg‚¤
};
#endif