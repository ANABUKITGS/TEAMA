#include "CMapSteel.h"
#include "CScene.h"

void CMapSteel::Update() {
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
bool CMapSteel::Collision(CRectangle *r) {
	//点ポリゴンは判定しない
	if (r->mScale.x > 0.0f && r->mScale.y > 0.0f){
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
					//左
					if (mPosition.x - CELLSIZE / 2 > r->mPosition.x) {
						r->mPosition.x = r->mPosition.x - aj.x;
						r->mVelocityX = 0.0f;
					}
					//右
					if (mPosition.x + CELLSIZE / 2 < r->mPosition.x) {
						r->mPosition.x = r->mPosition.x - aj.x;
						r->mVelocityX = 0.0f;
					}
					//下
					if (mPosition.y > r->mPosition.y) {
						r->mPosition.y = r->mPosition.y - aj.y;
						r->mVelocityY = 0.0f;
					}
					//上
					if (mPosition.y < r->mPosition.y) {
						r->mPosition.y = r->mPosition.y - aj.y;
						r->mVelocityY = 0.0f;
					}
				}
				//自身を押し返す当たり判定
				else{
					if (r->mTag != EPWEAPON &&
						r->mTag != EEWEAPON){
						mVelocityY = 0.0f;
						mPosition = mPosition + aj;
					}
				}
			}

			//プレイヤーのヨーヨー
			if (r->mTag == EPWEAPON)
				mBreak = true;

			return true;
		}
	}
	return false;
}

void CMapSteel::Render(){
	mTexSteel.DrawImage(STEEL_UV, 1.0f);
}

void CMapSteel::Gravity(){
	//速度を加速
	mVelocityY -= 16.33 / 15;
	//速度分移動
	mPosition.y += mVelocityY;
}