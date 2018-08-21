#ifndef CMAPCHECKPOINT_H
#define CMAPCHECKPOINT_H

#include "CMapChip.h"

#define CHECKPOINT_UV1 0 , 64 , 128 , 0
#define CHECKPOINT_UV2 0 , 64 , 256 , 128

class CMapCheckPoint : public CMapChip {
private:
	CTexture mTexCheckPoint;

public:
	CMapCheckPoint(const CVector2& pos, const CVector2& scale)
		//CMapChip‚Å‰Šú‰»
		: CMapChip(pos, scale, &mTexCheckPoint, CHECKPOINT_UV1, ECELLNUM::ECHECKPOINT)
	{
		mPriority = -10;
		mTexCheckPoint.Load(".\\Data\\Images\\Map\\Mapcheckpoint.tga");
	}
	void Update();
	bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
};

#endif