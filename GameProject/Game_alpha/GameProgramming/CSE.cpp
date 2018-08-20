#include "CSE.h"

CSound CSE::mSoundText;
CSound CSE::mSoundJewelry;
CSound CSE::mSoundChikuwa;

void CSE::Init(){
	mSoundText.Load(".\\Data\\Sound\\SE\\Text.wav");
	mSoundJewelry.Load(".\\Data\\Sound\\SE\\Jewelry.wav");
	mSoundChikuwa.Load(".\\Data\\Sound\\SE\\Chikuwa.wav");
}