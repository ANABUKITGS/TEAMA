#ifndef CMAPBELT_H
#define CMAPBELT_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#define BELT_UV1L	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 64 , 0, 1.0f
#define BELT_UV1R	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 64, 0, 64 , 0, 1.0f
#define BELT_UV2	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 128 , 64, 1.0f
#define BELT_UV3	mPosition.x - CELLSIZE / 2, mPosition.x + CELLSIZE / 2, mPosition.y - CELLSIZE / 2, mPosition.y + CELLSIZE / 2, 0, 64, 192, 128, 1.0f

#define BELT_SPEED	3.0f

class CMapBelt : public CMapChip{
private:
	ECELLNUM mDirection;
	int texture_pos;

public:
	CMapBelt(const CVector2& pos, const CVector2& scale, ECELLNUM tag, int texpos)
		//CMapChipÇ≈èâä˙âª
		: CMapChip(pos, scale, NULL, NULL, NULL, NULL, NULL, tag)
	{
		mDirection = tag;
		texture_pos = texpos;
		mTexBelt.Load(".\\Data\\Images\\Map\\MapBelt.tga");
	}

	static CMapBelt *mpBelt;
	CTexture mTexBelt;

	void Update();
	bool Collision(CRectangle *r);	//è’ìÀéûÇÃèàóù
	void Render();
};
#endif