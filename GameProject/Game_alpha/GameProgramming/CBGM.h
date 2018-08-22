#ifndef CBGM_H
#define CBGM_H
#include <time.h>
#include "CSound.h"

#define SOUND_TITLE		1135	//タイトル BGM (ミリ秒)
#define SOUND_TUTORIAL	2670	//チュートリアル BGM (ミリ秒)
#define SOUND_MAIN				//本編 BGM (ミリ秒)
#define SOUND_BOSS		0		//ボス BGM (ミリ秒)
#define SOUND_RESULT	0		//リザルト BGM (ミリ秒)
#define SOUND_RANKING	0		//ランキング BGM (ミリ秒)

class CBGM {
private:
	static int starttime;	//BGMの開始時間
	static int musicnum;	//BGM番号

	static CSound mSoundTitle;		//タイトル用
	static CSound mSoundTutorial;	//チュートリアル用
	static CSound mSoundMain;		//本編用
	static CSound mSoundBoss;		//ボス用
	static CSound mSoundResult;		//リザルト用
	static CSound mSoundRanking;	//ランキング用

public:
	enum EMUSIC_NUM{
		ETITLE = 1,
		ETUTORIAL,
		EMAIN,
		EBOSS,
		ERESULT,
		ERANKING,
		ESIZE
	};

	void Init();
	void Update();
	static void AllStop();

	static void ChangeMusic(EMUSIC_NUM);
};

#endif