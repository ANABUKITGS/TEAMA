#include "CBGM.h"

CSound CBGM::mSoundTitle;		//�^�C�g���p
CSound CBGM::mSoundTutorial;	//�`���[�g���A���p
CSound CBGM::mSoundMain;		//�{�җp
CSound CBGM::mSoundBoss;		//�{�X�p
CSound CBGM::mSoundResult;		//���U���g�p
CSound CBGM::mSoundRanking;		//�����L���O�p
CSound CBGM::mSoundEditer;		//�G�f�B�^�[�p
CSound CBGM::mSoundCredit;		//�N���W�b�g�p

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