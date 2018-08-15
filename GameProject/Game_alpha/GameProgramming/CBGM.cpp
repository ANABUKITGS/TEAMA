#include "CBGM.h"

void CBGM::Init(){
	mSoundTitle.Load("");
	mSoundTutorial.Load(".\\Data\\Sound\\BGM0.wav");
	mSoundMain.Load("");
	mSoundBoss.Load("");
	mSoundResult.Load("");
}

void CBGM::Update(){
	switch (CSceneChange::changenum){
	default:
		mSoundTitle.Stop();
		mSoundTutorial.Stop();
		mSoundMain.Stop();
		mSoundBoss.Stop();
		mSoundResult.Stop();
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ETITLE:
		mSoundTutorial.Stop();
		mSoundMain.Stop();
		mSoundBoss.Stop();
		mSoundResult.Stop();

		mSoundTitle.Play();
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EGAME:
		mSoundTitle.Stop();
		mSoundResult.Stop();
		if (musictime >= SOUND_TUTORIAL){
			musictime = 0;
			mSoundTutorial.Play();
		}
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ERANKING:
		break;

	case CSceneChange::ECSCENECHANGE_NUM::ESCORE:
		mSoundTitle.Stop();
		mSoundTutorial.Stop();
		mSoundMain.Stop();
		mSoundBoss.Stop();
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEDITER:
		mSoundTitle.Stop();
		mSoundMain.Stop();
		mSoundBoss.Stop();
		mSoundResult.Stop();

		if (musictime >= SOUND_TUTORIAL){
			musictime = 0;
			mSoundTutorial.Play();
		}
		break;

	case CSceneChange::ECSCENECHANGE_NUM::EEXIT:
		mSoundTitle.Stop();
		mSoundTutorial.Stop();
		mSoundMain.Stop();
		mSoundBoss.Stop();
		mSoundResult.Stop();
		break;
	}
	musictime++;
}