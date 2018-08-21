#include "CMapBox.h"
#include "CScene.h"

void CMapBox::Update() {
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		if (mBreak)
		Gravity();
		if (mPosition.y < -100)
			mEnabled = false;
	}
	CMapChip::Update();
}

/*
プレイヤーに当たったら無効にする
*/
bool CMapBox::Collision(CRectangle *r) {
	//プレイヤーまたは武器に衝突
	CVector2 aj;
	if (CRectangle::Collision(r, &aj)) {
		//設置状態
		if (!mBreak){
			//当たった他人を押し返す当たり判定
			if (r->mTag == EPLAYER ||
				r->mTag == EENEMY1 ||
				r->mTag == EENEMY2 ||
				r->mTag == EENEMY3 ||
				r->mTag == EBOSS) {
				r->mPosition = r->mPosition - aj;
				return true;
			}
			//自身を押し返す当たり判定
			else{
				if (r->mTag != EPWEAPON &&
					r->mTag != EEWEAPON){
					mVelocityY = 0.0f;
					mPosition = mPosition + aj;
					return true;
				}
			}
		}
		//落下状態
		else if (mBreak &&
			r->mTag == EPLAYER ||
			r->mTag == EENEMY1 ||
			r->mTag == EENEMY2 ||
			r->mTag == EENEMY3 ||
			r->mTag == EBOSS) {

			return true;
		}

		//プレイヤーのヨーヨー
		if (r->mTag == EPWEAPON) {
			mBreak = true;
			return true;
		}
	}
	return false;
}

void CMapBox::Render(){
	mTexBox.DrawImage(BOX_UV, 1.0f);
}

void CMapBox::Gravity(){
	//速度を加速
	mVelocityY -= 16.33 / 15;
	//速度分移動
	mPosition.y += mVelocityY;
}