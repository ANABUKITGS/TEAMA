#ifndef CSCORE_H
#define CSCORE_H
#include "CText.h"
#include "CScene.h"
#include "CMain.h"


struct  SRanking{
	char n[3];
	int s;
};

class CGetScore:public CScene{
public:
	int mJewelScore;
	int mMiniJewelScore;
	int mTimerScore;
	int mLifeScore;
	static int mScore;
	static bool mSort;
	int mdummy;
	CGetScore(){
		mSceneTag = ESCORE;
	}
	void Init();
	void Update();
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