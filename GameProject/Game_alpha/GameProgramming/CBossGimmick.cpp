#include "CBossGimmick.h"

CBossGimmick *CBossGimmick::mpBossGimmick = NULL;

void CBossGimmick::Update(){
	GetSeed(10);
}

int CBossGimmick::GetSeed(int num){
	srand((unsigned int)time(NULL) - clock());
	return rand() % num;
}