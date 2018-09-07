#include "CBoss.h"
#include "CGame2.h"
#include "CScore.h"
#include "CScene.h"
#include "CFade.h"
#include "CTime.h"
#include "CMapSign.h"
#include "CMapScroll.h"
#include "CBossGimmick.h"

CBoss *CBoss::mpBoss = 0;

//乱数を初期化してランダムな値を出す
int CBoss::GetRand(int random){
	srand((unsigned)time(NULL) - clock());
	return rand() % random;
}

//-----------------------------------------------------BossBehP処理開始---------------------------------------------------------------------
/*
BossBehP
ボスが待機状態からランダムで起こす行動
待機状態から新たに行動を起こしたり、変更する場合はここで
*/
void CBoss::BossBehP(BehP BP){
	switch (BP){
	case EDASH_0: case EDASH_1: case EDASH_2://0,1,2は移動
		IdolInterval = NULL;
		mAttackBehavior = EDASH;
		break;
	case BehP::EJUMP_3://3はジャンプ
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
	case BehP::ETELEPO_4://4はプレイヤーの後ろにテレポート
		//プレイヤーの後ろに現れるタイミングをランダムにする
		mBossAttackItr = GetRand(BOSSTELEPOA + 1);
		IdolInterval = NULL;
		//透明になる動作に入る
		mTelepoEnabled = false;
		//テレポート動作に移動
		mAttackBehavior = ETELEPO;
		break;
	default:
		IdolInterval = 50;
		break;
	}
}
//-----------------------------------------------------BossBehP処理終了---------------------------------------------------------------------



