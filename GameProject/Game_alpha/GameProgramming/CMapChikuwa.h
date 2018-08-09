#ifndef CMAPCHIKUWA_H
#define CMAPCHIKUWA_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#define SIGN_UV					0, 64, 64 * 6, 64 * 5
#define CHIKUWA_FALLING_TIME	60
#define CHIKUWA_LOST_TIME		CHIKUWA_FALLING_TIME * 10
#define FALLING_SPEED			0.02f

class CMapChikuwa : public CMapChip {
private:
	int lostcount;
	bool collision_flg;
	float mFalling;
	CVector2 setpos;

public:
	CTexture mTexChikuwa;
	CMapChikuwa(const CVector2& pos, const CVector2& scale)
		//CMapChip�ŏ�����
		: CMapChip(pos, scale, NULL, SIGN_UV, ECELLNUM::ECHIKUWA)
	{
		lostcount = 0;
		mFalling = 0.0f;
		collision_flg = false;
		setpos.x = mPosition.x;
		setpos.y = mPosition.y;
		mTexChikuwa.Load(".\\Data\\Images\\Map\\MapChikuwa.tga");
	}
	void Update();
	bool Collision(CRectangle *r);	//�Փˎ��̏���
	void Render();
};
#endif