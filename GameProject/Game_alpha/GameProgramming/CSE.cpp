#include "CSE.h"

CSound CSE::mSoundText;
CSound CSE::mSoundJewelry;
CSound CSE::mSoundChikuwa;

void CSE::Init(){
	mSoundText.Load(".\\Data\\Sound\\Text.wav");
	mSoundJewelry.Load(".\\Data\\Sound\\Jewelry.wav");
	mSoundChikuwa.Load(".\\Data\\Sound\\Chikuwa.wav");
}