//-----------------------------------------------------Boss_A_BehP処理開始------------------------------------------------------------------
/*
Boss_A_BehP
mAttackBehavior変数から行動につながる関数
BossBehP関数から繋がる新たな行動の追加や変更はここで
*/
void CBoss::Boss_A_BehP(){
	//待機状態からランダムで行動をとる(移動、ジャンプ、攻撃のどれか)
	mBossIBehavior = EIDOL_5;//GetRand(BehP::ESIZE_7);

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
				//整数型から列挙型へキャスト変換
				BossBehP(static_cast<BehP>(mBossIBehavior));
			}
		}
		mpBWeapon = 0;

		if (CBossGimmick::mpBossGimmick != NULL && CBossGimmick::mpBossGimmick->mGimmickFlg){
			//ボスが左にいるとき
			if (mPosition.x<CMapScroll::mpScroll->mPosition.x){
				//プレイヤーが左にいるとき
				if (CPlayerT::mpPlayer->mPosition.x < CMapScroll::mpScroll->mPosition.x){
					//ボスを右に向かせる
					mDirection = true;
					mVelocityX = BOSSMOVESPEED * 3;
				}
				//プレイヤーが右にいるとき
				else{
					//ボスを左に向かせる
					mDirection = false;
					break;
				}
			}
			//ボスが右にいるとき
			else{
				//プレイヤーが右にいるとき
				if (CPlayerT::mpPlayer->mPosition.x > CMapScroll::mpScroll->mPosition.x){
					//ボスを左にむかせる
					mDirection = false;
					mVelocityX = -BOSSMOVESPEED * 3;
				}
				//プレイヤーが左にいるとき
				else{
					//ボスを右に向かせる
					mDirection = true;
					break;
				}
			}
			mAttackBehavior = EJUMP;
			mVelocityY = BOSSGVELOCITY;
		}
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
				mBossAnimeFream = 0;
				mAttackBehavior = EBWEAPON;
				mVelocityX = 0;
			}
		}
		break;//ループ終了
		//走る処理終了


		//ボスのジャンプ処理
	case EJUMP:
		if (mBossAnimeFream == 4){
			mBossAnimeFream = 0;
			mAttackBehavior = EIDOL;
		}
		break;
		//ジャンプ処理終了

		//ボスの攻撃処理
	case EBWEAPON:
		//ボスがヨーヨーを出してない時
		if (!mpBWeapon){
			//ボスのアニメーションが最後まで行くと
			//ボスのヨーヨーを呼び出す
			if (mBossAnimeFream > 3){
				if (mDirection){
					mpBWeapon = new CWeapon(this, ECELLNUM::EBWEAPON, mPosition + CVector2(82.0f, 32.0f), mDirection);
				}

				else{
					mpBWeapon = new CWeapon(this, ECELLNUM::EBWEAPON, mPosition + CVector2(-82.0f, 32.0f), mDirection);
				}
				mpBWeapon->mScale = CVector2(20, 20);

				if (mDirection)		//敵が右を向いている時には右にヨーヨーを進ませる
					mpBWeapon->mPosition.x += 10;

				else				//敵が左を向いている時には左にヨーヨーを進ませる
					mpBWeapon->mPosition.x -= 10;
			}
		}
		//敵のヨーヨーが発射された時の処理を行う
		else {
			CVector2 mWeaponVec;
			mWeaponVec = mpBWeapon->mPosition - mPosition;
			//ボスのヨーヨーの寿命が来たら
			if (mpBWeapon->mLife < 0){
				if (abs(mWeaponVec.x)>mPosition.x){
					//ヨーヨーを消す
					mpBWeapon = NULL;
				}
				//待機状態にする
				if (mpBWeapon == 0){
					mAttackBehavior = EIDOL;
				}
			}
		}
		break;//ループ終了
		//攻撃処理終了
	case ETELEPO://瞬間移動
		if (Invincible)
			mAttackBehavior = EIDOL;
		//プレイヤーの後ろに出現した時
		else if (mTelepoEnabled){
			//消えるアニーメーションを最初に戻す
			mBossAnimeFreamT = 4;
			//アルファ値が一定値を超えているとき
			if (mAlpha >= 1.0){
				if (mBossAnimeFream == 4){
					mBossAnimeFream = 0;
					mAttackBehavior = EBWEAPON;
				}
			}
			//アルファ値が一定値を下回っている時
			else{
				//超えるまで加算する
				mAlpha += 0.03;
			}
			if (mAlpha <= 0.03){
				//プレイヤーの後ろに移動させる
				if (CPlayerT::mpPlayer->mDirection){
					mPosition = CVector2(CPlayerT::mpPlayer->mPosition.x - BOSSTELEPO, CPlayerT::mpPlayer->mPosition.y);
					mDirection = true;
				}
				else{
					mPosition = CVector2(CPlayerT::mpPlayer->mPosition.x + BOSSTELEPO, CPlayerT::mpPlayer->mPosition.y);
					mDirection = false;
				}
			}
		}
		//ボスが消える動作に入ったとき
		else{
			//ボスの消えるアニメーションが最後まで行ったとき
			if (mBossAnimeFreamT == 0){
				//アルファ値を減らす
				mAlpha -= 0.03;
				//アルファ値が一定値まで減った時
				if (mAlpha <= 0.0f){
					//カウントが0になるまで減算する
					mBossAttackItr--;
					//消える動作にはいったら出現するアニメーションを最初にもどす
					mBossAnimeFream = 0;
					//カウントが0になったら
					if (mBossAttackItr <= 0){
						//プレイヤーの後ろに出現させる
						mTelepoEnabled = true;
					}
				}
			}
		}
		break;

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
		if (mBossAnimeFream > 3){
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
			if (CSDiamond::mpSDiamond == NULL && !CSDiamond::mGetFlg)
				CSDiamond::mpSDiamond = new CSDiamond(CVector2(mPosition.x, mPosition.y));
			mBossDownTime++;
			if (mBossDownTime >= BOSS_DOWN_TIME && CSDiamond::mGetFlg){
				CFade::ChangeFade(CSceneChange::ECSCENECHANGE_NUM::ERESULT);
				CGame2::mTime = CTime::GetTime();
				CScore::GetScore();
				return;
			}
		}
		break;
		//ダメージ処理終了

		//ガード処理
	case EGUARD:
		//透明攻撃時のバグ修正の為、アルファ値を常にMAXにする
		mAlpha = 1.0f;
		//向きでガードした時に下がる方向を指定
		if (!mDirection)
			mVelocityX = 4;
		else
			mVelocityX = -4;
		//プレイヤーが発射したヨーヨーがプレイヤーに戻ったら、
		//敵の状態を待機状態に移行
		if (CPlayerT::mpPlayer->mpWeapon == 0){
			mBossAnimeFream = 0;
			mAttackBehavior = EIDOL;
		}

		if (CBossGimmick::mpBossGimmick != NULL && CBossGimmick::mpBossGimmick->mGimmickFlg){
			//ボスが左にいるとき
			if (mPosition.x<CMapScroll::mpScroll->mPosition.x){
				//プレイヤーが左にいるとき
				if (CPlayerT::mpPlayer->mPosition.x < CMapScroll::mpScroll->mPosition.x){
					//ボスを右に向かせる
					mDirection = true;
					mVelocityX = BOSSMOVESPEED * 3;
				}
				//プレイヤーが右にいるとき
				else{
					//ボスを左に向かせる
					mDirection = false;
					break;
				}
			}
			//ボスが右にいるとき
			else{
				//プレイヤーが右にいるとき
				if (CPlayerT::mpPlayer->mPosition.x > CMapScroll::mpScroll->mPosition.x){
					//ボスを左にむかせる
					mDirection = false;
					mVelocityX = -BOSSMOVESPEED * 3;
				}
				//プレイヤーが左にいるとき
				else{
					//ボスを右に向かせる
					mDirection = true;
					break;
				}
			}
			mAttackBehavior = EJUMP;
			mVelocityY = BOSSGVELOCITY;
		}
		break;
		//ガード処理終了

	case EAVOIDANCE:

		break;
	}
}
//-----------------------------------------------------Boss_A_BehP処理終了------------------------------------------------------------------



