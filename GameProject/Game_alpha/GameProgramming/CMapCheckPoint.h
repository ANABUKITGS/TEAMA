#ifndef CMAPCHECKPOINT_H
#define CMAPCHECKPOINT_H

#include "CMapChip.h"

#define CHECKPOINT_POS	mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE * 1.5
#define CHECKPOINT_UV1	0, 128 , 128 , 0
#define CHECKPOINT_UV2	128 * check_ani_count, 128 * (check_ani_count + 1), 128, 0

#define CHECK_ANI_COUNT_FLAME	6

class CMapCheckPoint : public CMapChip {
private:
	CTexture mTexCheckPoint;
	int check_ani_count;
	int check_ani_count_flame;
	bool mCheck;

public:
	CMapCheckPoint(const CVector2& pos)
		//CMapChipÇ≈èâä˙âª
		: CMapChip(pos, CVector2(CELLSIZE / 3, CELLSIZE / 2), NULL, NULL, NULL, NULL, NULL, ECELLNUM::ECHECKPOINT)
	{
		mRender = false;
		mPriority = -10;
		mTexCheckPoint.Load(".\\Data\\Images\\Map\\Mapcheckpoint.tga");
		check_ani_count = 0;
		check_ani_count_flame = 0;
		mCheck = false;
	}
	void Update();
	void Render();
	bool Collision(CRectangle *r);	//è’ìÀéûÇÃèàóù
};

#endif