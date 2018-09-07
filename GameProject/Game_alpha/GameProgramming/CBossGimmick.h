#ifndef CBOSSGIMMICK_H
#define CBOSSGIMMICK_H
#include <random>
#include "CRectangle.h"
#include "CPlayerT.h"
#include "CBoss.h"
#include "CMapBox.h"
#include "CMapSign.h"

#define WAIT_TIME		3000	//次の落下までのクールタイム
#define BOX_PROBABILITY	100	//コンテナを落とす確率

class CBossGimmick : public CRectangle{
private:
	int mWait;								//クールタイム 計測
	int mBoxProbability[BOX_PROBABILITY];	//確率

public:
	static CBossGimmick *mpBossGimmick;

	CBossGimmick()
		:CRectangle(CMapBossRoomSign::mpBossRoomSign->mPosition, CVector2(0.0f, 0.0f), NULL)
		, mWait(0)
	{
		for (int i = 0; i < BOX_PROBABILITY; i++)
			mBoxProbability[i] = i;

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