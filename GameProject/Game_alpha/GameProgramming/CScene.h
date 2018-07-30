#ifndef CSCENE_H
#define CSCENE_H
#include "CTexture.h"
#include "CText.h"


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
#endif
