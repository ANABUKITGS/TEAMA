#include "CSE.h"

CSound CSE::mSoundText;
CSound CSE::mSoundJewelry;
CSound CSE::mSoundChikuwa;
CSound CSE::mSoundJump;
CSound CSE::mSoundDamage;
CSound CSE::mSoundSelect;
CSound CSE::mSoundScore;
CSound CSE::mSoundTurn;
CSound CSE::mSoundContinue;
CSound CSE::mSoundBoss[3];
CSound CSE::mSoundYoyo;
CSound CSE::mSoundCheckPoint;
CSound CSE::mSoundBack;
CSound CSE::mSoundSwitch;

void CSE::Init(){
	mSoundText.Load(".\\Data\\Sound\\SE\\Text.wav");
	mSoundJewelry.Load(".\\Data\\Sound\\SE\\Jewely2.wav");
	mSoundChikuwa.Load(".\\Data\\Sound\\SE\\Chikuwa.wav");
	mSoundJump.Load(".\\Data\\Sound\\SE\\Jump.wav");
	mSoundDamage.Load(".\\Data\\Sound\\SE\\Damage.wav");
	mSoundScore.Load(".\\Data\\Sound\\SE\\Score.wav");
	mSoundSelect.Load(".\\Data\\Sound\\SE\\Select.wav");
	mSoundTurn.Load(".\\Data\\Sound\\SE\\Turn.wav");
	mSoundContinue.Load(".\\Data\\Sound\\SE\\Continue.wav");
	mSoundBoss[0].Load(".\\Data\\Sound\\SE\\BossTelepo.wav");
	mSoundBoss[1].Load(".\\Data\\Sound\\SE\\BossTelepo2.wav");
	mSoundBoss[2].Load(".\\Data\\Sound\\SE\\BossYoyo.wav");
	mSoundYoyo.Load(".\\Data\\Sound\\SE\\Yoyo.wav");
	mSoundCheckPoint.Load(".\\Data\\Sound\\SE\\CheckPoint.wav");
	mSoundBack.Load(".\\Data\\Sound\\SE\\Back.wav");
	mSoundSwitch.Load(".\\Data\\Sound\\SE\\Switch.wav");
}

void CSE::AllStop(){
	mSoundText.Stop();
	mSoundJewelry.Stop();
	mSoundChikuwa.Stop();
	mSoundJump.Stop();
	mSoundDamage.Stop();
	mSoundScore.Stop();
	mSoundSelect.Stop();
	mSoundTurn.Stop();
	mSoundContinue.Stop();
	mSoundBoss[0].Stop();
	mSoundBoss[1].Stop();
	mSoundBoss[2].Stop();
	mSoundYoyo.Stop();
	mSoundCheckPoint.Stop();
	mSoundBack.Stop();
	mSoundSwitch.Stop();
}