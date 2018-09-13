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
	static CSound mSoundBossTelepoIn;//消える動作の効果音
	static CSound mSoundBossTelepoOut;//消える動作解除の効果音
	static CSound mSoundBossYoyo;//ヨーヨーで攻撃する時の効果音
	static CSound mSoundBossJump;//ジャンプの効果音
	static CSound mSoundBossDown;//ボスがダウンした時
	static CSound mSoundBossGuard;//ガードした時
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