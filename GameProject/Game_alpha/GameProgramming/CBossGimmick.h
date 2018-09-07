#ifndef CBOSSGIMMICK_H
#define CBOSSGIMMICK_H
#include <random>
#include "CRectangle.h"
#include "CPlayerT.h"
#include "CBoss.h"
#include "CMapBox.h"
#include "CMapSign.h"

class CBossGimmick : public CRectangle{
private:

public:
	static CBossGimmick *mpBossGimmick;

	CBossGimmick(){
		mPosition = CMapBossRoomSign::mpBossRoomSign->mPosition;
		mScale = CVector2(0.0f, 0.0f);
		mTag = ECELLNUM::ENONE;
		CTaskManager::Get()->Add(this);
	}
	~CBossGimmick(){
		mpBossGimmick = NULL;
	}
	void Update();
	int GetSeed(int);
};
#endif