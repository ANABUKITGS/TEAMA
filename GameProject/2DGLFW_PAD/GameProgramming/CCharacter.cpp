#include "CCharacter.h"
#include "CKey.h"
#include <math.h>
#include "CSceneGame2.h"

//プレイヤーのインスタンス
CPlayer2 *CPlayer2::spInstance = 0;

//プレイヤー移動速度
#define VELOCITY_P 2
//ジャンプ初速
#define VELOCITY_JUMP 15
//重力加速度
#define GRAVITY 1
//敵移動速度
#define VELOCITY_E 1

//UVマッピング 敵の歩き
#define UVENEMYWALK1 136, 156, 190, 161
#define UVENEMYWALK2 168, 188, 190, 161
#define UVENEMYWALK1L 156, 136, 190, 161
#define UVENEMYWALK2L 188, 168, 190, 161
//敵泣き
#define UVENEMYCRY 196, 216, 190, 161
//UVマッピング プレイヤーの歩き
#define UVPLAYERWALK1 136, 156, 158, 130
#define UVPLAYERWALK2 168, 188, 158, 130
#define UVPLAYERWALK1L 156, 136, 158, 130
#define UVPLAYERWALK2L 188, 168, 158, 130
//プレイヤー泣き
#define UVPLAYERCRY 196, 216, 158, 130

/*
プレイヤーの更新処理
*/
void CPlayer2::Update() {
	//右へ移動
	if (CKey::Push('D') || CSceneGame2::mGamePad.mpButtons[PAD_RIGHT]
		|| CSceneGame2::mGamePad.mpPositions[0] > 0.08f) {
		x += VELOCITY_P;
		//X座標によって画像を変える
		if (x % 30 < 15) {
			//右画像1
			SetUv(UVPLAYERWALK1);
		}
		else {
			//右画像2
			SetUv(UVPLAYERWALK2);
		}
	}
	//左へ移動
	if (CKey::Push('A') || CSceneGame2::mGamePad.mpButtons[PAD_LEFT]
		|| CSceneGame2::mGamePad.mpPositions[0] < -0.08f) {
		//開始位置より左へ行かせない
		if (mStartX < x)
			x -= VELOCITY_P;
		//X座標によって画像を変える
		if (x % 30 < 15) {
			//左画像1
			SetUv(UVPLAYERWALK1L);
		}
		else {
			//左画像2
			SetUv(UVPLAYERWALK2L);
		}
	}
	//ジャンプする
	if ((CKey::Once(' ') || CSceneGame2::mGamePad.mpButtons[PAD_3]) && mState == ERUN) {
		mGravityV = VELOCITY_JUMP;
		//43
		//ジャンプ上
		mState = EJUMPUP;
		//1回再生
		mSound.Play();
	}
	if (mGravityV < -GRAVITY)
		//ジャンプ下
		mState = EJUMPDOWN;
	//重力速度分移動
	y += mGravityV;
	//重力速度更新
	mGravityV -= GRAVITY;
}
/*
プレイヤーの衝突処理
*/
bool CPlayer2::Collision(CCharacter *m, CCharacter *yo) {
	int dx, dy;
	//相手と衝突しているか判定
	if (CRectangle::Collision(yo, &dx, &dy)) {
		switch (yo->mTag) {
		//43
		case EENEMY: //相手が敵の時
			switch (yo->mState) {
			case ERUN:
				if (mState == ERUN) {
					mState = ECRY;
					SetUv(UVPLAYERCRY);
				}
				break;
			case ECRY:
				//戻りが小さい方へ戻す
				if (abs(dx) < abs(dy)) {
					x += dx;
				}
				else {
					y += dy;
					//重力初期化
					mGravityV = 0;
					//43
					//歩く
					mState = ERUN;
				}
				break;
			}
			break;
		case EBLOCK: //相手がブロック
			//戻りが小さい方へ戻す
			if (abs(dx) < abs(dy)) {
				x += dx;
			}
			else {
				y += dy;
				//重力初期化
				mGravityV = 0;
				//43
				//歩く
				mState = ERUN;
			}
			break;
		}
		//衝突している
		return true;
	}
	//衝突していない
	return false;
}
/*
敵の更新処理
*/
void CEnemy2::Update() {
	//43
	//泣いてる時は動かない
	if (mState == ECRY) return;
	//移動する
	x += mForward * VELOCITY_E;
	//重力速度分移動
	y += mGravityV;
	//重力速度更新
	mGravityV -= GRAVITY;
	//X座標によって画像の切り替え
	if (x % 30 < 15) {
		if (mForward > 0)
			//右画像
			SetUv(UVENEMYWALK1);
		else
			//左画像
			SetUv(UVENEMYWALK1L);
	}
	else {
		if (mForward > 0)
			//右画像
			SetUv(UVENEMYWALK2);
		else
			//左画像
			SetUv(UVENEMYWALK2L);
	}
}
/*
敵の衝突処理
*/
bool CEnemy2::Collision(CCharacter *m, CCharacter *yo) {
	int dx, dy;
	//相手と衝突しているか判定
	if (CRectangle::Collision(yo, &dx, &dy)) {
		switch (yo->mTag) {
		case EBLOCK: //相手がブロック
			//戻りが小さい方へ戻す
			if (abs(dx) < abs(dy)) {
				x += dx;
				//向きを反転させる
				mForward *= -1;
			}
			else {
				y += dy;
				//重力初期化
				mGravityV = 0;
			}
			break;
		//43
		case EPLAYER: //相手がプレイヤー
			//ジャンプ降下中
			if (yo->mState == EJUMPDOWN) {
				//泣きます
				SetUv(UVENEMYCRY);
				mState = ECRY;
			}
			break;
		}
		//衝突している
		return true;
	}
	//衝突していない
	return false;
}
//テクスチャマッピングの設定
void CCharacter::SetUv(int u0, int u1, int v0, int v1) {
	mU[0] = u0;
	mU[1] = u1;
	mV[0] = v0;
	mV[1] = v1;
}
