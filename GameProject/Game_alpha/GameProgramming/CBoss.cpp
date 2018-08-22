#include "CBoss.h"
#include "CGame2.h"
#include "CScene.h"

/*
ボスの移動処理
*/
float CBoss::BossFowrd(float speed){
	float r = speed;
	if (mPosition.x > CPlayerT::mpPlayer->mPosition.x){
		mDirection = false;
		mPosition.x -= r;
	}
	else{
		mDirection = true;
		mPosition.x += r;
	}
	return r;
}

/*
ボスのジャンプ処理
*/
void CBoss::BossJump(){
	static bool Jump = true;
	//引数値が真の時はジャンプする
	if (Jump){
		//BossFowrd(BOSSMOVESPEED);
		mVelocityY = BOSSGVELOCITY;	//重力加算の値を設定
	}
}

void CBoss::Update(){
	if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
		static const short int Back = 5;
		printf("%d\n", mBossDamageCnt);
		//ボスとプレイヤーとのベクトルを出す
		mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
		//一定間隔でジャンプの乱数を出す(とりあえず1秒に一回)
		if (mBossJcnt < BOSSJUMPTIME)
			mBossJcnt++;
		//一定時間経過すると乱数を出す
		else{
			mBossJumprad = rand() / 100 % 7;
			//printf("%d\n", mBossJumprad);
			mBossJcnt = NULL;
		}

		//行動パターン処理
		switch (mAttackBehavior){

		case EIDOL://待機状態
			break;

		case EMANTO://最初のマントの処理
			//ボスのアニメーションが最後まで行くと処理開始
			if (mBossAnimeFream > 4)
				mAttackBehavior = EDASH;
			break;//ループ終了

		case EDASH:				//ボスの走る処理
			BossFowrd(BOSSMOVESPEED);//ボスの移動速度を指定

			//乱数値が真(1)の時だけボスがジャンプをする
			if (mBossJumprad == 1){
				mAttackBehavior = EJUMP;//ボスの行動をジャンプにする
				mBossJumprad = NULL;//ボスの乱数値を一度0にして連続ジャンプを防ぐ
			}

			//プレイヤーとの距離が一定範囲内に入れば、攻撃を出す
			/*if (abs(mAttack_Search.x) < mBossBehavior)
				mAttackBehavior = EBWEAPON;*/
			break;//ループ終了

		case EJUMP:	//ボスのジャンプ処理
			BossJump();//ボスをジャンプさせる
			if (!mBossJumprad)
				mAttackBehavior = EDASH;
			break;

		case EBWEAPON:		//ボスの攻撃処理
			if (!mpBWeapon){
				if (mBossAttackItr < 0){
					mBossAttackItr = ATTACK_INTERVAL;
					//ボスのヨーヨーを呼び出す
					mpBWeapon = new CWeapon(EEWEAPON, mPosition, mDirection);

					if (mDirection)		//敵が右を向いている時には右にヨーヨーを進ませる
						mpBWeapon->mPosition.x += 10;

					else				//敵が左を向いている時には左にヨーヨーを進ませる
						mpBWeapon->mPosition.x -= 10;
				}
			}
			//敵のヨーヨーが発射された時の処理を行う
			else {
				if (mpBWeapon->mLife < 0){
					mpBWeapon = 0;
					mAttackBehavior = EDASH;
				}
			}
			break;//ループ終了

		case EDAMAGE://攻撃を受けた時
			if (CPlayerT::mpPlayer->mPosition.x<mPosition.x)
				mPosition.x += Back;
			else
				mPosition.x-=Back;
			if (mBossAnimeFream > 1)
				mAttackBehavior = EDASH;
			//一定以上のダメージを受けると消滅のアニメーションへ移行
			if (mBossDamageCnt == 3)
				mAttackBehavior = EDOWN;
			break;//ループ終了

		case EDOWN://プレイヤーに負けた時
			//最後までアニメーションが進んだ時に処理開始
			if (mBossAnimeFream > 4){
				//消滅までのカウントダウン開始
				if (mBossDeleteTime){
					//0になるまで減算する
					mBossDeleteTime--;
					//消滅まで点滅？を繰り返す
					if (BOSS_DELCNT%mBossDeleteTime == 0)
						mAlpha = 0.0f;
					else
						mAlpha = 1.0f;
				}
				//0になったら消滅させる
				else
					mEnabled = false;
			}
			break;

		default:	//通常では距離の遠近で判定する
			//プレイヤーが一定範囲内に入ればマントのアニメーションを行う
			if (STARTBEHAVIOR > abs(mAttack_Search.x))
				mAttackBehavior = EMANTO;
			////プレイヤーとの距離が一定の距離外であればプレイヤーに近づく
			//if (abs(mAttack_Search.x) > mBossBehavior)
			//	mAttackBehavior = EDASH;
			break;
		}
		//ダメージを受けた時に行う処理
			if (Invincible){
				mBossInvincibleTime--;
				//無敵時間を追加
				if (mBossInvincibleTime % 10 == 0)
					mAlpha = 0.0f;
				else
					mAlpha = 1.0f;
				if (!mBossInvincibleTime){
					mBossInvincibleTime = BOSSINVINCIBLE;
					mAlpha = 1.0f;
					Invincible = false;
				}
			}
		//重力処理
		Gravity();
	}
	//基底クラスの更新処理
	CRectangle::Update();
}

