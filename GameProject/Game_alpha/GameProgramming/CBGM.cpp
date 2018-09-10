#include "CBGM.h"

int CBGM::starttime;			//BGM�̊J�n����
int CBGM::musicnum;				//BGM�ԍ�

CSound CBGM::mSoundTitle;		//�^�C�g���p
CSound CBGM::mSoundTutorial;	//�`���[�g���A���p
CSound CBGM::mSoundMain;		//�{�җp
CSound CBGM::mSoundBoss;		//�{�X�p
CSound CBGM::mSoundResult;		//���U���g�p
CSound CBGM::mSoundRanking;		//�����L���O�p

void CBGM::Init(){
	starttime = clock();
	mSoundTitle.Load(".\\Data\\Sound\\BGM\\Title.wav");
	mSoundTutorial.Load(".\\Data\\Sound\\BGM\\Tutorial.wav");
	mSoundMain.Load(".\\Data\\Sound\\BGM\\Main.wav");
	mSoundBoss.Load("");
	mSoundResult.Load("");
	mSoundRanking.Load("");
	CBGM::ChangeMusic(CBGM::EMUSIC_NUM::ETITLE);
}

void CBGM::Update(){
	switch (musicnum){
	case EMUSIC_NUM::ETITLE:
		if (clock() >= SOUND_TITLE + starttime){
			ChangeMusic(EMUSIC_NUM::ETITLE);
			mSoundTitle.Play();
		}
		break;

	case EMUSIC_NUM::ETUTORIAL:
		if (clock() >= SOUND_TUTORIAL + starttime){
			ChangeMusic(EMUSIC_NUM::ETUTORIAL);
			mSoundTutorial.Play();
		}
		break;

	case EMUSIC_NUM::EMAIN:
		if (clock() >= SOUND_MAIN + starttime){
			ChangeMusic(EMUSIC_NUM::EMAIN);
			mSoundMain.Play();
		}
		break;

	case EMUSIC_NUM::EBOSS:
		if (clock() >= SOUND_BOSS + starttime){
			ChangeMusic(EMUSIC_NUM::EBOSS);
			mSoundBoss.Play();
		}
		break;

	case EMUSIC_NUM::ERESULT:
		if (clock() >= SOUND_RESULT + starttime){
			ChangeMusic(EMUSIC_NUM::ERESULT);
			mSoundResult.Play();
		}
		break;

	case EMUSIC_NUM::ERANKING:
		if (clock() >= SOUND_MAIN + starttime){
			ChangeMusic(EMUSIC_NUM::ERANKING);
			mSoundRanking.Play();
		}
		break;

	default:
		AllStop();
		break;
	}
}

void CBGM::ChangeMusic(EMUSIC_NUM num){
	starttime = clock();
	AllStop();

	if (num >= EMUSIC_NUM::ETITLE && num < EMUSIC_NUM::ESIZE){
		musicnum = num;
		switch (musicnum){
		case EMUSIC_NUM::ETITLE:
			mSoundTitle.Play();
			break;

		case EMUSIC_NUM::ETUTORIAL:
			mSoundTutorial.Play();
			break;

		case EMUSIC_NUM::EMAIN:
			mSoundMain.Play();
			break;

		case EMUSIC_NUM::EBOSS:
			mSoundBoss.Play();
			break;

		case EMUSIC_NUM::ERESULT:
			mSoundResult.Play();
			break;

		case EMUSIC_NUM::ERANKING:
			mSoundRanking.Play();
			break;

		default:
			AllStop();
			break;
		}
	}
	else
		musicnum = NULL;
}

void CBGM::AllStop(){
	mSoundTitle.Stop();
	mSoundTutorial.Stop();
	mSoundMain.Stop();
	mSoundBoss.Stop();
	mSoundResult.Stop();
	mSoundRanking.Stop();
}