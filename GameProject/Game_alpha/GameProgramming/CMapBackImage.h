#ifndef CMAPBACKIMAGE_H
#define CMAPBACKIMAGE_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMap.h"

#define BACK_UV mPosition.x - 640, mPosition.x + 640, mPosition.y - 360, mPosition.y + 360, 0, 1280, 720 , 0, 1.0f

class CMapBackImage : public CRectangle{
private:
	int texnum;
	CTexture mTexLayer1;
	CTexture mTexLayer2;

public:
	enum ETEXTURE_LAYER{
		LAYER1 = 1,
		LAYER2,
		ESIZE,
	};

	CMapBackImage(const CVector2 &pos, ETEXTURE_LAYER num)
		: CRectangle(pos, CVector2(0, 0), NULL)
	{
		mTexLayer1.Load(".\\Data\\Images\\Map\\Background1_1.tga");
		mTexLayer2.Load(".\\Data\\Images\\Map\\Background1_2.tga");

		texnum = num;
		mTag = ECELLNUM::ENONE;
		mPriority = 10;
		CTaskManager::Get()->Add(this);
	}
	void Update();
	void Render();
};
#endif