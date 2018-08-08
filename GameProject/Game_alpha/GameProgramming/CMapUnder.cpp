#include "CMapUnder.h"
#include "CPlayerT.h"

void CMapUnder::Update(){
	//親の更新処理を呼ぶ
	CMapChip::Update();
}

bool CMapUnder::Collision(CRectangle*r){
	// 当たっているか
	if (CRectangle::Collision(r)) {
		//プレイヤーに衝突
		if (r->mTag == EPLAYER) {
			//プレイヤーがジャンプ中の時は判定しない
			if ((-r->mScale.y/2)>mScale.y){
				return true;
			}
			return true;
		}
	}
	return false;
}