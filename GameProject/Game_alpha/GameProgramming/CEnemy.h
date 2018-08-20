#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CCharcter.h"
#include "CPlayerT.h"

#define MONITOR_TIME	180
#define WALK_TIME		180
#define ENEMY_VELOCITY	4.0f
#define E_SEARCHRANGE	250	//索敵範囲
#define DOWN_TIME		100
#define ATTACK_INTERVAL	120

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
public:
	CWeapon*mpEWeapon;	//敵が出すヨーヨーのインスタンス
	CSearch* mpSearch;
	static CEnemy *mpEnemy;
	float mVelocity;	//移動スピード
	int mMonitorTime;	//立ち止まる時間
	int mWalkTime;		//歩く時間
	int mDownTime;		//ダウンしてから消えるまでの時間
	int mAttackInterval;//攻撃インターバル
	//アニメーションの切り替えをタグ付けで行う
	enum AnimationTag{
		EWALK,
		EIDOL,
		EDOWN,
		EATTACK,
	};
	AnimationTag mAnimationTag;
	CEnemy(){
		mVelocityY = 0;	//重力の初期値を0にする
		mpEWeapon=0;	//敵のヨーヨーの値を0にしておく
		//mpEnemy = this;
		mTag = EENEMY1;
		mPriority = 1;
		mDirection = true;
		mAnimationTag = EWALK;
		mVelocity = ENEMY_VELOCITY;
		mMonitorTime = MONITOR_TIME;
		mWalkTime = WALK_TIME;
		mDownTime = DOWN_TIME;
		mAttackInterval = ATTACK_INTERVAL;
		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position)
		: CEnemy()
	{
		SetRectangle(position, CVector2(32, 60), NULL);
		mpSearch = new CSearch(CVector2(position.x + 128, position.y));
	}

	void Update();
	void Render();
	bool Collision(CRectangle *p);
	//敵の攻撃認識範囲 指定した範囲内に入ると攻撃を開始する
	//bool SearchCollision(CCharcter*, CCharcter*);
};

#endif