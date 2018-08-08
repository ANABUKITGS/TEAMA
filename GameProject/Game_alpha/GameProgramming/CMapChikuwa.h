#ifndef CMAPCHIKUWA_H
#define CMAPCHIKUWA_H
#include "CMapChip.h"
#include "CMap.h"
#include "CPlayerT.h"
#define SIGN_UV 0, 64, 64 * 6, 64 * 5
#define CHIKUWA_LOSTTIME 240

class CMapChikuwa : public CMapChip {
private:
	int lostcount;
	bool collision_flg;

public:
	CTexture mTexChikuwa;
	CMapChikuwa(const CVector2& pos, const CVector2& scale)
		//CMapChip‚Å‰Šú‰»
		: CMapChip(pos, scale, NULL, SIGN_UV, ECELLNUM::ECHIKUWA)
	{
		lostcount = 0;
		collision_flg = false;
		mTexChikuwa.Load(".\\Data\\Images\\Map\\MapChikuwa.tga");
	}
	void Update();
	bool Collision(CRectangle *r);	//Õ“Ë‚Ìˆ—
	void Render();
};
#endif