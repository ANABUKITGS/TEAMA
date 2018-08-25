#ifndef CBOSS_H
#define CBOSS_H

#include "CCharcter.h"
#include "CEnemy.h"
#include "CPlayerT.h"
#include <stdlib.h>
#include <time.h>

#define BEHAVIOR 270.0f					//ボスの行動切り替え定数(移動から攻撃)
#define BOSS_DELCNT 200					//ボスの消滅カウント（とりあえず100frameに設定）
#define ANI_FPS 60						//ボスのアニメーションフレーム
#define BOSSDAMAGECNT 180				//ボスがダメージを受けて無敵になる時間
#define BOSSGVELOCITY 30.0f				//ボスのジャンプ定数
#define BOSSJUMPTIME 60					//ボスのジャンプカウント(仮で60フレームに設定)
#define BOSSANIMESIZE 512				//ボスのテクスチャサイズ
#define BOSSMOVESPEED 6					//ボスの移動速度
#define STARTBEHAVIOR 600				//ボス戦開始時のみ使用
#define BOSSINVINCIBLE 120	
#define BOSSNEXTBEHAVIOR 70				//ボスの待機から次の行動までの時間
#define BOSS_DOWN_TIME 120				//やられてからの待ち時間
#define BOSS_LIFE 50					//ボスの初期HP

#define BOSS_TEX_POS mPosition.x - CELLSIZE * 2, mPosition.x + CELLSIZE * 2, mPosition.y - mScale.y, mPosition.y - mScale.y + CELLSIZE * 4	//テクスチャー Position

class CBoss : public CCharcter{
//自クラスだけ使用可能
private:
	CTexture mTexture;					//ボスに貼り付けるテクスチャ
	CVector2 mAttack_Search;			//ボスとプレイヤーとの距離を出す
	CVector2 mBossDefaultPos;			//ボスの初期位置
	CWeapon*mpBWeapon;					//ボスの武器使用クラスをインスタンスにする
	float mBossBehavior;				//敵の各行動に入る判別距離
	int mBossAttackItr;					//ボスのヨーヨー発射間隔
	int Boss_Ani_Count;					//次のコマに行く
	int mBossAnimeFream;				//ボスのアニメーションのテクスチャの枚数
	int mBehaviorPattern;				//ボスの一部の行動にランダム要素を追加
	int mBossDeleteTime;				//ボスが消滅する時間の変数
	int mBossJumprad;					//ボスのジャンプをするタイミングをランダムにする
	int mBossJcnt;						//ボスのジャンプ間隔
	int Boss_Ani_Count_Frame;			//一コマのフレーム数
	int mBossInvincibleTime;			//ボスの無敵時間
	int mBossIBehavior;					//待機状態からのランダム行動
	bool Invincible;					//無敵時間用変数を追加
	void BossJump();

	//引数無しコンストラクタで変数等の初期化処理
	CBoss()
		:mpBWeapon(0)
	{
		srand((unsigned)clock());	//乱数を初期化(一回のみ)
		mVelocityY = 0;
		mVelocityX = 0;
		mBossInvincibleTime = BOSSINVINCIBLE;
		Boss_Ani_Count=0;
		Boss_Ani_Count_Frame=0;
		mBossAnimeFream=0;
		mBossLife = mBossMaxLife = BOSS_LIFE;
		mBossLifeProportion = 0.0f;
		mBossJcnt=0;					//ジャンプ間隔変数の値を0にする
		mBossJumprad=0;					//最初のジャンプタイミングを初期化する
		mBossDeleteTime = BOSS_DELCNT;	//ボスの消滅時間を初期化
		Invincible = false;				//無敵時間は最初偽にして初期化
		mDirection = false;				//最初の向きを左向きにする
		mBossBehavior = BEHAVIOR;		//敵の行動値を代入
		mBossAttackItr = 0;
		mBossBattle = false;
		mAttackBehavior = EIDOL;		//待機状態にする
		mTag = EBOSS;					//タグをボスにする
		mPriority = 10;					//優先度を設定
		mRender = false;				//当たり判定の描画を削除
		mTexture.Load(".\\Data\\Images\\Boss\\Boss.tga");//テクスチャデータを読み込む
		CTaskManager::Get()->Add(this);	//タスクリストにボスキャラクターを追加
	}

//共通使用可能
public:
	enum AttackBehavior{
		EIDOL,							//待機
		EMANTO,							//マントのしぐさ？
		EBWEAPON,						//武器を使用
		EDASH,							//走る
		EJUMP,							//ジャンプ
		EDAMAGE,						//ダメージ
		EDOWN,							//ダウン
		ESIZE,
	};

	int mBossLife;						//ボスのHP
	int mBossMaxLife;					//ボスのHPの最大値
	float mBossLifeProportion;			//ボスのHPの割合
	bool mBossBattle;					//バトル開始フラグ
	AttackBehavior mAttackBehavior;
	static CBoss*mpBoss;
	//引数有のコンストラクタで出現位置を設定
	CBoss(CVector2 Pos)
		:CBoss()
	{
		//サイズを指定（テクスチャは別で用意するので引数には入れない）
		SetRectangle(Pos + CVector2(0.0f, 56.0f), CVector2(32, 90), NULL);
		mBossDefaultPos = Pos + CVector2(0.0f, 56.0f);
	}
	~CBoss(){
		mpBoss = 0;
	}
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	bool Collision(CRectangle*);
};

#endif