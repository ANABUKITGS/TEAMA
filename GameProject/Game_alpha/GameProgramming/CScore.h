#ifndef CSCORE_H
#define CSCORE_H
#include "CText.h"
#include "CScene.h"
#include "CMain.h"


struct  SRanking{
	char r[4];
	char n[3];
	int s;
};

class CSceneResult :public CScene{
public:
	CTexture mTexResult;
	CTexture mTexResultback;
	enum EResultTag{
		EROOT,
		ESCORE,
		ENAME,
		ERANKING,
	};
	static EResultTag mResultTag;
	void Init();
	void Update();
};
class CScore:public CScene{
public:
	static int mJewelScore;
	static int mMiniJewelScore;
	static int mTimerScore;
	static int mLifeScore;
	static int mScore[5];
	static bool mSort;
	static int mScoreNum;
	CScore(){
		mSceneTag = ESCORE;
	}
	void Init();
	void Update();
	static void GetScore();
	int CountUp(int max,int count);
};

class CName:public CScene{
public:
	static char name[3];
	static int charnum;
	CName(){
		CScene::mSceneTag = ENAME;
	}
	void Init();
	void Update();
};
class CRanking :public CScene{
public:
	SRanking mRanking[3];
	CRanking(){
		mSceneTag = ERANKING;
	}
	void Init();
	void Update();
	void Sort(int score , char *name);
};
#endif