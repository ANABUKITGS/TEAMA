#include "CBossGimmick.h"
#include <iostream>

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;

void CBossGimmick::Update(){
	mPosition = CPlayerT::mpPlayer->mPosition;
	if (!mWait && GetRandom(BOX_PROBABILITY)){
		new CMapBox(CVector2(CPlayerT::mpPlayer->mPosition.x, 720.0f), true);
	}
	if (mWait < WAIT_TIME)
		mWait++;
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

	std::cout << ans << std::endl;
	
	if (!ans){
		max = probability;
		return true;
	}
	else
		return false;
}