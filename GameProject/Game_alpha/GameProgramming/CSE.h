#ifndef CSE_H
#define CSE_H
#include <time.h>
#include "CSound.h"

#define SOUND_TURN 178

class CSE{
public:
	static CSound mSoundText;

	static CSound mSoundJewelry;
	static CSound mSoundChikuwa;
	static CSound mSoundJump;
	static CSound mSoundDamage;
	static CSound mSoundScore;
	static CSound mSoundSelect;
	static CSound mSoundTurn;
	static CSound mSoundContinue;
	static CSound mSoundBossTelepoIn;//�����铮��̌��ʉ�
	static CSound mSoundBossTelepoOut;//�����铮������̌��ʉ�
	static CSound mSoundBossYoyo;//���[���[�ōU�����鎞�̌��ʉ�
	static CSound mSoundBossJump;//�W�����v�̌��ʉ�
	static CSound mSoundBossDown;//�{�X���_�E��������
	static CSound mSoundBossGuard;//�K�[�h������
	static CSound mSoundBossDamage;
	static CSound mSoundYoyo;
	static CSound mSoundCheckPoint;
	static CSound mSoundBack;
	static CSound mSoundSwitch;
	static CSound mSoundBox;
	static CSound mSoundSteel;

	static void Init();
	static void AllStop();
};
#endif