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

	static void Init();
	static void AllStop();
};
#endif