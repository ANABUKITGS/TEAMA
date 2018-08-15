#ifndef CMAPCHIKUWA_H
#define CMAPCHIKUWA_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#include "CSound.h"
#define CHIKUWA_UV				0, CELLSIZE, CELLSIZE , 0
#define CHIKUWA_FALLING_TIME	60
#define CHIKUWA_LOST_TIME		CHIKUWA_FALLING_TIME * 10
#define FALLING_SPEED			0.02f

class CMapChikuwa : public CMapChip {
private:
	int lostcount;
	bool collision_flg;
	float mFalling;
	CVector2 setpos;
	CTexture mTexChikuwa;
	CSound mSoundChikuwa;

public:
	CMapChikuwa(const CVector2& pos, const CVector2& scale)
		//CMapChipで初期化
		: CMapChip(pos, scale, &mTexChikuwa, CHIKUWA_UV, ECELLNUM::ECHIKUWA)
	{
		lostcount = 0;
		mFalling = 0.0f;
		collision_flg = false;
		setpos.x = mPosition.x;
		setpos.y = mPosition.y;
		mTexChikuwa.Load(".\\Data\\Images\\Map\\MapChikuwa.tga");
		mSoundChikuwa.Load(".\\Data\\Sound\\hoge03.wav");
	}
	void Update();
	bool Collision(CRectangle *r);	//衝突時の処理
	void Render();
};
#endif