#ifndef CBGM_H
#define CBGM_H
#include <time.h>
#include "CSound.h"

#define SOUND_TITLE		1135	//�^�C�g�� BGM (�~���b)
#define SOUND_TUTORIAL	2670	//�`���[�g���A�� BGM (�~���b)
#define SOUND_MAIN				//�{�� BGM (�~���b)
#define SOUND_BOSS		0		//�{�X BGM (�~���b)
#define SOUND_RESULT	0		//���U���g BGM (�~���b)
#define SOUND_RANKING	0		//�����L���O BGM (�~���b)

class CBGM {
private:
	static int starttime;	//BGM�̊J�n����
	static int musicnum;	//BGM�ԍ�

	static CSound mSoundTitle;		//�^�C�g���p
	static CSound mSoundTutorial;	//�`���[�g���A���p
	static CSound mSoundMain;		//�{�җp
	static CSound mSoundBoss;		//�{�X�p
	static CSound mSoundResult;		//���U���g�p
	static CSound mSoundRanking;	//�����L���O�p

public:
	enum EMUSIC_NUM{
		ETITLE = 1,
		ETUTORIAL,
		EMAIN,
		EBOSS,
		ERESULT,
		ERANKING,
		ESIZE
	};

	void Init();
	void Update();
	static void AllStop();

	static void ChangeMusic(EMUSIC_NUM);
};

#endif