//-----------------------------------------------------Update処理開始-----------------------------------------------------------------------
/*
更新処理を行う
行動以外で細かな変更や追加はここで
*/
void CBoss::Update(){
	if (CMapBossRoomSign::mpBossRoomSign != NULL && CMapBossRoomSign::mpBossRoomSign->mColFlg && mBossBattle){
		if (CSceneChange::changenum != CSceneChange::ECSCENECHANGE_NUM::EEDITER){
			//ボスとプレイヤーとのベクトルを出す
			mAttack_Search = CPlayerT::mpPlayer->mPosition - mPosition;
			//一定間隔でジャンプの乱数を出す(とりあえず1秒に一回)
			if (mBossJcnt < BOSSJUMPTIME)
				mBossJcnt++;
			//一定時間経過すると乱数を出す
			else{
				mBossJumprad = GetRand(7);
				mBossJcnt = NULL;
			}
			//ジャンプの処理ここまで

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
			//ダメージを受けた時に行う処理ここまで

			//ボスの慣性法則
			if (mVelocityX > 0.0f)
				mVelocityX -= 0.25f;

			if (mVelocityX < 0.0f)
				mVelocityX += 0.25f;


			mPosition.x += mVelocityX;
			//ボスの慣性法則ここまで

			//ボスのHP処理
			mBossLifeProportion = static_cast <float> (mBossLife) / static_cast <float> (mBossMaxLife);

			//総行動処理
			Boss_A_BehP();

			//重力処理
			Gravity();

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
	if (mPosition.y < -100){
		mPosition.y = mBossDefaultPos.y;
		mPosition.x = CMapScroll::mpScroll->mPosition.x;
	}
}
//-----------------------------------------------------Update処理終了-----------------------------------------------------------------------



//-----------------------------------------------------Collision処理開始--------------------------------------------------------------------
/*
当たり判定処理を行う
当たり判定を変更、追加はここで
*/
bool CBoss::Collision(CRectangle*p){
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
				//ボスが無敵状態、ジャンプ中、ダウン中、透明攻撃のいずれかの状態の時は判定しない
				if (Invincible || mAttackBehavior == EJUMP || mAttackBehavior == EDOWN || mAttackBehavior == ETELEPO)
					return false;
				//アルファ値がMAX値よりも小さい時は攻撃はヒットしない
				else if (mAlpha < 1.0)
					return false;
				//ボスと向かい合っている時にヨーヨーで攻撃するとガードをする
				else if (CPlayerT::mpPlayer->mDirection != mDirection){
					mAttackBehavior = EGUARD;
					return false;
				}
				//無敵時間のフラグがOFFの時にダメージを加算する
				else  if(!Invincible){
					mVelocityY = 0.0f;
					mBossLife--;
					//無敵時間のフラグをONにする
					Invincible = true;
					//攻撃を受けた時のアニメーションをする
					//一定回数以上の攻撃を受けてない時にアニメーションされる
					if (mAttackBehavior != EDOWN)
						mAttackBehavior = EDAMAGE;
				}
				if (CPlayerT::mpPlayer->mpWeapon->mPosition.x > mPosition.x)
					mDirection = true;
				else
					mDirection = false;
				break;

			case ECELLNUM::EBOX:
			case ECELLNUM::ESTEEL:
				//落下中のオブジェクトと接触した場合
				if (p->mBreak){

					if (mAttackBehavior == EJUMP||Invincible||mAttackBehavior==EDOWN||mAlpha<1.0)
						return false;

					//無敵時間のフラグがOFFの時にダメージを加算する
					else if (!Invincible){
						mVelocityY = 0.0f;
						mBossLife -= static_cast <float> (mBossMaxLife)* 0.2;
						//無敵時間のフラグをONにする
						Invincible = true;
						//攻撃を受けた時のアニメーションをする
						//一定回数以上の攻撃を受けてない時にアニメーションされる
						if (mAttackBehavior != EDOWN||mAttackBehavior!=ETELEPO)
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
			case ECELLNUM::EBWEAPON:
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
			case ECELLNUM::ESDIAMOND:
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
//-----------------------------------------------------Collision処理終了--------------------------------------------------------------------



//-----------------------------------------------------Render処理開始-----------------------------------------------------------------------
/*
アニメーションの速さや新たに追加、変更はここで
*/
void CBoss::Render(){
	switch (mAttackBehavior){

	case EIDOL://待機状態
		// アニメーションの枚数 - 1を指定し、その枚数を超えたら
		if (mBossAnimeFream > 2)
		//アニメーションの最初に戻る
		mBossAnimeFream = 0;
		//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
		Boss_Ani_Count_Frame = 10;
		if (!mDirection)//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2304, 2048, mAlpha);
		else			//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2304, 2048, mAlpha);
		break;

	case EMANTO://マントアニメーション
		//テクスチャの枚数-1よりも値が大きくなれば
		if (mBossAnimeFream > 4)
			//ループの先頭に戻る
			mBossAnimeFream = 0;
		//次のコマに行くタイミング
		Boss_Ani_Count_Frame = 5;

		if (!mDirection)	//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
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

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1536, 1280, mAlpha);
			else				//右向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1536, 1280, mAlpha);
		}
		//ジャンプ下向中
		else if (mVelocityY < -0.1f){
			if (mBossAnimeFream >0)
				mBossAnimeFream = 0;

			Boss_Ani_Count_Frame = 10;

			if (!mDirection)	//左向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);
			else				//右向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 1792, 1536, mAlpha);
		}
		//着地地点
		else if (mVelocityY==0.0){
			//アニメーションの枚数-1を指定し、その枚数を超えたら
			if (mBossAnimeFream > 4)
				mBossAnimeFream = 4;//ループ開始位置(1枚目のアニメーション)に戻る

			//アニメーションの速さを指定(減値:速いアニメーション,増値:遅いアニメーション)
			Boss_Ani_Count_Frame = 7;

			if (!mDirection)//左向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream+1) * 256, mBossAnimeFream * 256, 1792, 1536, mAlpha);

			else			//右向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream+1) * 256, 1792, 1536, mAlpha);
		}
		break;

	case EBWEAPON://攻撃
		if (mpBWeapon != NULL){
			//if (!mDirection)
			//	//ヨーヨーの紐
			//	mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_L, 1.0f);

			//else
			//	//ヨーヨーの紐
			//	mpBWeapon->mTexYoyo.DrawImage(BSTRING_UV_R, 1.0f);

				mBossAnimeFream = 3;
		}
		else{
			if (mBossAnimeFream > 2)
				mBossAnimeFream = 3;
		}
		Boss_Ani_Count_Frame = 5;

			//左向き
			if (!mDirection)
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 2048, 1792, mAlpha);
			//右向き
			else
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 2048, 1792, mAlpha);
		break;
		
			case ETELEPO://瞬間移動
		if (!mTelepoEnabled){
			//テクスチャの枚数-1よりも値が大きくなれば
			if (mBossAnimeFreamT < 1)
				//ループの先頭に戻る
				mBossAnimeFreamT = 0;
			//次のコマに行くタイミング
			Boss_Ani_Count_Frame = 6;

			if (!mDirection)	//左向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFreamT + 1) * 256, mBossAnimeFreamT * 256, 512, 256, mAlpha);
			else				//右向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFreamT * 256, (mBossAnimeFreamT + 1) * 256, 512, 256, mAlpha);
		}
		else if(mTelepoEnabled){
			//テクスチャの枚数-1よりも値が大きくなれば
			if (mBossAnimeFream > 4)
				//ループの先頭に戻る
				mBossAnimeFream = 4;
			//次のコマに行くタイミング
			Boss_Ani_Count_Frame = 6;

			if (!mDirection)	//左向き
				mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
			else				//右向き
				mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
		}
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

	case EGUARD://ガードした時
		//指定テクスチャの枚数を超えたら
		if (mBossAnimeFream > 0)
			//最後の画像で固定する
			mBossAnimeFream = 0;
		if (!mDirection)	//左向き
			mTexture.DrawImage(BOSS_TEX_POS, (mBossAnimeFream + 1) * 256, mBossAnimeFream * 256, 512, 256, mAlpha);
		else				//右向き
			mTexture.DrawImage(BOSS_TEX_POS, mBossAnimeFream * 256, (mBossAnimeFream + 1) * 256, 512, 256, mAlpha);
		break;
	}
	//次のコマに行く為に加算する
	Boss_Ani_Count++;
	//一コマのフレーム数よりも大きくなれば
	if (Boss_Ani_Count > Boss_Ani_Count_Frame){
		if (mAttackBehavior == ETELEPO)
			mBossAnimeFreamT--;
		//次のコマに行く
		mBossAnimeFream++;
		//カウントをリセットする
		Boss_Ani_Count = 0;
	}
}
//-----------------------------------------------------Render処理終了-----------------------------------------------------------------------