#include "CBGM.h"

CSound CBGM::mSoundTitle;		//タイトル用
CSound CBGM::mSoundTutorial;	//チュートリアル用
CSound CBGM::mSoundMain;		//本編用
CSound CBGM::mSoundBoss;		//ボス用
CSound CBGM::mSoundResult;		//リザルト用
CSound CBGM::mSoundRanking;		//ランキング用
CSound CBGM::mSoundEditer;		//エディター用
CSound CBGM::mSoundCredit;		//クレジット用

void CBGM::Init(){
	mSoundTitle.Load(".\\Data\\Sound\\BGM\\Title.mp3");
	mSoundTutorial.Load(".\\Data\\Sound\\BGM\\Tutorial.mp3");
	mSoundMain.Load(".\\Data\\Sound\\BGM\\Main.mp3");
	mSoundBoss.Load(".\\Data\\Sound\\BGM\\Boss.mp3");
	mSoundResult.Load(".\\Data\\Sound\\BGM\\Result.mp3");
	mSoundRanking.Load(".\\Data\\Sound\\BGM\\Ranking.mp3");
	mSoundEditer.Load(".\\Data\\Sound\\BGM\\Editer.mp3");
	mSoundCredit.Load(".\\Data\\Sound\\BGM\\Credit.mp3");

	mSoundTitle.Repeat();
}

void CBGM::AllStop(){
	mSoundTitle.Stop();
	mSoundTutorial.Stop();
	mSoundMain.Stop();
	mSoundBoss.Stop();
	mSoundResult.Stop();
	mSoundRanking.Stop();
	mSoundEditer.Stop();
	mSoundCredit.Stop();
}