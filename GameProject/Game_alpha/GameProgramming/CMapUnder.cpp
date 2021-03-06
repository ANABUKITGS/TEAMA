#include "CMapUnder.h"
#include "CPlayerT.h"

void CMapUnder::Update(){
	//親の更新処理を呼ぶ
	CMapChip::Update();
}

void CMapUnder::Render(){
	mTexUnder.DrawImage(UNDER_UV, 1.0f);
}

bool CMapUnder::Collision(CRectangle*r){
	CVector2 aj;
	// 当たっているか
	if (r->mTag == ECELLNUM::EPLAYER ||
		r->mTag == ECELLNUM::EENEMY1 ||
		r->mTag == ECELLNUM::EENEMY2 ||
		r->mTag == ECELLNUM::EENEMY3){
		if (CRectangle::Collision(r) && CRectangle::Collision(r, &aj)) {
			if (mPosition.y < r->mPosition.y - r->mScale.y) {
				if (r->mTag == ECELLNUM::EPLAYER){
					//プレイヤーが上昇中の時は判定しない
					if (CPlayerT::mpPlayer->mVelocityY > 0.0f)
						return false;
					CPlayerT::mpPlayer->mJumpCount = 0;
				}
				r->mPosition.y = r->mPosition.y - aj.y;
				r->mVelocityY = 0.0f;
				return false;
			}
			return true;
		}
	}
	return false;
}