#include "CBossGimmick.h"

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;

void CBossGimmick::Update(){
	if (!GetSeed(BOX_PROBABILITY)){
		new CMapBox(CVector2(CPlayerT::mpPlayer->mPosition.x, 720.0f), true);
	}
}

int CBossGimmick::GetSeed(int probability){
	int num = 0;					//�z�� �ԍ�
	static int max = probability;	//�z�� �͈�
	int ans = 0;					//����

	srand((unsigned int)time(NULL) - clock());
	num = rand() % probability - max;
	ans = mBoxProbability[num];


	return ans;
}