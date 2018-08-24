#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CCharcter.h"
#include "CPlayerT.h"

#define MONITOR_TIME			180
#define WALK_TIME				180
#define ENEMY_VELOCITY_X_LIMIT	4.5f
#define ENEMY_VELOCITY_X		1.25f	//入力
#define ENEMY_VELOCITY_X_ICE	0.15f	//入力 氷足場
#define ENEMY_VELOCITY_X2		0.25f	//非入力
#define ENEMY_VELOCITY_X2_ICE	0.05f	//非入力 氷足場
#define E_SEARCHRANGE			250		//索敵範囲
#define DOWN_TIME				100
#define ATTACK_INTERVAL			120
#define ATTACK_INTERVAL2		30

class CSearch :public CRectangle{
public:
	bool mDiscovery;	//true:索敵範囲内
	CSearch(){
		mTag = ECELLNUM::ESEARCH;
		mDiscovery = false;
		mRender = false;
		CTaskManager::Get()->Add(this);
	}
	CSearch::CSearch(const CVector2&position)
		:CSearch()
	{
		SetRectangle(position, CVector2(128, 32), NULL);
	}
	void Update();
	bool Collision(CRectangle *p);
	void Render();
};

class CEnemy :public CCharcter{
private:
	CTexture mTexEnemy01;
	CTexture mTexEnemy02;
	CTexture mTexEnemy03;

public:
	enum EENEMYANI{
		EIDOL = 1,	//アイドル状態
		EWALK,		//歩く
		ETURN,		//方向転換
		EJUMP,		//ジャンプ
		EDAMAGE,	//ダメージ
		EYOYO,		//ヨーヨー攻撃
		EDOWN,		//やられ
		EBOX,		//箱を落とす動作
		ESIZE,		//EPLAYERANI サイズ
	};
	int enemy_ani;
	int enemy_ani_count;
	int enemy_ani_count_flame;
	int ENEMY_ANI_COUNT_FLAME;

	CWeapon*mpEWeapon;	//敵が出すヨーヨーのインスタンス
	CSearch* mpSearch;
	static CEnemy *mpEnemy;
	int mMonitorTime;	//立ち止まる時間
	int mWalkTime;		//歩く時間
	int mDownTime;		//ダウンしてから消えるまでの時間
	int mAttackInterval;//次の攻撃までの時間
	int mAttackInterval2;	//索敵範囲内に入られてからの時間


	CEnemy(){
		mVelocityY = 0.0f;	//重力の初期値を0にする
		mVelocityX = 0.0f;
		mpEWeapon=0;	//敵のヨーヨーの値を0にしておく
		mPriority = 1;
		mDirection = true;
		enemy_ani = EENEMYANI::EWALK;
		mMonitorTime = MONITOR_TIME;
		mWalkTime = WALK_TIME;
		mDownTime = DOWN_TIME;
		mAttackInterval = ATTACK_INTERVAL;
		mAttackInterval2 = ATTACK_INTERVAL2;
		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position, ECELLNUM tag)
		: CEnemy()
	{
		SetRectangle(position, CVector2(32, 60), NULL);
		mpSearch = new CSearch(CVector2(position.x + 128, position.y));
		mTag = tag;
		mRender = false;
		mIce = false;
		enemy_ani = EENEMYANI::EWALK;
		enemy_ani_count = 0;
		enemy_ani_count_flame = 0;
		ENEMY_ANI_COUNT_FLAME = 0;

		if (tag == ECELLNUM::EENEMY1)
			mTexEnemy01.Load(".\\Data\\Images\\Enemy\\Enemy01.tga");

		else if (tag == ECELLNUM::EENEMY2)
			mTexEnemy02.Load(".\\Data\\Images\\Enemy\\Enemy02.tga");

		else if (tag == ECELLNUM::EENEMY3)
			mTexEnemy03.Load(".\\Data\\Images\\Enemy\\Enemy03.tga");
	}
	~CEnemy(){
		mpEnemy = 0;
	}

	void Update();
	void Render();
	bool Collision(CRectangle *p);
	//敵の攻撃認識範囲 指定した範囲内に入ると攻撃を開始する
	//bool SearchCollision(CCharcter*, CCharcter*);
};

#endif