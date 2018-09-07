#include "CBossGimmick.h"
#include <iostream>

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;

void CBossGimmick::Update(){
	mPosition = CPlayerT::mpPlayer->mPosition;
	if (!mWait && GetRandom(BOX_PROBABILITY) && CBoss::mpBoss->mBossLife > 0){
		new CMapBox(CVector2(CPlayerT::mpPlayer->mPosition.x, 720.0f), true);
		mGimmickFlg = true;
		mWait = 1;
		return;
	}
	if (mWait < WAIT_TIME){
		mWait++;
		mGimmickFlg = false;
	}
	else
		mWait = 0;

	if (CPlayerT::mpPlayer->mJewel <= 0)
		mEnabled = false;
}

bool CBossGimmick::GetRandom(int probability){
	int num = 0;					//�z�� �ԍ�
	static int max = probability;	//�z�� �͈�
	int ans = 0;					//����
	int temp = 0;					//�l �ꎞ�ۊ�

	if (max <= 0)
		max = probability;

	srand((unsigned int)time(NULL) - clock());
	num = rand() % max;
	ans = mBoxProbability[num];

	//�o���l�ƍŌ�̒l�̓���ւ�
	max -= 1;
	mBoxProbability[num] = mBoxProbability[max];
	mBoxProbability[max] = ans;

#ifdef _DEBUG
	std::cout << ans << std::endl;
#endif
	
	if (!ans){
		max = probability;
		return true;
	}
	else
		return false;
}