#ifndef CSCENE_H
#define CSCENE_H
#include "CTexture.h"
#include "CText.h"

#include "CCharcter.h"
#include "CMap.h"
#include "CTitle.h"


extern CTexture Texture;
extern CTexture Element;
extern CText ENumText;

class CScene{
public:
	char buf2[11];
	virtual ~CScene(){}
	virtual void Init(){}
	virtual void Update(){}
	enum ESceneTag{
		EROOT,
		ESCORE,
		ENAME,
		ERANKING,
	};
	ESceneTag mSceneTag;
};

class CSceneChange{
public:
	enum ECSCENECHANGE_NUM{
		ETITLE = 1,
		EGAME,
		ERANKING,
		EEDITER,
		EHOGE1,
		ESIZE
	};
	static int changenum;
	void Init();
	void Update();
	void Render();
};
#endif
