#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CTaskManager.h"
#include "CWeapon.h"
#include "CCharcter.h"
#include "CPlayerT.h"

#define MONITOR_TIME 180
#define WALK_TIME 180
#define ENEMY_VELOCITY 1.5f
#define E_SEARCHRANGE 250	//索敵範囲

class CEnemy :public CCharcter{
public:
	CWeapon*mpEWeapon;	//敵が出すヨーヨーのインスタンス
	//static CEnemy *mpEnemy;
	float mVelocity;	//移動スピード
	bool mForward;	//移動方向 true:右 false:左
	int mMonitorTime;
	int mWalkTime;
	//アニメーションの切り替えをタグ付けで行う
	enum AnimationTag{
		EWALK,
		EMONITOR,
	};
	AnimationTag mAnimationTag;
	CEnemy(){
		mVelocityY = 0;	//重力の初期値を0にする
		CPlayerT::mpPlayer->mSearch = 40;
		mSearch =  E_SEARCHRANGE;
		mpEWeapon=0;	//敵のヨーヨーの値を0にしておく
		//mpEnemy = this;
		mTag = EENEMY1;
		mPriority = mTag;
		mForward = true;
		mAnimationTag = EWALK;
		mVelocity = ENEMY_VELOCITY;
		mMonitorTime = MONITOR_TIME;
		mWalkTime = WALK_TIME;

		CTaskManager::Get()->Add(this);
	}

	CEnemy::CEnemy(const CVector2&position, const CVector2&scale, CTexture*texture)
		: CEnemy()
	{
		SetRectangle(position, scale, texture);
	}

	void Update();
	void Render();
	bool Collision(CRectangle *p);
	//敵の攻撃認識範囲 指定した範囲内に入ると攻撃を開始する
	bool SearchCollision(CCharcter*, CCharcter*);
};
#endif