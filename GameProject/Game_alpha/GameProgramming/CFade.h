#ifndef CFADE_H
#define CFADE_H
#include "CRectangle.h"

#define FADE_UV	-640, 640, -360, 360, 0, 1280, 720 , 0
#define LOGO_UV	-384, 384, -40, 40, 0, 768, 80, 0

class CFade{
private:
	static CRectangle mRectFade;
	static CTexture mTexFade;
	static CTexture mTexLogo;
	static float mAlpha;
	static int change_scene;

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

	void Init();
	static bool ChangeFade(int);
	void RenderFade();
};
#endif