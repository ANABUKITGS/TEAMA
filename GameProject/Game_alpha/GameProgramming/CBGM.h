#ifndef CBGM_H
#define CBGM_H
#include <time.h>
#include "CSound.h"

class CBGM {
public:
	static CSound mSoundTitle;		//�^�C�g���p
	static CSound mSoundTutorial;	//�`���[�g���A���p
	static CSound mSoundMain;		//�{�җp
	static CSound mSoundBoss;		//�{�X�p
	static CSound mSoundResult;		//���U���g�p
	static CSound mSoundRanking;	//�����L���O�p
	static CSound mSoundEditer;		//�G�f�B�^�[�p
	static CSound mSoundCredit;		//�N���W�b�g�p
	static CSound mSoundGameOver;	//�Q�[���I�[�o�[�p

	void Init();
	void Update();
	static void AllStop();
};

#endif