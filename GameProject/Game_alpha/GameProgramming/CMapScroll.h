#ifndef CMAPSCROLL_H
#define CMAPSCROLL_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMap.h"
#include "CGame2.h"

#define SCROLL_SPEED			0.9f
#define ADD_SCROLL_SPEED		SCROLL_SPEED * 5
#define BOSSROOM_SCROLL_SPEED	0.75f * 10

#define DISPLAY_LEFT mPosition

class CMapScroll : public CRectangle{
public:
	static float add_scroll;
	static bool scroll_flg;
	static bool scroll_stop;
	static bool boss_scroll;
	static bool sign_scroll;
	static CMapScroll *mpScroll;
	CMapScroll()
		: CRectangle(CVector2(0, 0), CVector2(0, 0), NULL)
	{
		scroll_flg = false;
		scroll_stop = false;
		boss_scroll = false;
		sign_scroll = false;
		mRender = false;
		mTag = ECELLNUM::ENONE;
		CTaskManager::Get()->Add(this);
	}
	~CMapScroll(){
		mpScroll = 0;
	}

	void Update();
	void Reset();
};
#endif