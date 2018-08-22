#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include <stdlib.h>
#include <time.h>

#define BOSS_SEARCH 256					//ボスの索敵範囲を設定
#define BEHAVIOR 300.0f					//ボスの行動切り替え定数
#define BOSS_DELCNT 100					//ボスの消滅カウント（とりあえず100frameに設定）
#define ANI_FPS 60						//ボスのアニメーションフレーム
#define BOSSDAMAGECNT 180				//ボスがダメージを受けて無敵になる時間
#define BOSSGVELOCITY 30.0f				//ボスの重力定数
#define BOSSJUMPTIME 60					//ボスのジャンプカウント(仮で60フレームに設定)
#define BOSSANIMESIZE 512				//ボスのテクスチャサイズ
#define BOSSMOVESPEED 6					//ボスの移動速度
#define STARTBEHAVIOR BEHAVIOR			//ボス戦開始時のみ使用
#define BOSSINVINCIBLE 120	

class CBoss : public CCharcter{
//自クラスだけ使用可能
private:
	CTexture mTexture;					//ボスに貼り付けるテクスチャ
	CVector2 mAttack_Search;			//ボスとプレイヤーとの距離を出す
	CVector2 mForward;					//向いている方向を前にするインスタンス
	CWeapon*mpBWeapon;					//ボスの武器使用クラスをインスタンスにする
	float mBossBehavior;				//敵の各行動に入る判別距離
	float BossFowrd(float);				//ボスの向きに応じて
	//float BossJump(bool);				//ボスのジャンプ処理(※float型メソッド)
	int mBossAttackItr;					//ボスのヨーヨー発射間隔
	int Boss_Ani_Count;					//次のコマに行く
	int mBossAnimeFream;				//ボスのアニメーションのテクスチャの枚数
	int mBehaviorPattern;				//ボスの一部の行動にランダム要素を追加
	int mBossDeleteTime;				//ボスが消滅する時間の変数
	int mBossDamageCnt;					//ボスがダメージを受けた時に加算する変数
	int mBossJumprad;					//ボスのジャンプをするタイミングをランダムにする
	int mBossJcnt;						//ボスのジャンプ間隔
	int Boss_Ani_Count_Frame;			//一コマのフレーム数
	int mBossInvincibleTime;			//ボスの無敵時間
	bool Invincible;					//無敵時間用変数を追加
	void BossJump();
	enum AttackBehavior{
		ENONE,							//何もしない(初期化処理時のみ)
		EIDOL,							//待機
		EMANTO,							//マントのしぐさ？
		EBWEAPON,						//武器を使用
		EDASH,							//走る
		EJUMP,							//ジャンプ
		EDAMAGE,						//ダメージ
		EDOWN,							//ダウン
	};
	AttackBehavior mAttackBehavior;
	//引数無しコンストラクタで変数等の初期化処理
	CBoss()
		:mpBWeapon(0)
	{
		srand((unsigned)clock());	//乱数を初期化(一回のみ)
		mVelocityY = 0;				//初期重力値を0にする
		mBossInvincibleTime = BOSSINVINCIBLE;
		Boss_Ani_Count=NULL;
		Boss_Ani_Count_Frame=NULL;
		mBossAnimeFream=NULL;
		mBossDamageCnt=NULL;
		mBossJcnt=NULL;					//ジャンプ間隔変数の値を0にする
		mBossJumprad=NULL;				//最初のジャンプタイミングを初期化する
		mBossDeleteTime = BOSS_DELCNT;	//ボスの消滅時間を初期化
		Invincible = false;
		mDirection = false;				//最初の向きを左向きにする
		mBossBehavior = BEHAVIOR;		//敵の行動値を代入
		mBossAttackItr = ATTACK_INTERVAL;
		mAttackBehavior = ENONE;		//何もしない状態にする
		mTag = EBOSS;					//タグをボスにする
		mPriority = 10;					//優先度を設定
		mRender = false;				//当たり判定の描画を削除
		mTexture.Load(".\\Data\\Images\\Boss\\Boss.tga");//テクスチャデータを読み込む
		CTaskManager::Get()->Add(this);	//タスクリストにボスキャラクターを追加
	}

//共通使用可能
public:
	//引数有のコンストラクタで出現位置を設定
	CBoss(CVector2 Pos)
		:CBoss()
	{
		//サイズを指定（テクスチャは別で用意するので引数には入れない）
		SetRectangle(Pos, CVector2(32,90),NULL);
	}
	static CBoss*mpBoss;
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	bool Collision(CRectangle*);
};

#endif