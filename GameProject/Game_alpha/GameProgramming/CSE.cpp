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
CSound CSE::mSoundBossTelepo[2];
CSound CSE::mSoundYoyo;

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
	mSoundBossTelepo[0].Load(".\\Data\\Sound\\SE\\BossTelepo.wav");
	mSoundBossTelepo[1].Load(".\\Data\\Sound\\SE\\BossTelepo2.wav");
	mSoundYoyo.Load(".\\Data\\Sound\\SE\\Yoyo.wav");
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
	mSoundBossTelepo[0].Stop();
	mSoundBossTelepo[1].Stop();
	mSoundYoyo.Stop();
}