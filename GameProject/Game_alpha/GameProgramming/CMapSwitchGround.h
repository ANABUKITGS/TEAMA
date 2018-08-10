#ifndef CMAPSWITCHGROUND_H
#define CMAPSWITCHGROUND_H

#include "CMapChip.h"

class CMapSwitchGround :public CMapChip{
public:
	static ECELLNUM mNumber;
	CMapSwitchGround(const CVector2& pos, const CVector2& scale, CTexture *texture, float uv0, float uv1, float uv2, float uv3, ECELLNUM number)
		//CMapChip‚Å‰Šú‰»
		:CMapChip(pos, scale, texture, uv0, uv1, uv2, uv3, ESWITCH_GROUND1)
	{
		CMapSwitchGround::mNumber = number;
		if (mNumber==ESWITCH_GROUND1)
			mTag = ESWITCH_GROUND1;
		else
			mTag = ESWITCH_GROUND2;

	}
	void Update();	//“®‚«‚ğˆ—‚·‚é
	//bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
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