#ifndef CMAPBACKIMAGE_H
#define CMAPBACKIMAGE_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMap.h"

#define BACK_UV mPosition.x - 640, mPosition.x + 640, mPosition.y - 360, mPosition.y + 360, 0, 1280, 720 , 0, 1.0f

#define FADE_UV -640, 640, -360, 360, 0, 1280, 720 , 0

class CMapBackImage : public CRectangle{
private:
	int texnum;
	CTexture mTexLayer1;
	CTexture mTexLayer2;

	static CTexture mTexFade;
	static float mAlpha;

public:
	enum ETEXTURE_LAYER{
		LAYER1 = 1,
		LAYER2,
	};

	enum EGAMEMAP_NUM{
		ETUTORIAL = 1,
		EMAIN,
		EEDITER,
	};
	static EGAMEMAP_NUM mMapfile;

	enum EFADE_NUM{
		EFALSE = 1,	//無効
		EFADEOUT,	//フェードアウト
		ETRUE,		//有効, フェードイン
	};
	static EFADE_NUM mFade;	//フェード効果

	CMapBackImage(const CVector2 &pos, ETEXTURE_LAYER tag)
		: CRectangle(pos, CVector2(0, 0), NULL)
	{
		mTexLayer1.Load(".\\Data\\Images\\Map\\Background1_1.tga");
		mTexLayer2.Load(".\\Data\\Images\\Map\\Background1_2.tga");

		texnum = tag;
		mTag = ECELLNUM::ENONE;
		mRender = false;

		if (tag == ETEXTURE_LAYER::LAYER1)
			mPriority = 11;

		else if (tag == ETEXTURE_LAYER::LAYER2)
			mPriority = 10;

		CTaskManager::Get()->Add(this);
	}
	void Update();
	void Render();

	static void RenderFade();
};
#endif