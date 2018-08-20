#ifndef CMAPBOX_H
#define CMAPBOX_H
#include "CMapChip.h"

#define BOX_UV mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE, mPosition.y + CELLSIZE, 0, 256, 256 , 0

class CMapBox : public CMapChip {
private:
	CTexture mTexBox;

public:
	float mVelocityY;
	static bool mBreak;
	CMapBox(const CVector2& pos)
		//CMapChip‚Å‰Šú‰»
		: CMapChip(pos, CVector2(CELLSIZE, CELLSIZE), NULL, NULL, NULL, NULL, NULL, ECELLNUM::EBOX)
	{
		mRender = false;
		mBreak = false;
		mTexBox.Load(".\\Data\\Images\\Map\\MapBox.tga");
	}
	void Update();	//“®‚«‚ğˆ—‚·‚é
	void Render();	//•`‰æ‚ğˆ—‚·‚é
	bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
	void Gravity();
	//Render‚ÍCMapChip‚ÌRender‚ğg‚¤
};

#endif