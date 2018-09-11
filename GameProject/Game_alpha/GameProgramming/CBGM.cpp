#include "CBGM.h"

CSound CBGM::mSoundTitle;		//タイトル用
CSound CBGM::mSoundTutorial;	//チュートリアル用
CSound CBGM::mSoundMain;		//本編用
CSound CBGM::mSoundBoss;		//ボス用
CSound CBGM::mSoundResult;		//リザルト用
CSound CBGM::mSoundRanking;		//ランキング用

void CBGM::Init(){
	mSoundTitle.Load(".\\Data\\Sound\\BGM\\Title.mp3");
	mSoundTutorial.Load(".\\Data\\Sound\\BGM\\Tutorial.mp3");
	mSoundMain.Load(".\\Data\\Sound\\BGM\\Main.mp3");
	mSoundBoss.Load(".\\Data\\Sound\\BGM\\Boss.mp3");
	mSoundResult.Load("");
	mSoundRanking.Load("");
	mSoundTitle.Repeat();
}

void CBGM::AllStop(){
	mSoundTitle.Stop();
	mSoundTutorial.Stop();
	mSoundMain.Stop();
	mSoundBoss.Stop();
	mSoundResult.Stop();
	mSoundRanking.Stop();
}