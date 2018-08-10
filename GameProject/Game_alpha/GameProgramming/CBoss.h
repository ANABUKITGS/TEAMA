#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include <stdlib.h>

#define BOSS_SEARCH 256					//ボスの索敵範囲を設定
#define BEHAVIOR 6.0f					//ボスの行動切り替え定数

class CBoss : public CCharcter{
//自クラスだけ使用可能
private:
	CVector2 mAttack_Search;			//ボスとプレイヤーとの距離を出す
	CWeapon*mpBWeapon;					//ボスの武器使用クラスをインスタンスにする
	float mBossBehavior;				//敵の各行動に入る判別距離
	int mBehaviorPattern;				//ボスの一部の行動にランダム要素を追加
	float mBossFowrd(float);			//ボスの向きに応じて
	enum AttackBehavior{
		ENONE,							//何もしない(初期化処理時のみ)
		EBWEAPON,						//武器を使用
		EDASH,							//走る
		EJUMP							//ジャンプ
	};
	AttackBehavior mAttackBehavior;
	//引数無しコンストラクタで変数等の初期化処理
	CBoss()
	{
		mBossBehavior = BEHAVIOR;		//敵の行動値を代入
		mAttackBehavior = ENONE;		//何もしない状態にする
		mTag = EBOSS;					//タグをボスにする
		mPriority = mTag;				//優先度をタグに入っている番号にする
		mRotation = NULL;				//回転値を0にする
		CTaskManager::Get()->Add(this);	//タスクリストにボスキャラクターを追加
	}

//共通使用可能
public:
	//引数有のコンストラクタで出現位置、大きさ（コリジョンの大きさ）を設定
	CBoss(CVector2 Pos, CVector2 scale)
		:CBoss()
	{
		SetRectangle(Pos, scale, NULL);	//サイズを指定（テクスチャは別で用意するので引数には入れない）

	}
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	bool Collision(CRectangle*);
};

#endif