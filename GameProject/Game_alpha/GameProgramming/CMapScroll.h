#ifndef CMAPSCROLL_H
#define CMAPSCROLL_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMap.h"
#include "CGame2.h"

#define SCROLL_SPEED 0.75f

#define DISPLAY_LEFT mPosition

class CMapScroll : public CRectangle{
public:
	static float add_scroll;
	static bool scroll_flg;
	static bool scroll_stop;
	static CMapScroll *mpScroll;
	CMapScroll()
		: CRectangle(CVector2(0, 0), CVector2(0, 0), NULL)
	{
		scroll_flg = false;
		scroll_stop = false;
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