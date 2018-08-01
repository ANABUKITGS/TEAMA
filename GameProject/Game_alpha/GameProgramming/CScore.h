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
	static int mScore;
	bool mSort;
	int mdammy;
	int mScoreRank;
	CGetScore(){
		mSceneTag = ESCORE;
	}
	virtual void Init();
	virtual void Update();
};

class CName:public CScene{
public:
	static char name[3];
	int charnum = 0;
	CName(){
		mSceneTag = ENAME;
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
	void Sort();
};
#endif