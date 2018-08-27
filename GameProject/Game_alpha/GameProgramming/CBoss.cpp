#include "CBoss.h"
#include "CGame2.h"
#include "CScore.h"
#include "CScene.h"
#include "CFade.h"
#include "CTime.h"
#include "CMapSign.h"

CBoss *CBoss::mpBoss = 0;

void CBoss::Update(){
	if (CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg && mBossBattle){
		if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
			static int IdolInterval = 0;//待機状態から次の行動に移るまでの時間
			//ボスとプレイヤーとのベクトルを出す
			mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
			//一定間隔でジャンプの乱数を出す(とりあえず1秒に一回)
			if (mBossJcnt < BOSSJUMPTIME)
				mBossJcnt++;
			//一定時間経過すると乱数を出す
			else{
				mBossJumprad = rand() / 100 % 7;
				mBossJcnt = NULL;
			}
			//ジャンプの処理ここまで

			//待機状態からランダムで行動をとる(移動、ジャンプ、攻撃のどれか)
			mBossIBehavior = rand() / 1000 % 6;

			//行動パターン処理
			switch (mAttackBehavior){


				//待機状態
			case EIDOL:
				if (mPosition.x > CPlayerT::mpPlayer->mPosition.x)
					mDirection = false;
				else
					mDirection = true;

				if (mAttackBehavior != EMANTO){
					//次の行動までの時間を加算する
					if (IdolInterval != BOSSNEXTBEHAVIOR)
						IdolInterval++;
					//指定した秒数を超えれば行動をランダムでとる
					else{
						switch (mBossIBehavior){
						case 0: case 1: case 2://0,1,2は移動
							IdolInterval = NULL;
							mAttackBehavior = EDASH;
							break;
						case 3://1はジャンプ
							if (mBossLife <= mBossMaxLife * 0.5){
								CEnemy::mpEnemy = new CEnemy(mPosition, EENEMY1);
							}
							IdolInterval = NULL;
							mVelocityY = BOSSGVELOCITY;
							if (!mDirection)
								mVelocityX = -BOSSMOVESPEED * 3;
							else
								mVelocityX = BOSSMOVESPEED * 3;
							mAttackBehavior = EJUMP;
							break;

						default:
							IdolInterval = 50;
							break;
						}
					}
				}
				mpBWeapon = 0;
				break;
				//待機状態処理終了


				//最初のマントの処理
			case EMANTO:
				//ボスのアニメーションが最後まで行くと処理開始
				if (mBossAnimeFream > 4){
					mAttackBehavior = EIDOL;
				}
				mpBWeapon = 0;
				break;//ループ終了


				//ボスの走る処理
			case EDASH:

				if (!mDirection)
					mVelocityX = -BOSSMOVESPEED;
				else
					mVelocityX = BOSSMOVESPEED;

				//乱数値が真(1)の時だけボスがジャンプをする
				if (mBossJumprad == 1){
					mVelocityY = BOSSGVELOCITY;
					if (!mDirection)
						mVelocityX = -BOSSMOVESPEED * 3;
					else
						mVelocityX = BOSSMOVESPEED * 3;
					mAttackBehavior = EJUMP;//ボスの行動をジャンプにする
				}
				else{
					//プレイヤーとの距離が一定範囲内に入れば、攻撃を出す
					if (abs(mAttack_Search.x) < mBossBehavior){
						mBossAttackItr = 0;
						mAttackBehavior = EBWEAPON;
						mVelocityX = 0;
					}
				}
				break;//ループ終了
				//走る処理終了


				//ボスのジャンプ処理
			case EJUMP:
				break;
				//ジャンプ処理終了

				//ボスの攻撃処理
			case EBWEAPON:
				//ボスがヨーヨーを出してない時
				if (!mpBWeapon){
					//ボスの攻撃間隔が無くなった時
					if (mBossAttackItr <= 0){
						//攻撃間隔を戻す
						mBossAttackItr = ATTACK_INTERVAL;
						//ボスのヨーヨーを呼び出す
						if (mDirection)
							mpBWeapon = new CWeapon(ECELLNUM::EBWEAPON, mPosition + CVector2(82.0f, 32.0f), mDirection);

						else
							mpBWeapon = new CWeapon(ECELLNUM::EBWEAPON, mPosition + CVector2(-82.0f, 32.0f), mDirection);

						mpBWeapon->mScale = CVector2(20, 20);

						if (mDirection)		//敵が右を向いている時には右にヨーヨーを進ませる
							mpBWeapon->mPosition.x += 10;

						else				//敵が左を向いている時には左にヨーヨーを進ませる
							mpBWeapon->mPosition.x -= 10;
					}
					//ボスの攻撃間隔がある時
					else{
						//攻撃間隔を1フレームずつ減らす
						mBossAttackItr--;
					}
				}
				//敵のヨーヨーが発射された時の処理を行う
				else {
					//ボスのヨーヨーの寿命が来たら
					if (mpBWeapon->mLife < 0){
						//ヨーヨーを消す
						mpBWeapon = NULL;
						//ヨーヨーのアニメーションを最初に戻す
						mBossAnimeFream = 0;
						//待機状態にする
						if (mpBWeapon == NULL)
							mAttackBehavior = EIDOL;
					}
				}
				break;//ループ終了
				//攻撃処理終了

				//攻撃を受けた時
			case EDAMAGE:
				if (!mDirection)
					mVelocityX = 5;
				else
					mVelocityX = -5;
				//一定回数攻撃されると撃破される
				if (mBossLife <= 0)
					mAttackBehavior = EDOWN;

				else if (mBossAnimeFream > 1){
					mAttackBehavior = EIDOL;
				}
				break;//ループ終了

			case EDOWN://プレイヤーに負けた時
				//最後までアニメーションが進んだ時に処理開始
				if (mBossAnimeFream < 3){
					//消滅までのカウントダウン開始
					if (mBossDeleteTime){
						//0になるまで減算する
						mBossDeleteTime--;
						//消滅まで点滅？を繰り返す
						if (mBossDeleteTime % 10 == 0)
							mAlpha = 0.0f;
						else
							mAlpha = 1.0f;
					}
				}
				else {
					static int mBossDownTime = 0;
					mBossDownTime++;
					if (mBossDownTime >= BOSS_DOWN_TIME){
						CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERESULT);
						CGame2::mTimeMin = CTime::ElapsedTimeMin();
						CGame2::mTimeSec = CTime::ElapsedTimeSec();
						CScore::GetScore();
						return;
					}
				}
				break;
				//ダメージ処理終了
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

			if (mVelocityX > 0.0f)
				mVelocityX -= 0.25f;

			if (mVelocityX < 0.0f)
				mVelocityX += 0.25f;


			mPosition.x += mVelocityX;
			mBossLifeProportion = static_cast <float> (mBossLife) / static_cast <float> (mBossMaxLife);

			//基底クラスの更新処理
			CRectangle::Update();
		}
	}
	else if (CMapBossRoomSign::mpBossRoomSign != NULL && !CMapBossRoomSign::mpBossRoomSign->mColFlg){
		mBossBattle = false;
		mPosition = mBossDefaultPos;
		mAttackBehavior = EIDOL;
		mVelocityX = mVelocityY = 0.0f;
	}
}

