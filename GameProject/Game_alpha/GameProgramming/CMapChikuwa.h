#ifndef CMAPCHIKUWA_H
#define CMAPCHIKUWA_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#define CHIKUWA_UV				0, CELLSIZE, CELLSIZE , 0
#define CHIKUWA_FALLING_TIME	15
#define CHIKUWA_LOST_TIME		CHIKUWA_FALLING_TIME * 10
#define FALLING_SPEED			0.25f

class CMapChikuwa : public CMapChip {
private:
	int lostcount;
	bool collision_flg;
	float mFalling;
	CVector2 setpos;
	CTexture mTexChikuwa;

public:
	CMapChikuwa(const CVector2& pos, const CVector2& scale)
		//CMapChipÇ≈èâä˙âª
		: CMapChip(pos, scale, &mTexChikuwa, CHIKUWA_UV, ECELLNUM::ECHIKUWA)
	{
		lostcount = 0;
		mFalling = 0.0f;
		collision_flg = false;
		setpos.x = mPosition.x;
		setpos.y = mPosition.y;
		mPriority = -10;
		mTexChikuwa.Load(".\\Data\\Images\\Map\\MapChikuwa.tga");
	}
	void Update();
	bool Collision(CRectangle *r);	//è’ìÀéûÇÃèàóù
	void Render();
};
#endif