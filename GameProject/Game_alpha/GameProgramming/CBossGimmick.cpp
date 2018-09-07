#include "CBossGimmick.h"

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;

void CBossGimmick::Update(){
	if (!GetSeed(BOX_PROBABILITY)){
		new CMapBox(CVector2(CPlayerT::mpPlayer->mPosition.x, 720.0f), true);
	}
}

int CBossGimmick::GetSeed(int probability){
	int num = 0;					//”z—ñ ”Ô†
	static int max = probability;	//”z—ñ ”ÍˆÍ
	int ans = 0;					//Œ‹‰Ê

	srand((unsigned int)time(NULL) - clock());
	num = rand() % probability - max;
	ans = mBoxProbability[num];


	return ans;
}