#ifndef CMAPSCROLL_H
#define CMAPSCROLL_H
#include "CRectangle.h"
#include "CTaskManager.h"
#include "CMap.h"
#include "CGame2.h"

class CMapScroll : public CRectangle{
public:
	static CMapScroll *mScroll;
	CMapScroll()
		: CRectangle(CVector2(0, 0), CVector2(0, 0), NULL)
	{
		mRender = false;
		CTaskManager::Get()->Add(this);
	}

	void Update();
	void Reset();
};
#endif