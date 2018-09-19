#ifndef CSCORE_H
#define CSCORE_H
#include "CText.h"
#include "CScene.h"
#include "CMain.h"

#define NGWORD_NUM	6

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
private:
	CTexture mTexResultTitle;

public:
	static int mJewelScore;
	static int mMiniJewelScore;
	static int mTimerScore;
	static int mLifeScore;
	static int mScore[5];
	static bool mSort;
	static int mScoreNum;
	CScore(){
		CScene::mSceneTag = CScene::ESceneTag::ESCORE;
	}
	void Init();
	void Update();
	static void GetScore();
	int CountUp(int max,int count);
};

class CName:public CScene{
private:
	CTexture mTexName;
	bool CheckWord();
	struct  NGWord{
		char n[4];
	};
	NGWord mNGWord[NGWORD_NUM];

public:
	static char name[4];
	static int charnum;
	CName(){
		CScene::mSceneTag = CScene::ESceneTag::ENAME;
	}
	void Init();
	void Update();
};
class CRanking :public CScene{
private:
	CTexture mTexRankingTitle;

public:
	struct  SRanking{
		char r[4];
		char n[3];
		int s;
	};
	SRanking mRanking[3];
	/*bool mButton9;
	bool mButton10;
	bool mButton11;
	bool mButton12;*/
	bool mDelete;
	CRanking(){
		CScene::mSceneTag = CScene::ESceneTag::ERANKING;
		/*mButton9 = false;
		mButton10 = false;
		mButton11 = false;
		mButton12 = false;*/
		mDelete = false;
	}
	void Init();
	void Update();
	void Sort(int score , char *name);
};
#endif