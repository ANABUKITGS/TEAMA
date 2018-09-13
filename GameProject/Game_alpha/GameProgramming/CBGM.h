#ifndef CBGM_H
#define CBGM_H
#include <time.h>
#include "CSound.h"

class CBGM {
public:
	static CSound mSoundTitle;		//タイトル用
	static CSound mSoundTutorial;	//チュートリアル用
	static CSound mSoundMain;		//本編用
	static CSound mSoundBoss;		//ボス用
	static CSound mSoundResult;		//リザルト用
	static CSound mSoundRanking;	//ランキング用
	static CSound mSoundEditer;		//エディター用
	static CSound mSoundCredit;		//クレジット用
	static CSound mSoundGameOver;	//ゲームオーバー用

	void Init();
	void Update();
	static void AllStop();
};

#endif