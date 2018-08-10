#include "CBoss.h"

void CBoss::Update(){
	//ボスとプレイヤーとのベクトルを出す
	mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;

	//行動パターン処理
	switch (mAttackBehavior){
	case EDASH:				//ボスの走る処理
		if (mPosition.x<=mBossBehavior)
		mPosition.x -= 3;	//ボスの移動速度を指定
		break;

	case EBWEAPON:																//ボスの攻撃処理
		mpBWeapon = new CWeapon(EEWEAPON,mPosition,CVector2(10,10),true,NULL);	//武器を呼び出す
		//ボスのヨーヨーが発射されている場合
		if (mpBWeapon){
			//ヨーヨーが自分の位置と同じ位置に戻ってきたら削除する
			if (mpBWeapon->mPosition.x == mPosition.x){
				mpBWeapon = false;
			}
		}
		break;

	default:						//通常では距離の遠近で判定する
		if (mAttack_Search.x > mBossBehavior)
			mAttackBehavior = EDASH;
		else

		break;
	}
	Gravity();
	//基底クラスの更新処理
	CRectangle::Update();
}

void CBoss::Render(){
	//基底クラスの描画処理
	CRectangle::Render();
}

bool CBoss::Collision(CRectangle*r){
	if (r->GetEnabled()){
		//めり込んだ分戻す値をインスタンスで
		CVector2 ajust;
		//プレイヤー以外と衝突した時には戻す
		if (r->mTag != EPLAYER){
			if (CRectangle::Collision(r)){
				mPosition.x = mPosition.x + ajust.x;
				mPosition.y = mPosition.y + ajust.y;
			}
			return true;
		}
	}
	return false;
}