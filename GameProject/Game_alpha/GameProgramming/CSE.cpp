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
CSound CSE::mSoundBossTelepoIn;
CSound CSE::mSoundBossTelepoOut;
CSound CSE::mSoundBossYoyo;
CSound CSE::mSoundBossJump;
CSound CSE::mSoundBossDown;
CSound CSE::mSoundBossGuard;
CSound CSE::mSoundBossDamage;
CSound CSE::mSoundYoyo;
CSound CSE::mSoundCheckPoint;
CSound CSE::mSoundBack;
CSound CSE::mSoundSwitch;
CSound CSE::mSoundBox;
CSound CSE::mSoundSteel;

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
	mSoundYoyo.Load(".\\Data\\Sound\\SE\\Yoyo.wav");
	mSoundCheckPoint.Load(".\\Data\\Sound\\SE\\CheckPoint.wav");
	mSoundBack.Load(".\\Data\\Sound\\SE\\Back.wav");
	mSoundSwitch.Load(".\\Data\\Sound\\SE\\Switch.wav");
	mSoundBox.Load(".\\Data\\Sound\\SE\\Box.wav");
	mSoundSteel.Load(".\\Data\\Sound\\SE\\Steel.wav");

	//ボスSE
	mSoundBossTelepoIn.Load(".\\Data\\Sound\\SE\\BossTelepo.wav");
	mSoundBossTelepoOut.Load(".\\Data\\Sound\\SE\\BossTelepo2.wav");
	mSoundBossYoyo.Load(".\\Data\\Sound\\SE\\BossYoyo.wav");
	mSoundBossJump.Load(".\\Data\\Sound\\SE\\BossJump.wav");
	mSoundBossDown.Load(".\\Data\\Sound\\SE\\BossDownVoice.wav");
	mSoundBossGuard.Load(".\\Data\\Sound\\SE\\BossGuard.wav");
	mSoundBossDamage.Load(".\\Data\\Sound\\SE\\BossDamage.wav");
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
	mSoundYoyo.Stop();
	mSoundCheckPoint.Stop();
	mSoundBack.Stop();
	mSoundSwitch.Stop();
	mSoundBox.Stop();
	mSoundSteel.Stop();

	//ボスSE
	mSoundBossTelepoIn.Stop();
	mSoundBossTelepoOut.Stop();
	mSoundBossYoyo.Stop();
	mSoundBossJump.Stop();
	mSoundBossDown.Stop();
	mSoundBossGuard.Stop();
	mSoundBossDamage.Stop();
}