bool CBoss::Collision(CRectangle*p){
	//return false;
	if (p->GetEnabled()){
		CVector2 aj;
		if (CRectangle::Collision(p, &aj)) {
			switch (p->mTag){
			case ECELLNUM::EUNDER:
				if ((mPosition.y > p->mPosition.y) && mVelocityY <= 0.0f){
					mVelocityY = 0.0f;
					mPosition.y = mPosition.y + aj.y;
				}
				break;
			case ECELLNUM::EPWEAPON://プレイヤーのヨーヨーと衝突した時
				mVelocityY = 0.0f;
				if (Invincible)
					return false;
				//無敵時間のフラグがOFFの時にダメージを加算する
				else{
					mBossLife--;
					//無敵時間のフラグをONにする
					Invincible = true;
					//攻撃を受けた時のアニメーションをする
					//一定回数以上の攻撃を受けてない時にアニメーションされる
					if (mAttackBehavior != EDOWN)
						mAttackBehavior = EDAMAGE;
				}
				break;

			case ECELLNUM::EBOX:
			case ECELLNUM::ESTEEL:
				//落下中のオブジェクトと接触した場合
				if (p->mBreak){
					mAttackBehavior = EDAMAGE;

					mVelocityY = 0.0f;
					if (Invincible)
						return false;
					//無敵時間のフラグがOFFの時にダメージを加算する
					else{
						mBossLife -= static_cast <float> (mBossMaxLife)* 0.2;
						//無敵時間のフラグをONにする
						Invincible = true;
						//攻撃を受けた時のアニメーションをする
						//一定回数以上の攻撃を受けてない時にアニメーションされる
						if (mAttackBehavior != EDOWN)
							mAttackBehavior = EDAMAGE;
					}
				}
				break;

			case ECELLNUM::ESWITCH_GROUND1:
			case ECELLNUM::ESWITCH_GROUND2:
			case ECELLNUM::ENONE:
			case ECELLNUM::ECHIKUWA:
			case ECELLNUM::EBELTL:
			case ECELLNUM::EBELTR:
			case ECELLNUM::ESIGN:
			case ECELLNUM::EEWEAPON:
			case ECELLNUM::ESEARCH:
			case ECELLNUM::ESWITCH:
			case ECELLNUM::EPLAYER:
			case ECELLNUM::EENEMY1:
			case ECELLNUM::EENEMY2:
			case ECELLNUM::EENEMY3:
			case ECELLNUM::EICE:
			case ECELLNUM::EBOSSROOM:
			case ECELLNUM::EJEWELRY:
			case ECELLNUM::EJEWELRY2:
				break;

			default:
				CVector2 ad;
				if (aj.x > 0) {
					//右空き
					if (!(p->mColFlg & EDT_RIGHT)) {
						mPosition.x = mPosition.x + aj.x;
						//mAttackBehavior = EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
					}
				}
				else if (aj.x < 0) {
					//左空き
					if (!(p->mColFlg & EDT_LEFT)) {
						mPosition.x = mPosition.x + aj.x;
						//mAttackBehavior = EIDOL;
						if (mIce)
							mVelocityX = 0.0f;
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
							if (mAttackBehavior==EJUMP)
							mAttackBehavior = EIDOL;
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
		// アニメーションの枚数 - 1を指定し、その枚数を超えたら
		//if (mBossAnimeFream > 2)
			//アニメーションの最初に戻る
			//mBossAnimeFream = 0;
		//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
		//Boss_Ani_Count_Frame = 20;

		//if (!mDirection)//左向き
		//	mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2304, 2048, mAlpha);
		//else			//右向き
		//	mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2304, 2048, mAlpha);

		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;
		Boss_Ani_Count_Frame = 9;
		if (!mDirection)	//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);

		break;

	case EMANTO://マントアニメーション
		//テクスチャの枚数-1よりも値が大きくなれば
		if (mBossAnimeFream > 4)
			//ループの先頭に戻る
			mBossAnimeFream = 0;
		//次のコマに行くタイミング
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//右向き
			mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 512, 256, mAlpha);
		break;

	case EDASH://走り動作
		if (mBossAnimeFream > 4)
			mBossAnimeFream = 0;

		Boss_Ani_Count_Frame = 5;

		if (!mDirection)//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 256, 0, mAlpha);

		else//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 256, 0, mAlpha);
		break;

	case EJUMP://ジャンプ動作
		//ジャンプ上昇中の時の処理
		if (mVelocityY > 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame= 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2,mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE*2, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
			else				//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE*2, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 1536, 1280, mAlpha);
		}
		//ジャンプ下向中
		else if (mVelocityY < 0.0f){
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2, 
				mPosition.y + CELLSIZE * 2, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
			else				//右向き
				mTexture.DrawImage(mPosition.x - CELLSIZE*2, mPosition.x + CELLSIZE*2, mPosition.y - CELLSIZE*2,
				mPosition.y + CELLSIZE * 2, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
		}
		////ジャンプ最高地点
		//else if (mVelocityY >= BOSSGVELOCITY){
		//	//アニメーションの枚数-1を指定し、その枚数を超えたら
		//	if (mBossAnimeFream > 4)
		//		mBossAnimeFream = 0;//ループ開始位置(1枚目のアニメーション)に戻る

		//	//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
		//	Boss_Ani_Count_Frame = 4;

		//	if (!mDirection)//左向き
		//		mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 768, 512, mAlpha);

		//	else			//右向き
		//		mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 768, 512, mAlpha);
		//}
		//着地地点
		else if (mVelocityY == 0.0f){
			//アニメーションの枚数-1を指定し、その枚数を超えたら
			if (mBossAnimeFream > 3)
				mBossAnimeFream = 0;//ループ開始位置(1枚目のアニメーション)に戻る

			//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
			Boss_Ani_Count_Frame = 10;

			if (!mDirection)//左向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2506, 2250, mAlpha);

			else			//右向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2506, 2250, mAlpha);
		}
		break;

	case EBWEAPON://攻撃
		if (mpBWeapon != NULL){
			if (!mDirection)
				//ヨーヨーの紐
				mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_L, 1.0f);

			else
				//ヨーヨーの紐
				mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_R, 1.0f);
		}
		if (mpBWeapon){
			if (mBossAnimeFream > 3)
				mBossAnimeFream = 3;
		}
		else{
			if (mBossAnimeFream > 1)
				mBossAnimeFream = 0;
		}

			Boss_Ani_Count = 15;

			//左向き
			if (!mDirection)
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2048, 1792, mAlpha);
			//右向き
			else
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2048, 1792, mAlpha);
		break;


	case EDAMAGE://攻撃を受けた時
		if (mBossAnimeFream > 1){
			mBossAnimeFream = 0;
		}
		Boss_Ani_Count_Frame = 12;

		if (!mDirection)	//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1024, 768, mAlpha);
		else				//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1024, 768, mAlpha);
		break;


	case EDOWN://ダウンした時（プレイヤーに負けた時）
		//指定テクスチャの枚数を超えたら
		if (mBossAnimeFream > 3)
			//最後の画像で固定する
			mBossAnimeFream = 3;

		//アニメーションの速さを指定
		Boss_Ani_Count_Frame = 6;

		if (mBossAnimeFream == 3)
			mTexture.DrawImage(mPosition.x - CELLSIZE, mPosition.x + CELLSIZE, mPosition.y - CELLSIZE*2,
			mPosition.y + CELLSIZE, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);

		else{
			//左向き
			if (!mDirection)
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1280, 1024, mAlpha);
			//右向き
			else
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1280, 1024, mAlpha);
		}
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