bool CBoss::Collision(CRectangle*p){
	//return false;
	if (p->GetEnabled()){
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case EUNDER:
				if ((mPosition.y > p->mPosition.y) && mVelocityY < 0){
					mVelocityY = 0.0f;
					mPosition = mPosition + aj;
				}
				break;
			case EPWEAPON://プレイヤーのヨーヨーと衝突した時
				//無敵時間のフラグをONにする
				Invincible = true;
				mVelocityY = 0.0f;
				//ダメージを加算する
				mBossDamageCnt++;
				//攻撃を受けた時のアニメーションをする
				mAttackBehavior = EDAMAGE;
				break;
			case ESWITCH_GROUND1:
			case ESWITCH_GROUND2:
			case ENONE:
			case ECHIKUWA:
			case EBELTL:
			case EBELTR:
			case ESIGN:
			case EEWEAPON:
			case ESEARCH:
			case ESWITCH:
			case EPLAYER:
				break;

			default:
				CVector2 ad;
				if (aj.x > 0) {
					//右空き
					if (!(p->mColFlg & EDT_RIGHT)) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				else if (aj.x < 0) {
					//左空き
					if (!(p->mColFlg & EDT_LEFT)) {
						mPosition.x = mPosition.x + aj.x;
					}
				}
				if (CRectangle::Collision(p, &aj, &ad)) {
					if (ad.y < 0) {
						//下空き
						if (!(p->mColFlg & EDT_BOTTOM)) {
							mPosition.y = mPosition.y + ad.y;
							mVelocityY = 0.0f;
						}
					}
					else if (ad.y > 0) {
						//上空き
						if (!(p->mColFlg & EDT_TOP)) {
							mPosition.y = mPosition.y + ad.y;
							mVelocityY = 0.0f;
						}
					}
				}
				break;
			}
			return true;
		}
	}
	return false;
}

void CBoss::Render(){
	switch (mAttackBehavior){

	case EIDOL://待機状態
		break;

	case EMANTO://マントアニメーション
		//テクスチャの枚数-1よりも値が大きくなれば
		if (mBossAnimeFream > 4)
			//ループの先頭に戻る
			mBossAnimeFream = 0;
		//次のコマに行くタイミング
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//左向き
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//右向き
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 512, 256, mAlpha);
		break;

	case EDASH://走り動作
		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;

		Boss_Ani_Count_Frame = 5;

		if (!mDirection)//左向き
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE*2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 256, 0, mAlpha);

		else//右向き
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2,mPosition.y - CELLSIZE*2, 
			mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 256, 0, mAlpha);
		break;

	case EJUMP://ジャンプ動作
		//ジャンプ上昇中の時の処理
		if (mVelocityY > 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame= 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2,mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1536, 1280, mAlpha);
			else				//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE*2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
		}
		//ジャンプ下向中
		else if (mVelocityY < 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
			else				//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
		}
		//ジャンプ最高地点
		else if (mVelocityY >= BOSSGVELOCITY){
			//アニメーションの枚数-1を指定し、その枚数を超えたら
			if (mBossAnimeFream > 4)
				mBossAnimeFream = 0;//ループ開始位置(1枚目のアニメーション)に戻る

			//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
			Boss_Ani_Count_Frame = 4;

			if (!mDirection)//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 768, 512, mAlpha);

			else			//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 768, 512, mAlpha);
		}
		//着地地点
		else if (mVelocityY == 0.0f){
			//アニメーションの枚数-1を指定し、その枚数を超えたら
			if (mBossAnimeFream > 3)
				mBossAnimeFream = 0;//ループ開始位置(1枚目のアニメーション)に戻る

			//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
			Boss_Ani_Count_Frame = 10;

			if (!mDirection)//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2506, 2250, mAlpha);

			else			//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2506, 2250, mAlpha);
		}
		break;

	case EBWEAPON://攻撃
		if (mBossAnimeFream > 5)
			mBossAnimeFream = 0;

		Boss_Ani_Count = 20;

		//左向き
		if (!mDirection)
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2250, 1994, mAlpha);
		//右向き
		else
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2250, 1994, mAlpha);
		break;

	case EDAMAGE://攻撃を受けた時
		if (mBossAnimeFream > 1)
			mBossAnimeFream = 0;

		Boss_Ani_Count = 14;

		if (!mDirection)	//左向き
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);
		else				//右向き
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1280, 1024, mAlpha);

		break;

	case EDOWN://ダウンした時（プレイヤーに負けた時）
		//指定テクスチャの枚数を超えたら
		if (mBossAnimeFream > 4)
			//最後の画像で固定する
			mBossAnimeFream = 4;

		//アニメーションの速さを指定
		Boss_Ani_Count = 10;

		//左向き
		if (!mDirection)
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1024, 768, mAlpha);
		//右向き
		else
			mTexture.DrawImage(mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - CELLSIZE * 2,
			mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1024, 768, mAlpha);
		break;
	}
	//次のコマに行く為に加算する
	Boss_Ani_Count++;
	//一コマのフレーム数よりも大きくなれば
	if (Boss_Ani_Count > Boss_Ani_Count_Frame){
		//次のコマに行く
		mBossAnimeFream++;
		//カウントをリセットする
		Boss_Ani_Count = 0;
	}
}