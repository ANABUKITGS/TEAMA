#ifndef CSE_H
#define CSE_H
#include "CSound.h"

class CSE{
public:
	static CSound mSoundText;

	static CSound mSoundJewelry;
	static CSound mSoundChikuwa;
	static CSound mSoundJump;
	static CSound mSoundDamage;
	static CSound mSoundScore;
	static CSound mSoundSelect;

	static void Init();
	static void AllStop();
};
#endif